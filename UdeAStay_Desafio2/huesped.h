#ifndef HUESPED_H
#define HUESPED_H
#include "fecha.h"
#include "reservacion.h"

class Huesped {
private:
    char documento[20];
    int antiguedad;
    float puntuacion;

public:
    Huesped();
    Huesped(const char* doc, int ant, float punt);

    // Getters
    const char* getDocumento() const;
    int getAntiguedad() const;
    float getPuntuacion() const;

    // Métodos
    bool verificarReservas(const Fecha& inicio, int duracion, Reservacion** listaReservas, int totalReservas) const;
    const char* solicitarAnulacion();
    void consultarReservas(Reservacion** lista, int total);

};

#endif
