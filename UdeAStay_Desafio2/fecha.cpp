#include "fecha.h"
#include "iostream"
using namespace std;

Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }


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
