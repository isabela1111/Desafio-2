#include "alojamiento.h"
#include <cstring>
#include <iostream>
using namespace std;

Alojamiento::Alojamiento() {
    strncpy(codigo, "", sizeof(codigo) - 1);
    codigo[sizeof(codigo) - 1] = '\0';

    strncpy(nombre, "", sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';

    strncpy(documentoAnfitrion, "", sizeof(documentoAnfitrion) - 1);
    documentoAnfitrion[sizeof(documentoAnfitrion) - 1] = '\0';

    strncpy(departamento, "", sizeof(departamento) - 1);
    departamento[sizeof(departamento) - 1] = '\0';

    strncpy(municipio, "", sizeof(municipio) - 1);
    municipio[sizeof(municipio) - 1] = '\0';

    strncpy(tipo, "", sizeof(tipo) - 1);
    tipo[sizeof(tipo) - 1] = '\0';

    strncpy(direccion, "", sizeof(direccion) - 1);
    direccion[sizeof(direccion) - 1] = '\0';

    precioNoche = 0.0f;

    strncpy(amenidades, "", sizeof(amenidades) - 1);
    amenidades[sizeof(amenidades) - 1] = '\0';

    strncpy(fechasReservadas, "", sizeof(fechasReservadas) - 1);
    fechasReservadas[sizeof(fechasReservadas) - 1] = '\0';
}

Alojamiento::Alojamiento(const char* cod, const char* nom, const char* docAnf, const char* depto, const char* muni, const char* t,
                         const char* dir, float precio,const char* amen, const char* fechas) {

    strncpy(codigo, cod, sizeof(codigo) - 1);
    codigo[sizeof(codigo) - 1] = '\0';

    strncpy(nombre, nom, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';

    strncpy(documentoAnfitrion, docAnf, sizeof(documentoAnfitrion) - 1);
    documentoAnfitrion[sizeof(documentoAnfitrion) - 1] = '\0';

    strncpy(departamento, depto, sizeof(departamento) - 1);
    departamento[sizeof(departamento) - 1] = '\0';

    strncpy(municipio, muni, sizeof(municipio) - 1);
    municipio[sizeof(municipio) - 1] = '\0';

    strncpy(tipo, t, sizeof(tipo) - 1);
    tipo[sizeof(tipo) - 1] = '\0';

    strncpy(direccion, dir, sizeof(direccion) - 1);
    direccion[sizeof(direccion) - 1] = '\0';

    precioNoche = precio;

    strncpy(amenidades, amen, sizeof(amenidades) - 1);
    amenidades[sizeof(amenidades) - 1] = '\0';

    strncpy(fechasReservadas, fechas, sizeof(fechasReservadas) - 1);
    fechasReservadas[sizeof(fechasReservadas) - 1] = '\0';
}

const char* Alojamiento::getCodigo() const { return codigo; }
const char* Alojamiento::getNombre() const { return nombre; }
const char* Alojamiento::getMunicipio() const { return municipio; }
float Alojamiento::getPrecioPorNoche() const { return precioNoche; }

void Alojamiento::mostrar() const {
    cout << "Codigo: " << codigo << " - " << nombre << endl;
    cout << "Tipo: " << tipo << " - Direccion: " << direccion << endl;
    cout << "Municipio: " << municipio << " (" << departamento << ")" << endl;
    cout << "Precio por noche: $" << precioNoche << endl;
    cout << "Amenidades: " << amenidades << endl;
    if (strlen(fechasReservadas) > 0) {
        cout << "Fechas reservadas: " << fechasReservadas << endl;
    } else {
        cout << "Sin fechas reservadas." << endl;
    }
    cout << "--------------------------" << endl;
}

bool Alojamiento::disponibilidad(const Fecha& nuevaEntrada, int duracion,const Reservacion* reservas, int cantidadReservas) const {
    Fecha nuevaSalida = nuevaEntrada.sumarDias(duracion);

    for (int i = 0; i < cantidadReservas; i++) {
        const Reservacion& res = reservas[i];

        if (strcmp(res.getCodigoAlojamiento(), codigo) == 0) {
            Fecha resInicio = res.getFechaInicio();
            Fecha resSalida = resInicio.sumarDias(res.getDuracion());

            bool noSeSolapan = nuevaSalida.esMenorQue(resInicio) || resSalida.esMenorQue(nuevaEntrada);
            if (!noSeSolapan) {
                return false;
            }
        }
    }

    return true; // No se encontró solapamiento, está disponible
}

