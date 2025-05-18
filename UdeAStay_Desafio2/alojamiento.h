#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

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
    float getPrecioPorNoche() const;

    void mostrar() const;
};

#endif
