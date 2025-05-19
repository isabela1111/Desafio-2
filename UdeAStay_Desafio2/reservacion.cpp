#include "reservacion.h"
#include <cstring>
#include <iostream>
using namespace std;

Reservacion::Reservacion() {
    strncpy(codigo, "", sizeof(codigo) - 1);
    codigo[sizeof(codigo) - 1] = '\0';

    strncpy(documentoHuesped, "", sizeof(documentoHuesped) - 1);
    documentoHuesped[sizeof(documentoHuesped) - 1] = '\0';

    strncpy(codigoAlojamiento, "", sizeof(codigoAlojamiento) - 1);
    codigoAlojamiento[sizeof(codigoAlojamiento) - 1] = '\0';

    fechaInicio = Fecha();
    duracionNoches = 0;

    strncpy(metodoPago, "", sizeof(metodoPago) - 1);
    metodoPago[sizeof(metodoPago) - 1] = '\0';
    monto = 0.0;

    strncpy(anotaciones, "", sizeof(anotaciones) - 1);
    anotaciones[sizeof(anotaciones) - 1] = '\0';
}

Reservacion::Reservacion(const char* codRes, const char* docH, const char* codAloj,Fecha inicio, int noches, const char* metodo,
                         float m, const char* nota) {

    strncpy(codigo, codRes, sizeof(codigo) - 1); codigo[sizeof(codigo) - 1] = '\0';
    strncpy(documentoHuesped, docH, sizeof(documentoHuesped) - 1); documentoHuesped[sizeof(documentoHuesped) - 1] = '\0';
    strncpy(codigoAlojamiento, codAloj, sizeof(codigoAlojamiento) - 1); codigoAlojamiento[sizeof(codigoAlojamiento) - 1] = '\0';
    fechaInicio = inicio;
    duracionNoches = noches;
    strncpy(metodoPago, metodo, sizeof(metodoPago) - 1); metodoPago[sizeof(metodoPago) - 1] = '\0';
    monto = m;
    strncpy(anotaciones, nota, sizeof(anotaciones) - 1); anotaciones[sizeof(anotaciones) - 1] = '\0';
}

const char* Reservacion::getCodigo() const { return codigo; }
const char* Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
const char* Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
Fecha Reservacion::getFechaInicio() const { return fechaInicio; }
int Reservacion::getDuracion() const { return duracionNoches; }
const char* Reservacion::getMetodoPago() const { return metodoPago; }
float Reservacion::getMonto() const { return monto; }
const char* Reservacion::getAnotaciones() const { return anotaciones; }

void Reservacion::mostrar() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Huesped: " << documentoHuesped << " - Alojamiento: " << codigoAlojamiento << endl;
    cout << "Fecha de inicio: "; fechaInicio.imprimirFechaLarga();
    cout << "Duracion: " << duracionNoches << " noches" << endl;
    cout << "Pago: " << metodoPago << " - Monto: $" << monto << endl;
    if (strlen(anotaciones) > 0) {
        cout << "Notas: " << anotaciones << endl;
    }
    cout << "------------------------" << endl;
}

bool Reservacion::activa(const Fecha& fechaCorte) const {
    Fecha fin = fechaInicio.sumarDias(duracionNoches);
    return fin.comparar(fechaCorte) >= 0;
}
