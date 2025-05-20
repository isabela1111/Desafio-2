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

void Huesped::reservar() {
    cout << "Reservando alojamiento para huésped " << documento << endl;
}

void Huesped::anularReserva() {
    cout << "Anulando reservación para huésped " << documento << endl;
}

void Huesped::consultarReservas() {
    cout << "Consultando reservaciones activas para huésped " << documento << endl;
}

