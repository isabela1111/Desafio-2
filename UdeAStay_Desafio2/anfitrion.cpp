#include "anfitrion.h"
#include "medicionrecursos.h"
#include "reservacion.h"
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

Anfitrion::Anfitrion() {
    documento = new char[1];
    MedicionRecursos::agregarMemoria(1);
    documento[0] = '\0';
    antiguedad = 0;
    puntuacion = 0;
    codigosAlojamientos = nullptr;
    numAlojamientos = 0;
}

Anfitrion::Anfitrion(const char* doc, int ant, float punt, int* cods, int numCods) {
    documento = new char[strlen(doc) + 1];
    MedicionRecursos::agregarMemoria(strlen(doc) + 1);
    strcpy(documento, doc);
    antiguedad = ant;
    puntuacion = punt;
    numAlojamientos = numCods;

    if (numAlojamientos > 0) {
        codigosAlojamientos = new int[numAlojamientos];
        MedicionRecursos::agregarMemoria(numAlojamientos*sizeof(int));
        for (int i = 0; i < numAlojamientos; i++) {
            MedicionRecursos::contarCiclo();
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
const char* Anfitrion::getDocumento() const {
    return documento;
}

float Anfitrion::getPuntuacion() const {
    return puntuacion;
}

int Anfitrion::getNumAlojamientos() const {
    return numAlojamientos;
}

int* Anfitrion::getCodigosAlojamientos() const {
    return codigosAlojamientos;
}

void Anfitrion::verReservas(Reservacion* reservas[], int totalReservas) const {
    cout << "Reservas activas para el anfitrion con documento: " << documento << endl;
    bool encontrada = false;

    for (int i = 0; i < totalReservas; i++) {
        MedicionRecursos::contarCiclo();
        const char* codReserva = reservas[i]->getCodigoAlojamiento();
        for (int j = 0; j < numAlojamientos; j++) {
            MedicionRecursos::contarCiclo();
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
