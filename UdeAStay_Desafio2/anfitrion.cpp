#include "anfitrion.h"
#include <iostream>
#include <cstring>

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

void Anfitrion::verReservas() {
    /* Aun está pendiente su desarrollo. Esta función debería recorrer todas las reservaciones 
       activas del sistema y filtrar aquellas cuyo alojamiento esté asociado al anfitrión actual.

       Posible firma futura:
       void verReservas(Reservacion* reservaciones[], int cantidad);
    */
}

void Anfitrion::actualizarHistorico() {
    /* Debería recorrer las reservaciones activas y mover aquellas con fecha final anterior
       a la fecha de corte indicada por el usuario, hacia un archivo histórico.

       Posible firma futura:
       void actualizarHistorico(Reservacion* reservaciones[], int& numReservas, const Fecha& corte);
    */
}
