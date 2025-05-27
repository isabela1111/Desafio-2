#include "udeastay.h"
#include "medicionrecursos.h"
#include "reservacion.h"
#include "fecha.h"
#include "alojamiento.h"
#include "anfitrion.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

UdeAStay::UdeAStay() {
    huespedes = nullptr;
    totalHuespedes = 0;

    alojamientos = nullptr;
    totalAlojamientos = 0;

    anfitriones = nullptr;
    totalAnfitriones = 0;

    capacidadReservas = 300;
    totalReservas = 0;
    reservas = new Reservacion*[capacidadReservas];
    MedicionRecursos::agregarMemoria(sizeof(reservas));
    fechaCorteDefinida = false;

    cargarHuespedes();
    cargarAlojamientos();
    anfitriones = new Anfitrion*[100];
    MedicionRecursos::agregarMemoria(100*sizeof(anfitriones));
    cargarAnfitriones(anfitriones, totalAnfitriones, 100);
    cargarReservaciones();
    cargarFechaCorteDesdeArchivo();
}

UdeAStay::~UdeAStay() {
    delete[] huespedes;
    delete[] alojamientos;
    for (int i = 0; i < totalReservas; i++) {
        MedicionRecursos::contarCiclo();
        delete reservas[i];
    }
    delete[] reservas;

    for (int i = 0; i < totalAnfitriones; i++) {
         MedicionRecursos::contarCiclo();
        delete anfitriones[i];
    }
    delete[] anfitriones;
}

bool igualesSinMayusculasYEspacios(const char* a, const char* b) {
    while (*a && *b) {
        MedicionRecursos::contarCiclo();
        while (*a == ' ') a++;
        while (*b == ' ') b++;

        char ca = *a;
        char cb = *b;
        if (ca >= 'A' && ca <= 'Z') ca = ca + ('a' - 'A');
        if (cb >= 'A' && cb <= 'Z') cb = cb + ('a' - 'A');
        if (ca != cb) return false;

        if (*a) a++;
        if (*b) b++;
    }
    while (*a == ' ') a++;
    while (*b == ' ') b++;
    return *a == '\0' && *b == '\0';
}

void UdeAStay::cargarHuespedes() {
    FILE* archivo = fopen("Huespedes.txt", "r");
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo huespedes.txt" << endl;
        return;
    }
    char linea[256];
    int contador = 0;
    while (fgets(linea, 256, archivo)) {
        MedicionRecursos::contarCiclo();
        if (strlen(linea) > 1) contador++;
    }
    if (contador == 0) {
        cout << "Archivo vacio o sin lineas validas." << endl;
        fclose(archivo);
        return;
    }
    rewind(archivo);
    huespedes = new Huesped[contador];
    MedicionRecursos::agregarMemoria(contador*sizeof(huespedes));
    totalHuespedes = 0;
    while (fgets(linea, 256, archivo)) {
        MedicionRecursos::contarCiclo();
        linea[strcspn(linea, "\r\n")] = 0;

        char* token = strtok(linea, ";");
        if (token == NULL) continue;

        char doc[20];
        strcpy(doc, token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        int ant = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        float punt = atof(token);

        if (ant < 0 || punt < 0.0f || punt > 5.0f) {
            cout << "Linea invalida: " << doc << endl;
            continue;
        }
        huespedes[totalHuespedes] = Huesped(doc, ant, punt);
        totalHuespedes++;
    }
    fclose(archivo);
}

void UdeAStay::cargarAnfitriones(Anfitrion* anfitriones[], int& totalAnfitriones, int maxAnfitriones) {
    FILE* archivo = fopen("Anfitriones.txt", "r");
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo anfitriones.txt.\n";
        totalAnfitriones = 0;
        return;
    }
    char linea[256];
    totalAnfitriones = 0;

    while (fgets(linea, 256, archivo) && totalAnfitriones < maxAnfitriones) {
        MedicionRecursos::contarCiclo();
        linea[strcspn(linea, "\n")] = '\0';
        char* documento = strtok(linea, ";");
        char* strAntiguedad = strtok(NULL, ";");
        char* strPuntuacion = strtok(NULL, ";");
        char* codigosTexto = strtok(NULL, ";");

        if (!documento || !strAntiguedad || !strPuntuacion)
            continue;

        int antiguedad = atoi(strAntiguedad);
        float puntuacion = atof(strPuntuacion);

        int codigos[100];
        int cantidad = 0;

        if (codigosTexto && strlen(codigosTexto) > 0) {
            char* token = strtok(codigosTexto, ",");
            while (token != NULL && cantidad < 100) {
                MedicionRecursos::contarCiclo();
                codigos[cantidad++] = atoi(token);
                token = strtok(NULL, ",");
            }
        }
        anfitriones[totalAnfitriones] = new Anfitrion(documento, antiguedad, puntuacion, codigos, cantidad);
        MedicionRecursos::agregarMemoria(sizeof(Anfitrion));
        totalAnfitriones++;
    }
    fclose(archivo);
}

