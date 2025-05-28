#ifndef MEDICIONRECURSOS_H
#define MEDICIONRECURSOS_H
#include <cstddef>

class MedicionRecursos {
private:
    static int conteoCiclos;
    static size_t memoriaAsignada;

public:
    static void contarCiclo();
    static void agregarMemoria(size_t bytes);
    static void mostrarResumen();
};

#endif
