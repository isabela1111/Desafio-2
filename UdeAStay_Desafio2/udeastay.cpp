#include "udeastay.h"
#include <fstream>
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
    ifstream archivo("Huespedes.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo huespedes.txt" << endl;
        return;
    }
    else {
        cout << "Archivo abierto correctamente." << endl;
    }
    char linea[256];
    int contador = 0;

    while (archivo.getline(linea, 256)) {
        if (linea[0] != '\0') contador++;
    }
    archivo.clear();
    archivo.seekg(0);

    huespedes = new Huesped[contador];
    totalHuespedes = contador;

    int i = 0;
    while (archivo.getline(linea, 256)) {
        if (linea[0] == '\0') continue;

        char doc[50];
        char antStr[10];
        char puntStr[10];

        int pos1 = 0, pos2 = 0;
        int j = 0;
        while (linea[j] != '\0') {
            if (linea[j] == ';') {
                if (pos1 == 0) pos1 = j;
                else {
                    pos2 = j;
                    break;
                }
            }
            j++;
        }

        for (int j = 0; j < pos1; j++) {
            doc[j] = linea[j];
        }
        doc[pos1] = '\0';

        int k = 0;
        for (int j = pos1 + 1; j < pos2; j++) {
            antStr[k++] = linea[j];
        }
        antStr[k] = '\0';

        k = 0;
        for (int j = pos2 + 1; linea[j] != '\0'; j++) {
            puntStr[k++] = linea[j];
        }
        puntStr[k] = '\0';

        int ant = atoi(antStr);
        float punt = atof(puntStr);

        if (ant < 0) {
            cout << "Error: antiguedad invalida (" << ant << ") para el huesped con documento " << doc << ". Linea omitida." << endl;
            continue;
        }

        if (punt < 0.0f || punt > 5.0f) {
            cout << "Error puntuacion invalida (" << punt << ") para el huesped con documento " << doc << ". Linea omitida." << endl;
            continue;
        }
        huespedes[i] = Huesped(doc, ant, punt);
        i++;
    }

    archivo.close();
}

void UdeAStay::mostrarHuespedes() {
    for (int i = 0; i < totalHuespedes; i++) {
        cout << "Documento: " << huespedes[i].getDocumento()
        << ", Antigedad: " << huespedes[i].getAntiguedad()
        << ", Puntuacion: " << huespedes[i].getPuntuacion()
        << endl;
    }
}