void UdeAStay::cargarAlojamientos() {
    FILE* archivo = fopen("Alojamientos.txt", "r");
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo de alojamientos.\n";
        return;
    }
    char linea[300];
    int contador = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        MedicionRecursos::contarCiclo();
        if (strlen(linea) > 1) contador++;
    }
    rewind(archivo);
    alojamientos = new Alojamiento[contador];
    MedicionRecursos::agregarMemoria(contador*sizeof(alojamientos));
    totalAlojamientos = contador;

    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) && i < totalAlojamientos) {
        MedicionRecursos::contarCiclo();
        linea[strcspn(linea, "\r\n")] = 0;

        char* token = strtok(linea, ";");
        if (!token) continue;
        char cod[10]; strncpy(cod, token, sizeof(cod) - 1); cod[sizeof(cod) - 1] = '\0';

        token = strtok(NULL, ";"); if (!token) continue;
        char nom[50]; strncpy(nom, token, sizeof(nom) - 1); nom[sizeof(nom) - 1] = '\0';

        token = strtok(NULL, ";"); if (!token) continue;
        char docAnf[15]; strncpy(docAnf, token, sizeof(docAnf) - 1); docAnf[sizeof(docAnf) - 1] = '\0';

        token = strtok(NULL, ";"); if (!token) continue;
        char depto[30]; strncpy(depto, token, sizeof(depto) - 1); depto[sizeof(depto) - 1] = '\0';

        token = strtok(NULL, ";"); if (!token) continue;
        char muni[30]; strncpy(muni, token, sizeof(muni) - 1); muni[sizeof(muni) - 1] = '\0';

        token = strtok(NULL, ";"); if (!token) continue;
        char tipo[20]; strncpy(tipo, token, sizeof(tipo) - 1); tipo[sizeof(tipo) - 1] = '\0';

        token = strtok(NULL, ";"); if (!token) continue;
        char dir[60]; strncpy(dir, token, sizeof(dir) - 1); dir[sizeof(dir) - 1] = '\0';

        token = strtok(NULL, ";"); if (!token) continue;
        float precio = atof(token);

        token = strtok(NULL, ";"); if (!token) continue;
        char amen[200]; strncpy(amen, token, sizeof(amen) - 1); amen[sizeof(amen) - 1] = '\0';

        token = strtok(NULL, ";");
        char fechas[200] = "";
        if (token) {
            strncpy(fechas, token, sizeof(fechas) - 1);
            fechas[sizeof(fechas) - 1] = '\0';
        }
        alojamientos[i] = Alojamiento(cod, nom, docAnf, depto, muni, tipo, dir, precio, amen, fechas);
        MedicionRecursos::agregarMemoria(sizeof(Alojamiento));
        i++;
    }
    fclose(archivo);
}

