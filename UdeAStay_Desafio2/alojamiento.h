#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include <string>
using namespace std;

class Alojamiento {
private:
    string codigo;
    string nombre;
    string documentoAnfitrion;
    string departamento;
    string municipio;
    string tipo;
    string direccion;
    float precioNoche;
    string amenidades;
    string fechasReservadas;

public:
    Alojamiento();
    Alojamiento(string cod, string nom, string docAnf, string depto,string muni, string tipo, string dir,
                float precio,string amenidades, string fechasRes);

    // Getters
    string getCodigo() const;
    string getNombre() const;
    string getDocumentoAnfitrion() const;
    string getDepartamento() const;
    string getMunicipio() const;
    string getTipo() const;
    string getDireccion() const;
    float getPrecioPorNoche() const;
    string getAmenidades() const;
    string getFechasReservadas() const;

    // Setters
    void setCodigo(string cod);
    void setNombre(string nom);
    void setDocumentoAnfitrion(string doc);
    void setDepartamento(string depto);
    void setMunicipio(string muni);
    void setTipo(string t);
    void setDireccion(string dir);
    void setPrecioPorNoche(float precio);
    void setAmenidades(string a);
    void setFechasReservadas(string fechas);

    void Disponibilidad() const;
};

#endif // ALOJAMIENTO_H
