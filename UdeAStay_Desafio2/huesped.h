#ifndef HUESPED_H
#define HUESPED_H

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
    void reservar();
    void anularReserva();
    void consultarReservas();
};

#endif
