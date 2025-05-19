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
    pago = Pago(); //Se reemplazan unas lineas para que incluirse la clase pago
    
    strncpy(anotaciones, "", sizeof(anotaciones) - 1); 
    anotaciones[sizeof(anotaciones) - 1] = '\0';
}

Reservacion::Reservacion(const char* codRes, const char* docH, const char* codAloj,
                         Fecha inicio, int noches, const Pago& p, const char* nota) {
    strncpy(codigo, codRes, sizeof(codigo) - 1); codigo[sizeof(codigo) - 1] = '\0';
    strncpy(documentoHuesped, docH, sizeof(documentoHuesped) - 1); documentoHuesped[sizeof(documentoHuesped) - 1] = '\0';
    strncpy(codigoAlojamiento, codAloj, sizeof(codigoAlojamiento) - 1); codigoAlojamiento[sizeof(codigoAlojamiento) - 1] = '\0';
    fechaInicio = inicio;
    duracionNoches = noches;
    pago = p;
    strncpy(anotaciones, nota, sizeof(anotaciones) - 1); anotaciones[sizeof(anotaciones) - 1] = '\0';
}

const char* Reservacion::getCodigo() const { return codigo; }
const char* Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
const char* Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
Fecha Reservacion::getFechaInicio() const { return fechaInicio; }
int Reservacion::getDuracion() const { return duracionNoches; }
Pago Reservacion::getPago() const { return pago; }
const char* Reservacion::getAnotaciones() const { return anotaciones; }

void Reservacion::mostrar() const {
    cout << "Código: " << codigo << endl;
    cout << "Huésped: " << documentoHuesped << " - Alojamiento: " << codigoAlojamiento << endl;
    cout << "Fecha de inicio: ";
    fechaInicio.imprimirFechaLarga();
    cout << "Duración: " << duracionNoches << " noches" << endl;
    cout << "Pago:\n";
    pago.mostrarPago();
    if (strlen(anotaciones) > 0) {
        cout << "Notas: " << anotaciones << endl;
    }
    cout << "------------------------" << endl;
}

bool Reservacion::activa(const Fecha& fechaCorte) const {
    Fecha fin = fechaInicio.sumarDias(duracionNoches);
    return fin.comparar(fechaCorte) >= 0;
}




