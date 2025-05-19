#ifndef PAGO_H
#define PAGO_H

#include "fecha.h"

class Pago {
private:
    char metodo[10];      // "PSE" o "TCredito"
    Fecha fechaPago;
    float monto;

public:
    Pago();
    Pago(const char* metodoPago, const Fecha& fecha, float monto);

    // Getters
    const char* getMetodo() const;
    Fecha getFechaPago() const;
    float getMonto() const;

    // Setters
    void setMetodo(const char* metodoPago);
    void setFechaPago(const Fecha& fecha);
    void setMonto(float monto);

    void mostrarPago() const;
};

#endif // PAGO_H
