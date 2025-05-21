#ifndef UDEASTAY_H
#define UDEASTAY_H

#include "huesped.h"
#include "anfitrion.h"
#include "alojamiento.h"

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
    void mostrarAnfitriones();

    void cargarAlojamientos();
    void mostrarAlojamientos();
    void cargarReservaciones(Reservacion* reservas[], int& totalReservas, int maxReservas);

    void anularReserva(const char* codigoReserva);
    void menuAnularReservaComoHuesped(const char* documentoHuesped);
    float obtenerPuntuacionAnfitrion(const char* doc)const;
    void menuReservar();
    int obtenerUltimoCodigoReserva();
    void guardarReservacionEnArchivo(const Reservacion& nueva);
    void agregarReserva(Reservacion* nueva);
    void menuHuesped();
    void aplicarFiltros(const char* municipio, const Fecha& inicio, int noches, float maxPrecio, float minPuntuacion) const;


    void menuAnfitrion(Anfitrion* anfitriones[], int totalAnfitriones, Reservacion* reservas[], int& totalReservas);



};

#endif // UDEASTAY_H
