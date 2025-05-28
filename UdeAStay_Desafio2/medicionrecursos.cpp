#include "medicionrecursos.h"
#include <iostream>
using namespace std;

int MedicionRecursos::conteoCiclos = 0;
size_t MedicionRecursos::memoriaAsignada = 0;

void MedicionRecursos::contarCiclo() {
    conteoCiclos++;
}

void MedicionRecursos::agregarMemoria(size_t bytes) {
    memoriaAsignada += bytes;
}

void MedicionRecursos::mostrarResumen() {
    cout << "\n--- RESUMEN DE RENDIMIENTO ---\n";
    cout << "Total de ciclos ejecutados: " << conteoCiclos << endl;
    cout << "Memoria total asignada con 'new': " << memoriaAsignada << " bytes\n";
    cout << "-------------------------------\n";
}