void UdeAStay::cargarReservaciones() {
    FILE* archivo = fopen("Reservaciones_activas.txt", "r");
    if (!archivo) {
        cout << "No se pudo abrir el archivo de reservaciones activas.\n";
        return;
    }
    char linea[512];
    totalReservas = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        MedicionRecursos::contarCiclo();
        linea[strcspn(linea, "\r\n")] = 0;

        char* token = strtok(linea, ";");
        if (!token) continue;
        char codRes[15]; strncpy(codRes, token, sizeof(codRes) - 1); codRes[sizeof(codRes) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        char docH[20]; strncpy(docH, token, sizeof(docH) - 1); docH[sizeof(docH) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        char codAloj[10]; strncpy(codAloj, token, sizeof(codAloj) - 1); codAloj[sizeof(codAloj) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        int d, m, a;
        sscanf(token, "%d/%d/%d", &d, &m, &a);
        Fecha fechaInicio(d, m, a);

        token = strtok(NULL, ";");
        if (!token) continue;
        int noches = atoi(token);

        token = strtok(NULL, ";");
        if (!token) continue;
        char metodo[10]; strncpy(metodo, token, sizeof(metodo) - 1); metodo[sizeof(metodo) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        float monto = atof(token);

        token = strtok(NULL, ";");
        if (!token) continue;
        int dp, mp, ap;
        sscanf(token, "%d/%d/%d", &dp, &mp, &ap);
        Fecha fechaPago(dp, mp, ap);

        token = strtok(NULL, ";");
        char anot[1001] = "";
        if (token) strncpy(anot, token, sizeof(anot) - 1);

        Reservacion* r = new Reservacion(codRes, docH, codAloj, fechaInicio, noches, metodo, monto, fechaPago, anot);
        MedicionRecursos::agregarMemoria(sizeof(Reservacion));
        agregarReserva(r);
    }
    fclose(archivo);
}

void UdeAStay::cargarFechaCorteDesdeArchivo() {
    FILE* f = fopen("FechaCorte.txt", "r");
    if (!f) return;
    int d, m, a;
    if (fscanf(f, "%d/%d/%d", &d, &m, &a) == 3) {
        fechaCorte = Fecha(d, m, a);
        fechaCorteDefinida = true;
    }
    fclose(f);
}

void UdeAStay::guardarReservacionEnArchivo(const Reservacion& r) {
    FILE* archivo = fopen("Reservaciones_activas.txt", "a");
    if (!archivo) {
        cout << "No se pudo abrir reservas.txt para escribir.\n";
        return;
    }
    fprintf(archivo, "%s;%s;%s;%d/%d/%d;%d;%s;%.0f;%d/%d/%d;%s\n",
            r.getCodigo(),
            r.getDocumentoHuesped(),
            r.getCodigoAlojamiento(),
            r.getFechaInicio().getDia(),
            r.getFechaInicio().getMes(),
            r.getFechaInicio().getAnio(),
            r.getDuracion(),
            r.getMetodoPago(),
            r.getMonto(),
            r.getFechaPago().getDia(),
            r.getFechaPago().getMes(),
            r.getFechaPago().getAnio(),
            r.getAnotaciones()
            );
    fclose(archivo);
}

void UdeAStay::guardarFechaCorteEnArchivo() {
    FILE* f = fopen("FechaCorte.txt", "w");
    if (!f) {
        cout << "Error al guardar la fecha de corte.\n";
        return;
    }
    fprintf(f, "%02d/%02d/%04d", fechaCorte.getDia(), fechaCorte.getMes(), fechaCorte.getAnio());
    fclose(f);
}


void UdeAStay::agregarReserva(Reservacion* nueva) {
    if (totalReservas >= capacidadReservas) {
        int nuevaCapacidad = capacidadReservas * 2;
        Reservacion** nuevoArray = new Reservacion*[nuevaCapacidad];
        MedicionRecursos::agregarMemoria(nuevaCapacidad*sizeof(Reservacion));
        for (int i = 0; i < totalReservas; i++) {
            MedicionRecursos::contarCiclo();
            nuevoArray[i] = reservas[i];
        }
        delete[] reservas;
        reservas = nuevoArray;
        capacidadReservas = nuevaCapacidad;
    }
    reservas[totalReservas++] = nueva;
}

bool UdeAStay::huespedExiste(const char* documento) const {
    for (int i = 0; i < totalHuespedes; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(huespedes[i].getDocumento(), documento) == 0) {
            return true;
        }
    }
    return false;
}

bool UdeAStay::anfitrionExiste(const char* documento) const {
    for (int i = 0; i < totalAnfitriones; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(anfitriones[i]->getDocumento(), documento) == 0) {
            return true;
        }
    }
    return false;
}

int UdeAStay::obtenerUltimoCodigoReserva() {
    FILE* archivo = fopen("Reservaciones_activas.txt", "r");
    if (!archivo) return 0;

    char linea[256];
    int ultimo = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        MedicionRecursos::contarCiclo();
        char* token = strtok(linea, ";");
        if (token && token[0] == 'R') {
            int num = atoi(token + 1);
            if (num > ultimo) ultimo = num;
        }
    }
    fclose(archivo);
    return ultimo;
}

