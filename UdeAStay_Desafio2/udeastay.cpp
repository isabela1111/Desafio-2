#include "udeastay.h"
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

    capacidadReservas = 300;
    totalReservas = 0;
    reservas = new Reservacion*[capacidadReservas];

    cargarHuespedes();
    cargarAlojamientos();
}

UdeAStay::~UdeAStay() {
    delete[] huespedes;
}
void UdeAStay::cargarHuespedes() {
    FILE* archivo = fopen("Huespedes.txt", "r");
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo huespedes.txt" << endl;
        return;
    } else {
        cout << "Archivo abierto correctamente." << endl;
    }

    char linea[256];
    int contador = 0;
    while (fgets(linea, 256, archivo)) {
        if (strlen(linea) > 1) contador++;
    }

    if (contador == 0) {
        cout << "Archivo vacío o sin líneas válidas." << endl;
        fclose(archivo);
        return;
    }

    rewind(archivo);

    huespedes = new Huesped[contador];
    totalHuespedes = 0;

    while (fgets(linea, 256, archivo)) {
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
            cout << "Línea inválida: " << doc << endl;
            continue;
        }

        huespedes[totalHuespedes] = Huesped(doc, ant, punt);
        totalHuespedes++;
    }
    fclose(archivo);
}


void UdeAStay::mostrarHuespedes() {
    for (int i = 0; i < totalHuespedes; i++) {
        cout << "Documento: " << huespedes[i].getDocumento()
        << ", Antiguedad: " << huespedes[i].getAntiguedad()
        << ", Puntuacion: " << huespedes[i].getPuntuacion()
        << endl;
    }
}


void UdeAStay::cargarAnfitriones(Anfitrion* anfitriones[], int& totalAnfitriones, int maxAnfitriones) {
    FILE* archivo = fopen("anfitriones.txt", "r");
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo anfitriones.txt.\n";
        totalAnfitriones = 0;
        return;
    }

    char linea[256];
    totalAnfitriones = 0;

    while (fgets(linea, 256, archivo) && totalAnfitriones < maxAnfitriones) {
        linea[strcspn(linea, "\n")] = '\0';

        char* documento = strtok(linea, ";");
        char* strAntiguedad = strtok(NULL, ";");
        char* strPuntuacion = strtok(NULL, ";");
        char* codigosTexto = strtok(NULL, ";");

        if (!documento || !strAntiguedad || !strPuntuacion)
            continue;

        int antiguedad = atoi(strAntiguedad);
        int puntuacion = atoi(strPuntuacion);

        int codigos[100];
        int cantidad = 0;

        if (codigosTexto && strlen(codigosTexto) > 0) {
            char* token = strtok(codigosTexto, ",");
            while (token != NULL && cantidad < 100) {
                codigos[cantidad++] = atoi(token);
                token = strtok(NULL, ",");
            }
        }

        anfitriones[totalAnfitriones] = new Anfitrion(documento, antiguedad, puntuacion, codigos, cantidad);
        totalAnfitriones++;
    }

    fclose(archivo);
}


void UdeAStay::cargarAlojamientos() {
    FILE* archivo = fopen("alojamientos.txt", "r");
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo de alojamientos.\n";
        return;
    }

    char linea[300];
    int contador = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (strlen(linea) > 1) contador++;
    }
    rewind(archivo);

    alojamientos = new Alojamiento[contador];
    totalAlojamientos = contador;

    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) && i < totalAlojamientos) {
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
        i++;
    }

    fclose(archivo);
}

void UdeAStay::mostrarAlojamientos() {
    for (int i = 0; i < totalAlojamientos; i++) {
        alojamientos[i].mostrar();
    }
}

int UdeAStay::obtenerUltimoCodigoReserva() {
    FILE* archivo = fopen("Reservaciones_activas.txt", "r");
    if (!archivo) return 0;

    char linea[256];
    int ultimo = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
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
        if (strcmp(anfitriones[i]->getDocumento(), doc) == 0)
            return anfitriones[i]->getPuntuacion();
    }
    return 0.0;
}


