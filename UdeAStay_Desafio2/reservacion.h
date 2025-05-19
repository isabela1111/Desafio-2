#ifndef RESERVACION_H
#define RESERVACION_H

#include "fecha.h"
#include "pago.h"

class Reservacion {
private:
    char codigo[15];
    char documentoHuesped[20];
    char codigoAlojamiento[10];
    Fecha fechaInicio;
    int duracionNoches;
    Pago pago; 
    char anotaciones[1001];

public:
    Reservacion();
    Reservacion(const char* codRes, const char* docH, const char* codAloj,
                Fecha inicio, int noches, const Pago& pago, const char* nota);

    const char* getCodigo() const;
    const char* getDocumentoHuesped() const;
    const char* getCodigoAlojamiento() const;
    Fecha getFechaInicio() const;
    int getDuracion() const;
    Pago getPago() const;
    const char* getAnotaciones() const;

    void mostrar() const;
    bool activa(const Fecha& fechaCorte) const;
};

#endif
