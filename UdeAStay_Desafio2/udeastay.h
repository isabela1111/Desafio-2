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

    Fecha fechaCorte;
    bool fechaCorteDefinida;

public:
    UdeAStay();
    ~UdeAStay();

    void cargarHuespedes();
    void cargarAnfitriones(Anfitrion* anfitriones[], int& totalAnfitriones, int maxAnfitriones);
    void cargarAlojamientos();
    void cargarReservaciones();

    void guardarReservacionEnArchivo(const Reservacion& nueva);

    int obtenerUltimoCodigoReserva();
    float obtenerPuntuacionAnfitrion(const char* doc) const;
    void agregarReserva(Reservacion* nueva);
    void aplicarFiltros(const char* municipio, const Fecha& inicio, int noches, float precioMax, float puntMin) const;
    void anularReserva(const char* codigoReserva);

    void menuAnularReservaComoHuesped(const char* documentoHuesped);
    void menuReservar();
    void menuAnfitrion(Anfitrion* anfitriones[], int totalAnfitriones, Reservacion* reservas[], int& totalReservas);
    void menuHuesped(const char* documento);
    void menuPrincipal();

    bool huespedExiste(const char* documento) const;
    bool anfitrionExiste(const char* documento) const;
    void guardarFechaCorteEnArchivo();
    void cargarFechaCorteDesdeArchivo();
    void actualizarHistorico();


};

#endif // UDEASTAY_H



