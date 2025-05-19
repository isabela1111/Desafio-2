#include "pago.h"
#include <iostream>
#include <cstring>

using namespace std;

Pago::Pago() {
    metodo[0] = '\0';
    monto = 0.0f;
}


Pago::Pago(const char* metodoPago, const Fecha& fecha, float monto) {
    strncpy(metodo, metodoPago, 9);
    metodo[9] = '\0';
    fechaPago = fecha;
    this->monto = monto;
}

// Getters
const char* Pago::getMetodo() const {
    return metodo;
}

Fecha Pago::getFechaPago() const {
    return fechaPago;
}

float Pago::getMonto() const {
    return monto;
}

// Setters
void Pago::setMetodo(const char* metodoPago) {
    strncpy(metodo, metodoPago, 9);
    metodo[9] = '\0';
}

void Pago::setFechaPago(const Fecha& fecha) {
    fechaPago = fecha;
}

void Pago::setMonto(float monto) {
    this->monto = monto;
}

// Se muestra información del pago
void Pago::mostrarPago() const {
    cout << "Método de pago: " << metodo << endl;
    cout << "Fecha del pago: ";
    fechaPago.imprimirFechaLarga();
    cout << "Monto pagado: $" << monto << endl;
}
