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
    if (dia < 10) std::cout << "0";
    std::cout << dia << "/";

    if (mes < 10) std::cout << "0";
    std::cout << mes << "/";

    std::cout << anio;
}

bool Fecha::esMenorQue(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

bool Fecha::esIgualA(const Fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

Fecha& Fecha::operator=(const Fecha& otra) {
    if (this != &otra) {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    return *this;
}

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
        "enero", "febrero", "marzo", "abril", "mayo", "junio",
        "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"
    };

    if (mes >= 1 && mes <= 12) {
        std::cout << dia << " de " << nombresMes[mes - 1] << " del " << anio << std::endl;
    }
    else {
        std::cout << "Fecha inválida" << std::endl;
    }
}

Fecha Fecha::sumarDias(int dias) const {
    int d = dia, m = mes, a = anio;
    int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    while (dias > 0) {
        if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) diasMes[1] = 29;
        else diasMes[1] = 28;

        int diasRestantesMes = diasMes[m - 1] - d + 1;
        if (dias < diasRestantesMes) {
            d += dias;
            dias = 0;
        }
        else {
            dias -= diasRestantesMes;
            d = 1;
            m++;
            if (m > 12) {
                m = 1;
                a++;
            }
        }
    }

    return Fecha(d, m, a);
}

int Fecha::comparar(const Fecha& otra) const {
    if (anio < otra.anio) return -1;
    if (anio > otra.anio) return 1;
    if (mes < otra.mes) return -1;
    if (mes > otra.mes) return 1;
    if (dia < otra.dia) return -1;
    if (dia > otra.dia) return 1;
    return 0;
}