float UdeAStay::obtenerPuntuacionAnfitrion(const char* doc)const{
    for (int i = 0; i < totalAnfitriones; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(anfitriones[i]->getDocumento(), doc) == 0)
            return anfitriones[i]->getPuntuacion();
    }
    return 0.0;
}

void UdeAStay::aplicarFiltros(const char* municipio, const Fecha& inicio, int noches, float precioMax, float puntMin) const {
    cout << "\n--- ALOJAMIENTOS DISPONIBLES ---\n";
    bool alguno = false;

    for (int i = 0; i < totalAlojamientos; i++) {
        MedicionRecursos::contarCiclo();
        const Alojamiento& a = alojamientos[i];
        if (!igualesSinMayusculasYEspacios(a.getMunicipio(), municipio))
            continue;
        if (precioMax > 0 && a.getPrecioPorNoche() > precioMax)
            continue;
        if (puntMin > 0) {
            float puntAnfitrion = obtenerPuntuacionAnfitrion(a.getDocumentoAnfitrion());
            if (puntAnfitrion < puntMin)
                continue;
        }
        if (!a.disponibilidad(inicio, noches, reservas, totalReservas))
            continue;
        a.mostrar();
        alguno = true;
    }
    if (!alguno) {
        cout << "No hay alojamientos que cumplan con los filtros indicados.\n";
    }
}

void UdeAStay::anularReserva(const char* codigoReservaEliminar) {
    FILE* original = fopen("Reservaciones_activas.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    if (!original || !temp) {
        cout << "Error al abrir los archivos.\n";
        return;
    }
    char linea[1024];
    bool encontrada = false;
    char codAlojamiento[10] = "";
    Fecha fechaInicio;
    int duracion = 0;

    while (fgets(linea, sizeof(linea), original)) {
        MedicionRecursos::contarCiclo();
        char copia[1024];
        strcpy(copia, linea);
        copia[strcspn(copia, "\n")] = 0;

        char* token = strtok(copia, ";");
        if (token && strcmp(token, codigoReservaEliminar) == 0) {
            encontrada = true;

            strtok(NULL, ";");
            token = strtok(NULL, ";");
            if (token) strcpy(codAlojamiento, token);
            token = strtok(NULL, ";");
            if (token) {
                int d, m, a;
                sscanf(token, "%d/%d/%d", &d, &m, &a);
                fechaInicio = Fecha(d, m, a);
            }
            token = strtok(NULL, ";");
            if (token) duracion = atoi(token);
        }
        else {
            fputs(linea, temp);
        }
    }
    fclose(original);
    fclose(temp);
    remove("Reservaciones_activas.txt");
    rename("temp.txt", "Reservaciones_activas.txt");
    if (encontrada) {
        for (int i = 0; i < totalReservas; i++) {
            MedicionRecursos::contarCiclo();
            if (strcmp(reservas[i]->getCodigo(), codigoReservaEliminar) == 0) {
                delete reservas[i];
                for (int j = i; j < totalReservas - 1; j++) {
                    reservas[j] = reservas[j + 1];
                }
                totalReservas--;
                break;
            }
        }
        for (int i = 0; i < totalAlojamientos; i++) {
            MedicionRecursos::contarCiclo();
            if (strcmp(alojamientos[i].getCodigo(), codAlojamiento) == 0) {
                alojamientos[i].actualizarFechasAlojamiento(codAlojamiento, fechaInicio, duracion);
                break;
            }
        }
        cout << "Reservacion eliminada correctamente.\n";
    }
    else {
        cout << "No se encontro la reservacion con ese codigo.\n";
    }
}

