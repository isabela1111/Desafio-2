#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include "fecha.h"
#include "reservacion.h"

class Alojamiento {
private:
    char codigo[10];
    char nombre[50];
    char documentoAnfitrion[15];
    char departamento[30];
    char municipio[30];
    char tipo[20];
    char direccion[60];
    float precioNoche;
    char amenidades[200];
    char fechasReservadas[200];

public:
    Alojamiento();
    Alojamiento(const char* cod, const char* nom, const char* docAnf,const char* depto, const char* muni, const char* tipo,
                const char* dir, float precio,const char* amen, const char* fechas);

    const char* getCodigo() const;
    const char* getNombre() const;
    const char* getMunicipio() const;
    const char* getDocumentoAnfitrion() const;
    float getPrecioPorNoche() const;



    void mostrar() const;
    bool disponibilidad(const Fecha& nuevaEntrada, int duracion, Reservacion** reservas, int cantidadReservas) const;
    void actualizarFechasAlojamiento(const char* codAloj, const Fecha& inicio, int duracion);
    void agregarFechasReservadas(const char* cod, const Fecha& inicio, int duracion);


};

#endif