void UdeAStay::aplicarFiltros(const char* municipio, const Fecha& inicio, int noches, float precioMax, float puntMin) const {
    cout << "\n--- ALOJAMIENTOS DISPONIBLES ---\n";
    bool alguno = false;

    for (int i = 0; i < totalAlojamientos; i++) {
        const Alojamiento& a = alojamientos[i];
        if (strcmp(a.getMunicipio(), municipio) != 0)
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

void UdeAStay::guardarReservacionEnArchivo(const Reservacion& r) {
    FILE* archivo = fopen("Reservaciones_activas.txt", "a");
    if (!archivo) {
        cout << "No se pudo abrir reservas.txt para escribir.\n";
        return;
    }

    fprintf(archivo, "%s;%s;%s;%d/%d/%d;%d;%s;%.2f;%d/%d/%d;%s\n",
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


void UdeAStay::agregarReserva(Reservacion* nueva) {
    if (totalReservas >= capacidadReservas) {
        int nuevaCapacidad = capacidadReservas * 2;
        Reservacion** nuevoArray = new Reservacion*[nuevaCapacidad];

        for (int i = 0; i < totalReservas; i++) {
            nuevoArray[i] = reservas[i];
        }
        delete[] reservas;
        reservas = nuevoArray;
        capacidadReservas = nuevaCapacidad;
    }
    reservas[totalReservas++] = nueva;
}


void UdeAStay::menuReservar() {
    cout << "\n--- RESERVACIÓN DE ALOJAMIENTO ---\n";

    char municipio[30];
    cout << "Ingrese el municipio que desea buscar: ";
    cin >> municipio;

    int dia, mes, anio, noches;
    cout << "Ingrese la fecha de entrada (dd mm aaaa): ";
    cin >> dia >> mes >> anio;
    Fecha entrada(dia, mes, anio);

    if (!entrada.validarFecha()) {
        cout << "Fecha inválida.\n";
        return;
    }

    cout << "Cantidad de noches: ";
    cin >> noches;
    if (noches <= 0) {
        cout << "Duración invalida.\n";
        return;
    }

    float maxPrecio = 9999999;
    float minPuntuacion = 0.0;
    char usarFiltro;
    cout << "¿Desea usar filtros? (s/n): ";
    cin >> usarFiltro;

    if (usarFiltro == 's' || usarFiltro == 'S') {
        cout << "Ingrese precio maximo por noche: ";
        cin >> maxPrecio;
        cout << "Ingrese puntuacion minima del anfitrión (0.0 a 5.0): ";
        cin >> minPuntuacion;
    }

    bool encontrados = false;
    for (int i = 0; i < totalAlojamientos; i++) {
        if (strcmp(alojamientos[i].getMunicipio(), municipio) == 0 &&
            alojamientos[i].getPrecioPorNoche() <= maxPrecio &&
            obtenerPuntuacionAnfitrion(alojamientos[i].getDocumentoAnfitrion()) >= minPuntuacion &&
            alojamientos[i].disponibilidad(entrada, noches, reservas, totalReservas)) {

            alojamientos[i].mostrar();
            encontrados = true;
        }
    }

    if (!encontrados) {
        cout << "No hay alojamientos disponibles con esos filtros.\n";
        return;
    }

    char codAloj[10];
    cout << "Ingrese el código del alojamiento que desea reservar: ";
    cin >> codAloj;

    Alojamiento* seleccionado = nullptr;
    for (int i = 0; i < totalAlojamientos; i++) {
        if (strcmp(alojamientos[i].getCodigo(), codAloj) == 0) {
            seleccionado = &alojamientos[i];
            break;
        }
    }

    if (!seleccionado) {
        cout << "Alojamiento no encontrado.\n";
        return;
    }

    char docH[20];
    cout << "Ingrese su documento de identidad: ";
    cin >> docH;

    Huesped* huesped = nullptr;
    for (int i = 0; i < totalHuespedes; i++) {
        if (strcmp(huespedes[i].getDocumento(), docH) == 0) {
            huesped = &huespedes[i];
            break;
        }
    }

    if (!huesped) {
        cout << "Huesped no encontrado.\n";
        return;
    }

    if (!huesped->verificarReservas(entrada, noches, reservas, totalReservas)) {
        cout << "Ya tiene reservas en esas fechas.\n";
        return;
    }

    float monto = seleccionado->getPrecioPorNoche() * noches;
    char anotaciones[1001] = "";
    cout << "Ingrese anotaciones (opcional, sin espacios): ";
    cin >> anotaciones;

    char codReserva[10];
    sprintf(codReserva, "R%03d", obtenerUltimoCodigoReserva() + 1);

    Reservacion* nueva = new Reservacion(
        codReserva, docH, codAloj, entrada, noches,
        "", monto, Fecha(), anotaciones
        );

    if (!nueva->realizarPago()) {
        cout << "Reserva cancelada.\n";
        delete nueva;
        return;
    }

    agregarReserva(nueva);
    guardarReservacionEnArchivo(*nueva);

    Fecha fin = entrada.sumarDias(noches - 1);
    cout << "\n--- COMPROBANTE DE RESERVA ---\n";
    cout << "Código: " << codReserva << endl;
    cout << "Usuario: " << docH << endl;
    cout << "Alojamiento: " << seleccionado->getNombre() << " (" << codAloj << ")\n";
    cout << "Fecha inicio: "; entrada.imprimirFechaLarga();
    cout << "Fecha fin: "; fin.imprimirFechaLarga();
    cout << "Monto pagado: $" << monto << endl;
    cout << "------------------------------\n";
}


//Se espera que reserva .txt sea codigo; documentoHuesped; codigoAlojamiento; fechaInicio; duracionNoches; metodoPago; monto; fechaPago; anotaciones
void UdeAStay::cargarReservaciones(Reservacion* reservas[], int& totalReservas, int maxReservas) {
    FILE* archivo = fopen("reservas.txt", "r");
    if (!archivo) {
        cout << "No se pudo abrir el archivo reservas.txt\n";
        totalReservas = 0;
        return;
    }

    char linea[512];
    totalReservas = 0;

    while (fgets(linea, sizeof(linea), archivo) && totalReservas < maxReservas) {
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
        if (token) {
            strncpy(anot, token, sizeof(anot) - 1);
            anot[sizeof(anot) - 1] = '\0';
        }

        reservas[totalReservas] = new Reservacion(codRes, docH, codAloj, fechaInicio, noches, metodo, monto, fechaPago, anot);
        totalReservas++;
    }

    fclose(archivo);
    cout << totalReservas << " reservaciones cargadas correctamente.\n";
}


void UdeAStay::anularReserva(const char* codigoReservaEliminar) {
    FILE* original = fopen("reservas_activas.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    if (!original || !temp) {
        cout << "Error al abrir los archivos.\n";
        return;
    }

    char linea[1024];
    bool encontrada = false;
    char codAlojamiento[10];
    Fecha fechaInicio;
    int duracion = 0;

    while (fgets(linea, sizeof(linea), original)) {
        char copia[1024];
        strcpy(copia, linea);
        copia[strcspn(copia, "\n")] = 0;  // quitar salto de línea

        char* token = strtok(copia, ";");
        if (token && strcmp(token, codigoReservaEliminar) == 0) {
            encontrada = true;

            strtok(NULL, ";");

            token = strtok(NULL, ";");
            strcpy(codAlojamiento, token);

            token = strtok(NULL, ";");
            int d, m, a;
            sscanf(token, "%d/%d/%d", &d, &m, &a);
            fechaInicio = Fecha(d, m, a);

            token = strtok(NULL, ";");
            duracion = atoi(token);
        }
        else {
            fputs(linea, temp);
        }
    }
    fclose(original);
    fclose(temp);

    remove("reservas_activas.txt");
    rename("temp.txt", "reservas_activas.txt");
    if (encontrada) {
        for (int i = 0; i < totalReservas; i++) {
            if (strcmp(reservas[i]->getCodigo(), codigoReservaEliminar) == 0) {
                delete reservas[i];
                for (int j = i; j < totalReservas - 1; j++) {
                    reservas[j] = reservas[j + 1];
                }
                totalReservas--;
                break;
            }
        }
        cout << "Reservacion eliminada correctamente.\n";
    }
    else {
        cout << "No se encontro la reservación con ese codigo.\n";
    }
}


void UdeAStay::menuAnularReservaComoHuesped(const char* documentoHuesped) {
    const char* codigo = nullptr;
    bool tieneReservas = false;
    for (int i = 0; i < totalReservas; i++) {
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
        cout << "Huésped no encontrado.\n";
        return;
    }
    codigo = huesped->solicitarAnulacion();
    anularReserva(codigo);
}

