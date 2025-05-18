#include "huesped.h"
#include <iostream>
using namespace std;

Huesped::Huesped() {
    documento = "";
    antiguedad = 0;
    puntuacion = 0.0;
}

Huesped::Huesped(string doc, int ant, float punt) {
    documento = doc;
    antiguedad = ant;
    puntuacion = punt;
}

string Huesped::getDocumento() const {
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
