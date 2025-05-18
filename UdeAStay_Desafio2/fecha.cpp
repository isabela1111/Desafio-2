#include "fecha.h"
#include <iostream>

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

bool Fecha::esMenorQue(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

bool Fecha::esIgualA(const Fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

// Operador de asignación
Fecha& Fecha::operator=(const Fecha& otra) {
    if (this != &otra) {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    return *this;

bool Fecha::validarFecha() const {
    if (anio < 0 || mes < 1 || mes > 12 || dia < 1)
        return false;

    int diasMes;
    if (mes == 2) {
        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
            diasMes = 29;
        else
            diasMes = 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasMes = 30;
    }
    else {
        diasMes = 31;
    }
    return dia <= diasMes;
}

void Fecha::imprimirFechaLarga() const {
    const char* nombresMes[] = {
        "enero", "febrero", "marzo", "abril", "mayo", "junio","julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"
    };

    if (mes >= 1 && mes <= 12) {
        cout << dia << " de " << nombresMes[mes - 1] << " del " << anio << endl;
    }
    else {
        cout << "Fecha inválida" << endl;
    }
}

