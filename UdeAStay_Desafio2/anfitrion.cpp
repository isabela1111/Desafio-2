#include "anfitrion.h"
#include "reservacion.h"
#include <cstring>
#include <iostream>

using namespace std;

Anfitrion::Anfitrion() {
    documento = new char[1];
    documento[0] = '\0';
    antiguedad = 0;
    puntuacion = 0;
    codigosAlojamientos = nullptr;
    numAlojamientos = 0;
}

Anfitrion::Anfitrion(const char* doc, int ant, int punt, int* cods, int numCods) {
    documento = new char[strlen(doc) + 1];
    strcpy(documento, doc);
    antiguedad = ant;
    puntuacion = punt;
    numAlojamientos = numCods;

    if (numAlojamientos > 0) {
        codigosAlojamientos = new int[numAlojamientos];
        for (int i = 0; i < numAlojamientos; i++) {
            codigosAlojamientos[i] = cods[i];
        }
    } else {
        codigosAlojamientos = nullptr;
    }
}

Anfitrion::~Anfitrion() {
    delete[] documento;
    delete[] codigosAlojamientos;
}


//Esta funcion solo se uso de prueba para comprobar que el programara leyera correctamente la informacion del .txt, se borrara en un commit despues
/*
void Anfitrion::mostrarInfo() const {
    cout << "Documento: " << documento << endl;
    cout << "Antigüedad: " << antiguedad << " meses" << endl;
    cout << "Puntuación: " << puntuacion << "/5" << endl;
    cout << "Alojamientos: ";
    if (numAlojamientos == 0) {
        cout << "Ninguno";
    } else {
        for (int i = 0; i < numAlojamientos; i++) {
            cout << codigosAlojamientos[i];
            if (i < numAlojamientos - 1)
                cout << ", ";
        }
    }
    cout << "\n-----------------------------\n";
}*/

void Anfitrion::verReservas(Reservacion* reservas[], int totalReservas) const {
    cout << "Reservas activas para el anfitrión con documento: " << documento << endl;
    bool encontrada = false;

    for (int i = 0; i < totalReservas; i++) {
        const char* codReserva = reservas[i]->getCodigoAlojamiento();

        // Comparar contra todos los alojamientos del anfitrión
        for (int j = 0; j < numAlojamientos; j++) {
            char buffer[10];
            sprintf(buffer, "%d", codigosAlojamientos[j]);

            if (strcmp(codReserva, buffer) == 0) {
                reservas[i]->mostrar();
                encontrada = true;
                break;
            }
        }
    }

    if (!encontrada) {
        cout << "No se encontraron reservaciones para sus alojamientos.\n";
    }
}

void Anfitrion::actualizarHistorico() {
    /* Debería recorrer las reservaciones activas y mover aquellas con fecha final anterior
       a la fecha de corte indicada por el usuario, hacia un archivo histórico.

       Posible firma futura:
       void actualizarHistorico(Reservacion* reservaciones[], int& numReservas, const Fecha& corte);
    */
}
