#ifndef PAGO_H
#define PAGO_H
#include "fecha.h"
#include <string>
using namespace std;

class Pago {
private:
    string metodo;
    Fecha fechaPago;
    float monto;

public:
    Pago();
    Pago(string metodo, Fecha fechaPago, float monto);

    // Getters
    string getMetodo() const;
    Fecha getFechaPago() const;
    float getMonto() const;
    // Setters
    void setMetodo(string metodo);
    void setFechaPago(Fecha fechaPago);
    void setMonto(float monto);

    void mostrar() const;
};

#endif // PAGO_H
