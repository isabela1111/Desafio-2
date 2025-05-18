#ifndef HUESPED_H
#define HUESPED_H

#include <string>
using namespace std;

class Huesped {
private:
    string documento;
    int antiguedad;
    float puntuacion;

public:
    Huesped();
    Huesped(string doc, int ant, float punt);
    // Getters
    string getDocumento() const;
    int getAntiguedad() const;
    float getPuntuacion() const;

    // Metodos
    void reservar();
    void anularReserva();
    void consultarReservas();
};

#endif
