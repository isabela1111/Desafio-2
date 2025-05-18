#include "udeastay.h"
#include "alojamiento.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

UdeAStay::UdeAStay() {
    huespedes = nullptr;
    totalHuespedes = 0;
    cargarHuespedes();
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

