#ifndef UDEASTAY_H
#define UDEASTAY_H

#include "huesped.h"
#include "anfitrion.h"
#include "alojamiento.h"
#include "reservacion.h"
#include "fecha.h"

class UdeAStay {
private:
    Huesped* huespedes;
    int totalHuespedes;

    Alojamiento* alojamientos;
    int totalAlojamientos;

    Anfitrion** anfitriones;
    int totalAnfitriones;

    Reservacion** reservas;
    int totalReservas;
    int capacidadReservas;

public:
    UdeAStay();
    ~UdeAStay();

    void cargarHuespedes();
    void mostrarHuespedes();

    void cargarAnfitriones(Anfitrion* anfitriones[], int& totalAnfitriones, int maxAnfitriones);
    void cargarAlojamientos();
    void mostrarAlojamientos();

    void cargarReservaciones();
    void guardarReservacionEnArchivo(const Reservacion& nueva);

    int obtenerUltimoCodigoReserva();
    float obtenerPuntuacionAnfitrion(const char* doc) const;

    void agregarReserva(Reservacion* nueva);
    void aplicarFiltros(const char* municipio, const Fecha& inicio, int noches, float precioMax, float puntMin) const;

    void menuReservar();
    void anularReserva(const char* codigoReserva);
    void menuAnularReservaComoHuesped(const char* documentoHuesped);

    void menuAnfitrion(Anfitrion* anfitriones[], int totalAnfitriones, Reservacion* reservas[], int& totalReservas);
    void menuHuesped(const char* documento);
    void menuPrincipal();

};

#endif // UDEASTAY_H



