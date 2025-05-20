#include "huesped.h"
#include <iostream>
#include <cstring>
using namespace std;

Huesped::Huesped() {
    strcpy(documento, "");
    antiguedad = 0;
    puntuacion = 0.0;
}

Huesped::Huesped(const char* doc, int ant, float punt) {
    strcpy(documento, doc);
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
bool Huesped::verificarReservas(const Fecha& inicio, int duracion, const Reservacion* listaReservas, int totalReservas) const {
    Fecha finDeseada = inicio.sumarDias(duracion - 1);

    for (int i = 0; i < totalReservas; i++) {
        if (strcmp(listaReservas[i].getDocumentoHuesped(), documento) == 0) {
            Fecha inicioExistente = listaReservas[i].getFechaInicio();
            Fecha finExistente = inicioExistente.sumarDias(listaReservas[i].getDuracion() - 1);

            if (!(finDeseada.esMenorQue(inicioExistente) || inicio.esMenorQue(finExistente) == false)) {
                return false;
            }
        }
    }

    return true;
}


void Huesped::reservar() {
    cout << "Reservando alojamiento para huésped " << documento << endl;
}

void Huesped::solicitarAnulacion() {
    cout << "Anulando reservación para huésped " << documento << endl;
}

void Huesped::consultarReservas() {
    cout << "Consultando reservaciones activas para huésped " << documento << endl;
}