void UdeAStay::actualizarHistorico() {
    if (!fechaCorteDefinida) {
        cout << "No hay fecha de corte definida.\n";
        return;
    }
    FILE* archivoIn = fopen("Reservaciones_activas.txt", "r");
    FILE* archivoHist = fopen("Historico.txt", "a");
    if (!archivoIn || !archivoHist) {
        cout << "Error al abrir archivos.\n";
        if (archivoIn) fclose(archivoIn);
        if (archivoHist) fclose(archivoHist);
        return;
    }
    char codigosAEliminar[300][15];
    int cantidadAEliminar = 0;

    char linea[1024];
    while (fgets(linea, sizeof(linea), archivoIn)) {
        MedicionRecursos::contarCiclo();
        char copia[1024];
        strcpy(copia, linea);
        copia[strcspn(copia, "\n")] = '\0';

        char* token = strtok(copia, ";");
        if (!token) continue;
        char codReserva[15]; strcpy(codReserva, token);

        token = strtok(NULL, ";");
        token = strtok(NULL, ";"); if (!token) continue;
        char codAloj[10]; strcpy(codAloj, token);

        token = strtok(NULL, ";"); if (!token) continue;
        int d, m, a;
        sscanf(token, "%d/%d/%d", &d, &m, &a);
        Fecha entrada(d, m, a);

        token = strtok(NULL, ";"); if (!token) continue;
        int duracion = atoi(token);
        Fecha salida = entrada.sumarDias(duracion - 1);

        if (salida.esMenorQue(fechaCorte)) {
            fputs(linea, archivoHist);
            strcpy(codigosAEliminar[cantidadAEliminar++], codReserva);
        }
    }
    fclose(archivoIn);
    fclose(archivoHist);
    for (int i = 0; i < cantidadAEliminar; i++) {
        MedicionRecursos::contarCiclo();
        anularReserva(codigosAEliminar[i]);
    }
    cout << "Reservas finalizadas pasadas al historico.\n";
}

