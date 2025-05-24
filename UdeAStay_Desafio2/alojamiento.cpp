#include "alojamiento.h"
#include <cstring>
#include <iostream>
using namespace std;

Alojamiento::Alojamiento() {
    strncpy(codigo, "", sizeof(codigo) - 1);
    codigo[sizeof(codigo) - 1] = '\0';

    strncpy(nombre, "", sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';

    strncpy(documentoAnfitrion, "", sizeof(documentoAnfitrion) - 1);
    documentoAnfitrion[sizeof(documentoAnfitrion) - 1] = '\0';

    strncpy(departamento, "", sizeof(departamento) - 1);
    departamento[sizeof(departamento) - 1] = '\0';

    strncpy(municipio, "", sizeof(municipio) - 1);
    municipio[sizeof(municipio) - 1] = '\0';

    strncpy(tipo, "", sizeof(tipo) - 1);
    tipo[sizeof(tipo) - 1] = '\0';

    strncpy(direccion, "", sizeof(direccion) - 1);
    direccion[sizeof(direccion) - 1] = '\0';

    precioNoche = 0.0;

    strncpy(amenidades, "", sizeof(amenidades) - 1);
    amenidades[sizeof(amenidades) - 1] = '\0';

    strncpy(fechasReservadas, "", sizeof(fechasReservadas) - 1);
    fechasReservadas[sizeof(fechasReservadas) - 1] = '\0';
}

Alojamiento::Alojamiento(const char* cod, const char* nom, const char* docAnf, const char* depto, const char* muni, const char* t,
                         const char* dir, float precio,const char* amen, const char* fechas) {

    strncpy(codigo, cod, sizeof(codigo) - 1);
    codigo[sizeof(codigo) - 1] = '\0';

    strncpy(nombre, nom, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';

    strncpy(documentoAnfitrion, docAnf, sizeof(documentoAnfitrion) - 1);
    documentoAnfitrion[sizeof(documentoAnfitrion) - 1] = '\0';

    strncpy(departamento, depto, sizeof(departamento) - 1);
    departamento[sizeof(departamento) - 1] = '\0';

    strncpy(municipio, muni, sizeof(municipio) - 1);
    municipio[sizeof(municipio) - 1] = '\0';

    strncpy(tipo, t, sizeof(tipo) - 1);
    tipo[sizeof(tipo) - 1] = '\0';

    strncpy(direccion, dir, sizeof(direccion) - 1);
    direccion[sizeof(direccion) - 1] = '\0';

    precioNoche = precio;

    strncpy(amenidades, amen, sizeof(amenidades) - 1);
    amenidades[sizeof(amenidades) - 1] = '\0';

    strncpy(fechasReservadas, fechas, sizeof(fechasReservadas) - 1);
    fechasReservadas[sizeof(fechasReservadas) - 1] = '\0';
}

const char* Alojamiento::getCodigo() const {
    return codigo;
}
const char* Alojamiento::getNombre() const {
    return nombre;
}
const char* Alojamiento::getMunicipio() const {
    return municipio;
}
const char* Alojamiento::getDocumentoAnfitrion() const {
    return documentoAnfitrion;
}
float Alojamiento::getPrecioPorNoche() const {
    return precioNoche;
}

void Alojamiento::mostrar() const {
    cout << "Codigo: " << codigo << " - " << nombre << endl;
    cout << "Tipo: " << tipo << " - Direccion: " << direccion << endl;
    cout << "Municipio: " << municipio << " (" << departamento << ")" << endl;
    cout << "Precio por noche: $" << precioNoche << endl;
    cout << "Amenidades: " << amenidades << endl;
    if (strlen(fechasReservadas) > 0) {
        cout << "Fechas reservadas: " << fechasReservadas << endl;
    }
    else {
        cout << "Sin fechas reservadas." << endl;
        }
    cout << "--------------------------" << endl;
}

bool Alojamiento::disponibilidad(const Fecha& nuevaEntrada, int duracion, Reservacion** reservas, int cantidadReservas) const {
    for (int i = 0; i < duracion; i++) {
        Fecha dia = nuevaEntrada.sumarDias(i);
        if (fechaOcupada(dia)) {
            return false;
        }
    }
    for (int i = 0; i < cantidadReservas; i++) {
        Reservacion* res = reservas[i];

        if (strcmp(res->getCodigoAlojamiento(), codigo) == 0) {
            Fecha resInicio = res->getFechaInicio();
            Fecha resSalida = resInicio.sumarDias(res->getDuracion() - 1);
            Fecha nuevaSalida = nuevaEntrada.sumarDias(duracion - 1);

            bool noSeSolapan = nuevaSalida.esMenorQue(resInicio) || resSalida.esMenorQue(nuevaEntrada);
            if (!noSeSolapan) {
                return false;
            }
        }
    }
    return true;
}


void Alojamiento::actualizarFechasAlojamiento(const char* cod, const Fecha& inicio, int duracion) {
    FILE* in = fopen("Alojamientos.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    if (!in || !temp) {
        cout << "Error al abrir los archivos de alojamiento.\n";
        return;
    }
    char linea[1024];
    char fechasAEliminar[12][15];

    for (int i = 0; i < duracion; i++) {
        Fecha f = inicio.sumarDias(i);
        sprintf(fechasAEliminar[i], "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());
    }

    while (fgets(linea, sizeof(linea), in)) {
        char copia[1024];
        strcpy(copia, linea);
        copia[strcspn(copia, "\n")] = 0;

        char campos[10][256];
        int count = 0;

        char* token = strtok(copia, ";");
        while (token != NULL && count < 10) {
            strcpy(campos[count++], token);
            token = strtok(NULL, ";");
        }
        if (count == 10 && strcmp(campos[0], cod) == 0) {
            char* fechaToken = strtok(campos[9], ",");
            char nuevasFechas[512] = "";
            bool primera = true;

            while (fechaToken) {
                bool eliminar = false;
                for (int i = 0; i < duracion; i++) {
                    if (strcmp(fechaToken, fechasAEliminar[i]) == 0) {
                        eliminar = true;
                        break;
                    }
                }
                if (!eliminar) {
                    if (!primera) strcat(nuevasFechas, ",");
                    strcat(nuevasFechas, fechaToken);
                    primera = false;
                }

                fechaToken = strtok(NULL, ",");
            }
            for (int i = 0; i < 9; i++) {
                fprintf(temp, "%s;", campos[i]);
            }
            fprintf(temp, "%s\n", nuevasFechas);
        }
        else {
            fputs(linea, temp);
        }
    }
    fclose(in);
    fclose(temp);
    remove("Alojamientos.txt");
    rename("temp.txt", "Alojamientos.txt");
}

void Alojamiento::agregarFechasReservadas(const char* cod, const Fecha& inicio, int duracion) {
    FILE* in = fopen("Alojamientos.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    if (!in || !temp) {
        cout << "Error al abrir los archivos de alojamiento.\n";
        return;
    }
    char linea[1024];
    char nuevasFechas[512];

    while (fgets(linea, sizeof(linea), in)) {
        char copia[1024];
        strcpy(copia, linea);
        copia[strcspn(copia, "\n")] = 0;

        char campos[10][256] = {};
        int count = 0;
        char* token = strtok(copia, ";");
        while (token && count < 10) {
            strncpy(campos[count], token, sizeof(campos[count]) - 1);
            campos[count][sizeof(campos[count]) - 1] = '\0';
            count++;
            token = strtok(NULL, ";");
        }

        if (count == 10 && strcmp(campos[0], cod) == 0) {
            if (strlen(campos[9]) > 0) {
                strncpy(nuevasFechas, campos[9], sizeof(nuevasFechas));
            } else {
                nuevasFechas[0] = '\0';
            }

            for (int i = 0; i < duracion; i++) {
                Fecha f = inicio.sumarDias(i);
                char fechaStr[15];
                sprintf(fechaStr, "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());

                if (strlen(nuevasFechas) > 0) strcat(nuevasFechas, ",");
                strcat(nuevasFechas, fechaStr);
            }

            for (int i = 0; i < 9; i++) {
                fprintf(temp, "%s;", campos[i]);
            }
            fprintf(temp, "%s\n", nuevasFechas);
        } else {
            fputs(linea, temp);
        }
    }
    fclose(in);
    fclose(temp);
    remove("Alojamientos.txt");
    rename("temp.txt", "Alojamientos.txt");
}

bool Alojamiento::fechaOcupada(const Fecha& f) const {
    char buscada[12];
    sprintf(buscada, "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());

    char copia[1024];
    strncpy(copia, fechasReservadas, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    char* token = strtok(copia, ",");
    while (token != NULL) {
        if (strcmp(token, buscada) == 0) {
            return true;
        }
        token = strtok(NULL, ",");
    }
    return false;
}

