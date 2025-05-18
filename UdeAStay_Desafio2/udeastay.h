#ifndef UDEASTAY_H
#define UDEASTAY_H
#include "huesped.h"

class UdeAStay {
private:
    Huesped* huespedes;
    int totalHuespedes;

public:
    UdeAStay();
    ~UdeAStay();
    void cargarHuespedes();
    void mostrarHuespedes();
    void cargarAnfitriones(Anfitrion* anfitriones[], int& totalAnfitriones, int maxAnfitriones);

};

#endif // UDEASTAY_H
