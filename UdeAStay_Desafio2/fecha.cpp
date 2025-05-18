#include "fecha.h"
#include <iostream>

using namespace std;

Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}


int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }

void Fecha::mostrar() const {
    cout << (dia < 10 ? "0" : "") << dia << "/"
         << (mes < 10 ? "0" : "") << mes << "/"
         << anio;
}

// Valida si la fecha es valida
bool Fecha::esValida() const {
    if (anio < 1900 || mes < 1 || mes > 12 || dia < 1) return false;

    int diasPorMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0); //aqui verifica si el año en el que estamos culpe para ser bisiesto y que se pueda escribir 29/2

    if (mes == 2 && bisiesto)
        return dia <= 29;
    else
        return dia <= diasPorMes[mes - 1];
}

// Comparar si es menor que otra fecha
bool Fecha::esMenorQue(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

// Comparar igualdad
bool Fecha::esIgualA(const Fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

// Verifica si esta fecha está dentro de los próximos 12 meses desde otra
bool Fecha::estaEnRango12Meses(const Fecha& actual) const {
    int diffAnios = anio - actual.anio;
    int diffMeses = mes - actual.mes + diffAnios * 12;

    if (diffMeses < 0 || diffMeses > 12)
        return false;
    if (diffMeses == 12 && dia > actual.dia)
        return false;

    return !esMenorQue(actual);
}

// Operador de asignación
Fecha& Fecha::operator=(const Fecha& otra) {
    if (this != &otra) {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    return *this;
}

