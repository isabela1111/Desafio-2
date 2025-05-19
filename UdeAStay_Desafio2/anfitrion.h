#ifndef ANFITRION_H
#define ANFITRION_H
#include "reservacion.h"

class Anfitrion {
private:
    char* documento;
    int antiguedad;
    int puntuacion;
    int* codigosAlojamientos;
    int numAlojamientos;

public:
    Anfitrion();
    Anfitrion(const char* doc, int ant, int punt, int* cods, int numCods);
    ~Anfitrion();

    //Funcion de prueba
    //void mostrarInfo() const;

    void verReservas(Reservacion* reservas[], int totalReservas) const;       
    void actualizarHistorico(Reservacion* reservas[], int& totalReservas, const Fecha& fechaCorte);

};

#endif 
