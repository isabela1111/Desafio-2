#ifndef MEDICIONDERECURSOS_H
#define MEDICIONDERECURSOS_H

class MonitorRendimiento {
private:
    static int conteoCiclos;
    static size_t memoriaAsignada;

public:
    static void contarCiclo();

    static void agregarMemoria(size_t bytes);

    static void mostrarResumen();
};

#endif
