#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha(int d = 1, int m = 1, int a = 2000);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    bool esMenorQue(const Fecha& otra) const;
    Fecha& operator=(const Fecha& otra);
    bool validarFecha() const;
    void imprimirFechaLarga() const;
    Fecha sumarDias(int dias) const;
    int comparar(const Fecha& otra) const;
};

#endif