void UdeAStay::menuReservar() {
    if (!fechaCorteDefinida) {
        cout << "Aun no se ha definido una fecha de corte.\n";
        cout << "Un anfitrion debe actualizar el historico antes de poder hacer reservas.\n";
        return;
    }
    cout << "\n--- RESERVACION DE ALOJAMIENTO ---\n";
    cout << "Como desea buscar alojamiento?\n";
    cout << "a) Por municipio y filtros\n";
    cout << "b) Directamente por codigo del alojamiento\n";
    char opcionBusqueda;
    cin >> opcionBusqueda;
    int dia, mes, anio;
    cout << "Ingrese la fecha de entrada (dd mm aaaa): ";
    cin >> dia >> mes >> anio;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Entrada invalida.\n";
        return;
    }
    Fecha entrada(dia, mes, anio);
    if (!entrada.validarFecha()) {
        cout << "Error: Fecha invalida.\n";
        return;
    }
    int noches;
    cout << "Cantidad de noches: ";
    cin >> noches;
    if (cin.fail() || noches <= 0) {
        cout << "Error: Duracion invalida.\n";
        return;
    }
    Fecha finReserva = entrada.sumarDias(noches - 1);
    Fecha limite = fechaCorte.sumarMeses(12);
    if (entrada.esMenorQue(fechaCorte) || finReserva.esMayorQue(limite)) {
        cout << "Error: Solo se permiten reservaciones entre ";
        fechaCorte.imprimirFechaLarga();
        cout << " y ";
        limite.imprimirFechaLarga();
        cout << ".\n";
        return;
    }
    char docH[20];
    cout << "Ingrese su documento de identidad: ";
    cin >> docH;
    Huesped* huesped = nullptr;
    for (int i = 0; i < totalHuespedes; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(huespedes[i].getDocumento(), docH) == 0) {
            huesped = &huespedes[i];
            break;
        }
    }
    if (!huesped) {
        cout << "Error: Huesped no encontrado.\n";
        return;
    }
    if (!huesped->verificarReservas(entrada, noches, reservas, totalReservas)) {
        cout << "Ya tienes reservas en esas fechas.\n";
        return;
    }
    Alojamiento* seleccionado = nullptr;
    if (opcionBusqueda == 'a' || opcionBusqueda == 'A') {
        char municipio[30];
        cout << "Ingrese el municipio que desea buscar: ";
        cin.ignore();
        cin.getline(municipio, sizeof(municipio));

        float maxPrecio = 9999999;
        float minPuntuacion = 0.0;
        char usarFiltro;
        cout << "Desea usar filtros? (s/n): ";
        cin >> usarFiltro;
        if (usarFiltro == 's' || usarFiltro == 'S') {
            char tipoFiltro;
            cout << "Que filtro desea aplicar?\n";
            cout << "a) Precio maximo\nb) Puntuacion minima\nc) Ambos\n";
            cin >> tipoFiltro;
            if (tipoFiltro == 'a' || tipoFiltro == 'c') {
                cout << "Ingrese precio maximo por noche: ";
                cin >> maxPrecio;
            }
            if (tipoFiltro == 'b' || tipoFiltro == 'c') {
                cout << "Ingrese puntuacion minima del anfitrion: ";
                cin >> minPuntuacion;
            }
        }
        bool hayDisponibles = false;
        for (int i = 0; i < totalAlojamientos; i++) {
            MedicionRecursos::contarCiclo();
            if (igualesSinMayusculasYEspacios(alojamientos[i].getMunicipio(), municipio) &&
                alojamientos[i].getPrecioPorNoche() <= maxPrecio &&
                obtenerPuntuacionAnfitrion(alojamientos[i].getDocumentoAnfitrion()) >= minPuntuacion &&
                alojamientos[i].disponibilidad(entrada, noches, reservas, totalReservas)) {
                hayDisponibles = true;
                break;
            }
        }
        if (!hayDisponibles) {
            cout << "No hay alojamientos disponibles con esos filtros.\n";
            return;
        }
        aplicarFiltros(municipio, entrada, noches, maxPrecio, minPuntuacion);
        cout << "Ingrese el codigo del alojamiento que desea reservar(si no desea ninguno ingrese 0): ";
        char codAloj[10];
        cin >> codAloj;
        for (int i = 0; i < totalAlojamientos; i++) {
            MedicionRecursos::contarCiclo();
            if (strcmp(alojamientos[i].getCodigo(), codAloj) == 0 &&
                alojamientos[i].disponibilidad(entrada, noches, reservas, totalReservas)) {
                seleccionado = &alojamientos[i];
                break;
            }
        }
    }
    else if (opcionBusqueda == 'b' || opcionBusqueda == 'B') {
        cout << "Ingrese el codigo del alojamiento: ";
        char codAloj[10];
        cin >> codAloj;

        for (int i = 0; i < totalAlojamientos; i++) {
            MedicionRecursos::contarCiclo();
            if (strcmp(alojamientos[i].getCodigo(), codAloj) == 0 &&
                alojamientos[i].disponibilidad(entrada, noches, reservas, totalReservas)) {
                seleccionado = &alojamientos[i];
                break;
            }
        }

        if (!seleccionado) {
            cout << "Alojamiento no disponible o codigo invalido.\n";
            return;
        }
    }
    else {
        cout << "Opcion invalida.\n";
        return;
    }

    if (!seleccionado) {
        cout << "Error: No se pudo seleccionar alojamiento.\n";
        return;
    }

    float monto = seleccionado->getPrecioPorNoche() * noches;
    char anotaciones[1001] = "";
    cout << "Ingrese anotaciones (opcional): ";
    cin.ignore();
    cin.getline(anotaciones, 1000);

    char codReserva[10];
    sprintf(codReserva, "R%03d", obtenerUltimoCodigoReserva() + 1);

    Reservacion* nueva = new Reservacion(codReserva, docH, seleccionado->getCodigo(), entrada, noches, "", monto, Fecha(), anotaciones);
    MedicionRecursos::agregarMemoria(sizeof(Reservacion));
    if (!nueva->realizarPago()) {
        cout << "Reserva cancelada.\n";
        delete nueva;
        return;
    }
    agregarReserva(nueva);
    guardarReservacionEnArchivo(*nueva);
    seleccionado->agregarFechasReservadas(seleccionado->getCodigo(), entrada, noches);
    cargarAlojamientos();

    Fecha fin = entrada.sumarDias(noches - 1);
    cout << "\n--- COMPROBANTE DE RESERVA ---\n";
    cout << "Codigo: " << codReserva << endl;
    cout << "Usuario: " << docH << endl;
    cout << "Alojamiento: " << seleccionado->getNombre() << " (" << seleccionado->getCodigo() << ")\n";
    cout << "Fecha inicio: "; entrada.imprimirFechaLarga();
    cout << "Fecha fin: "; fin.imprimirFechaLarga();
    cout << "Monto pagado: $" << monto << endl;
    cout << "------------------------------\n";
}


void UdeAStay::menuAnularReservaComoHuesped(const char* documentoHuesped) {
    const char* codigo = nullptr;
    bool tieneReservas = false;
    for (int i = 0; i < totalReservas; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(reservas[i]->getDocumentoHuesped(), documentoHuesped) == 0) {
            reservas[i]->mostrar();
            tieneReservas = true;
        }
    }
    if (!tieneReservas) {
        cout << "No tienes reservas activas.\n";
        return;
    }
    Huesped* huesped = nullptr;
    for (int i = 0; i < totalHuespedes; i++) {
        if (strcmp(huespedes[i].getDocumento(), documentoHuesped) == 0) {
            huesped = &huespedes[i];
            break;
        }
    }
    if (!huesped) {
        cout << "Huesped no encontrado.\n";
        return;
    }
    codigo = huesped->solicitarAnulacion();
    anularReserva(codigo);
}


