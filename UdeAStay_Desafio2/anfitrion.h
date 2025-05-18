#ifndef ANFITRION_H
#define ANFITRION_H

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

    //Funciones en desarrollo
    void verReservas();         
    void actualizarHistorico();
};

#endif // ANFITRION_H
