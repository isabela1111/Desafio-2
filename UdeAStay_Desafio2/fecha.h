#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha();
    Fecha(int d, int m, int a);

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    // Funciones de utilidad
    bool esValida() const;
    bool estaEnRango12Meses(const Fecha& actual) const;
    bool esMenorQue(const Fecha& otra) const;
    bool esIgualA(const Fecha& otra) const;
    void mostrar() const;

    
    Fecha& operator=(const Fecha& otra);
};

#endif 
