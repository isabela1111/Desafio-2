#include "medicionderecursos.h"
#include <iostream>
using namespace std;

int medicionderecursos::conteoCiclos = 0;
size_t medicionderecursos::memoriaAsignada = 0;

void medicionderecursos::contarCiclo() {
    conteoCiclos++;
}

void medicionderecursos::agregarMemoria(size_t bytes) {
    memoriaAsignada += bytes;
}

void medicionderecursos::mostrarResumen() {
    cout << "\n--- RESUMEN DE RENDIMIENTO ---\n";
    cout << "Total de ciclos ejecutados: " << conteoCiclos << endl;
    cout << "Memoria total asignada con 'new': " << memoriaAsignada << " bytes\n";
    cout << "-------------------------------\n";
}