void UdeAStay::menuAnfitrion(Anfitrion* anfitriones[], int totalAnfitriones, Reservacion* reservas[], int& totalReservas) {
    char documento[20];
    cout << "Ingrese su documento de identificacion: ";
    cin >> documento;
    if (!anfitrionExiste(documento)) {
        cout << "No estas registrado como anfitrion.\n";
        return;
    }
    Anfitrion* anfitrionActivo = nullptr;
    for (int i = 0; i < totalAnfitriones; i++) {
    MedicionRecursos::contarCiclo();
        if (strcmp(anfitriones[i]->getDocumento(), documento) == 0) {
            anfitrionActivo = anfitriones[i];
            break;
        }
    }
    if (!anfitrionActivo) {
        cout << "Anfitrion no encontrado.\n";
        return;
    }
    int opcion;
    do {
        MedicionRecursos::contarCiclo();
        cout << "\n--- MENU ANFITRION ---\n";
        cout << "1. Ver reservas activas\n";
        cout << "2. Actualizar historico de reservas\n";
        cout << "3. Anular una reservacion\n";
        cout << "4. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            anfitrionActivo->verReservas(reservas, totalReservas);
            break;
        case 2: {
            if (fechaCorteDefinida) {
                cout << "La fecha de corte actual es: ";
                fechaCorte.imprimirFechaLarga();
                cout << endl;
            } else {
                cout << "No hay una fecha de corte definida aun.\n";}

            int d, m, a;
            cout << "Ingrese nueva fecha de corte (dd mm aaaa): ";
            cin >> d >> m >> a;

            Fecha nuevaCorte(d, m, a);
            if (!nuevaCorte.validarFecha()) {
                cout << "Fecha invalida.\n";
                break;
            }
            if (fechaCorteDefinida && !fechaCorte.esMenorQue(nuevaCorte)) {
                cout << "La nueva fecha debe ser mayor que la actual.\n";
                break;
            }
            fechaCorte = nuevaCorte;
            fechaCorteDefinida = true;
            guardarFechaCorteEnArchivo();
            actualizarHistorico();
            break;
        }
        case 3: {
            char codigo[20];
            cout << "Ingrese el codigo de la reserva que desea anular: ";
            cin >> codigo;
            anularReserva(codigo);
            break;
        }
        case 4:
            cout << "Regresando al menu principal...\n";
                  system("cls");
            break;

        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}

void UdeAStay::menuHuesped(const char* documento) {
    Huesped* huesped = nullptr;
    for (int i = 0; i < totalHuespedes; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(huespedes[i].getDocumento(), documento) == 0) {
            huesped = &huespedes[i];
            break;
        }
    }
    if (!huesped) {
        cout << "Huesped no encontrado.\n";
        return;
    }
    int opcion;
    do {
        MedicionRecursos::contarCiclo();
        cout << "\n--- MENU HUESPED ---\n";
        cout << "1. Reservar alojamiento\n";
        cout << "2. Consultar reservas activas\n";
        cout << "3. Anular una reservacion\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1:
            menuReservar();
            break;
        case 2:
            huesped->consultarReservas(reservas, totalReservas);
            break;
        case 3:
            menuAnularReservaComoHuesped(documento);
            break;
        case 4:
            cout << "Saliendo del menu de huesped...\n";
            system("cls");
            break;
        default:
            cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 4);
}

void UdeAStay::menuPrincipal() {
    int opcion;
    do {
        MedicionRecursos::contarCiclo();
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Ingresar como huesped\n";
        cout << "2. Ingresar como anfitrion\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            char documento[20];
            cout << "Ingrese su documento: ";
            cin >> documento;
            if (!huespedExiste(documento)) {
                cout << "No estas registrado como huesped.\n";
                break;
            }
            cout << "Bienvenido, acceso permitido como huesped.\n";
            menuHuesped(documento);
            break;
        }
        case 2:
            menuAnfitrion(anfitriones, totalAnfitriones, reservas, totalReservas);
            break;
        case 3:
            cout << "Saliendo del sistema...\n";
            MedicionRecursos::mostrarResumen();
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 3);
}


