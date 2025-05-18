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
};

#endif // UDEASTAY_H
