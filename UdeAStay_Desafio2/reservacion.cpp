#include "reservacion.h"
#include <cstring>
#include <iostream>

using namespace std;

Reservacion::Reservacion() {
    strncpy(codigo, "", sizeof(codigo) - 1); codigo[sizeof(codigo) - 1] = '\0';
    strncpy(documentoHuesped, "", sizeof(documentoHuesped) - 1); documentoHuesped[sizeof(documentoHuesped) - 1] = '\0';
    strncpy(codigoAlojamiento, "", sizeof(codigoAlojamiento) - 1); codigoAlojamiento[sizeof(codigoAlojamiento) - 1] = '\0';
    fechaInicio = Fecha();
    duracionNoches = 0;
    strncpy(metodoPago, "", sizeof(metodoPago) - 1); metodoPago[sizeof(metodoPago) - 1] = '\0';
    monto = 0.0f;
    fechaPago = Fecha();
    strncpy(anotaciones, "", sizeof(anotaciones) - 1); anotaciones[sizeof(anotaciones) - 1] = '\0';
}

Reservacion::Reservacion(const char* codRes, const char* docH, const char* codAloj,
                         Fecha inicio, int noches, const char* metodo, float m, Fecha fPago, const char* nota) {
    strncpy(codigo, codRes, sizeof(codigo) - 1); codigo[sizeof(codigo) - 1] = '\0';
    strncpy(documentoHuesped, docH, sizeof(documentoHuesped) - 1); documentoHuesped[sizeof(documentoHuesped) - 1] = '\0';
    strncpy(codigoAlojamiento, codAloj, sizeof(codigoAlojamiento) - 1); codigoAlojamiento[sizeof(codigoAlojamiento) - 1] = '\0';
    fechaInicio = inicio;
    duracionNoches = noches;
    strncpy(metodoPago, metodo, sizeof(metodoPago) - 1); metodoPago[sizeof(metodoPago) - 1] = '\0';
    monto = m;
    fechaPago = fPago;
    strncpy(anotaciones, nota, sizeof(anotaciones) - 1); anotaciones[sizeof(anotaciones) - 1] = '\0';
}

// Getters
const char* Reservacion::getCodigo() const { return codigo; }
const char* Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
const char* Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
Fecha Reservacion::getFechaInicio() const { return fechaInicio; }
int Reservacion::getDuracion() const { return duracionNoches; }
const char* Reservacion::getMetodoPago() const { return metodoPago; }
float Reservacion::getMonto() const { return monto; }
Fecha Reservacion::getFechaPago() const { return fechaPago; }
const char* Reservacion::getAnotaciones() const { return anotaciones; }

void Reservacion::mostrar() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Huesped: " << documentoHuesped << " - Alojamiento: " << codigoAlojamiento << endl;
    cout << "Fecha de inicio: ";
    fechaInicio.imprimirFechaLarga();
    cout << "Duracion: " << duracionNoches << " noches" << endl;
    cout << "Metodo de pago: " << metodoPago << " - Monto: $" << monto << endl;
    cout << "Fecha de pago: ";
    fechaPago.imprimirFechaLarga();
    if (strlen(anotaciones) > 0) {
        cout << "Notas: " << anotaciones << endl;
    }
    cout << "------------------------" << endl;
}

bool Reservacion::activa(const Fecha& fechaCorte) const {
    Fecha fin = fechaInicio.sumarDias(duracionNoches);
    return fin.comparar(fechaCorte) >= 0;
}

bool Reservacion::realizarPago() {
    char respuesta[5];
    cout << "¿Desea pagar ahora? (si/no): ";
    cin >> respuesta;

    if (strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0) {
        cout << "Monto total a pagar: $" << monto << endl;

        int opcion;
        cout << "Seleccione el metodo de pago:\n";
        cout << "1. PSE\n";
        cout << "2. Tarjeta\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            strncpy(metodoPago, "PSE", sizeof(metodoPago) - 1);
            metodoPago[sizeof(metodoPago) - 1] = '\0';
        }
        else if (opcion == 2) {
            strncpy(metodoPago, "Tarjeta", sizeof(metodoPago) - 1);
            metodoPago[sizeof(metodoPago) - 1] = '\0';
        }
        else {
            cout << "Metodo invalido. No se registro el pago.\n";
            return false;
        }

        int d, m, a;
        cout << "Ingrese la fecha de pago (dd mm aaaa): ";
        cin >> d >> m >> a;
        fechaPago = Fecha(d, m, a);

        if (!fechaPago.validarFecha()) {
            cout << "Fecha invalida. No se registro el pago.\n";
            return false;
        }

        if (monto <= 0) {
            cout << "Monto invalido. No se puede pagar.\n";
            return false;
        }
        cout << "Pago registrado correctamente el ";
        fechaPago.imprimirFechaLarga();
        cout << " con metodo: " << metodoPago << endl;
        return true;
    }
    cout << "Pago pendiente.\n";
    return false;
}





