#include "huesped.h"
#include "medicionrecursos.h"
#include <iostream>
#include <cstring>
using namespace std;

Huesped::Huesped() {
    strncpy(documento, "", sizeof(documento) - 1);
    documento[sizeof(documento) - 1] = '\0';
    antiguedad = 0;
    puntuacion = 0.0;
}

Huesped::Huesped(const char* doc, int ant, float punt) {
    strncpy(documento, doc, sizeof(documento) - 1);
    documento[sizeof(documento) - 1] = '\0';
    antiguedad = ant;
    puntuacion = punt;
}

const char* Huesped::getDocumento() const {
    return documento;
}
int Huesped::getAntiguedad() const {
    return antiguedad;
}
float Huesped::getPuntuacion() const {
    return puntuacion;
}

bool Huesped::verificarReservas(const Fecha& inicio, int duracion, Reservacion** listaReservas, int totalReservas) const {
    Fecha finDeseada = inicio.sumarDias(duracion - 1);

    for (int i = 0; i < totalReservas; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(listaReservas[i]->getDocumentoHuesped(), documento) == 0) {
            Fecha inicioExistente = listaReservas[i]->getFechaInicio();
            Fecha finExistente = inicioExistente.sumarDias(listaReservas[i]->getDuracion() - 1);

            bool noSeSolapan = finDeseada.esMenorQue(inicioExistente) || finExistente.esMenorQue(inicio);
            if (!noSeSolapan) {
                return false;
            }
        }
    }
    return true;
}


const char* Huesped::solicitarAnulacion() {
    static char codigo[10];
    cout << "Ingrese el codigo de la reservacion a anular: ";
    cin >> codigo;
    return codigo;
}

void Huesped::consultarReservas(Reservacion** lista, int total){
    cout << "\nReservas activas del huesped " << documento << ":\n";
    bool hayReservas = false;

    for (int i = 0; i < total; i++) {
        MedicionRecursos::contarCiclo();
        if (strcmp(lista[i]->getDocumentoHuesped(), documento) == 0) {
            lista[i]->mostrar();
            hayReservas = true;
        }
    }
    if (!hayReservas) {
        cout << "No tiene reservas activas.\n";
    }
}

