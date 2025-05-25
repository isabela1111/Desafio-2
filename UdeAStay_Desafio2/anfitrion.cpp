#include "anfitrion.h"
#include "reservacion.h"
#include "alojamiento.h"
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

Anfitrion::Anfitrion() {
    documento = new char[1];
    documento[0] = '\0';
    antiguedad = 0;
    puntuacion = 0;
    codigosAlojamientos = nullptr;
    numAlojamientos = 0;
}

Anfitrion::Anfitrion(const char* doc, int ant, float punt, int* cods, int numCods) {
    documento = new char[strlen(doc) + 1];
    strcpy(documento, doc);
    antiguedad = ant;
    puntuacion = punt;
    numAlojamientos = numCods;

    if (numAlojamientos > 0) {
        codigosAlojamientos = new int[numAlojamientos];
        for (int i = 0; i < numAlojamientos; i++) {
            codigosAlojamientos[i] = cods[i];
        }
    } else {
        codigosAlojamientos = nullptr;
    }
}

Anfitrion::~Anfitrion() {
    delete[] documento;
    delete[] codigosAlojamientos;
}
const char* Anfitrion::getDocumento() const {
    return documento;
}

float Anfitrion::getPuntuacion() const {
    return puntuacion;
}

void Anfitrion::verReservas(Reservacion* reservas[], int totalReservas) const {
    cout << "Reservas activas para el anfitrion con documento: " << documento << endl;
    bool encontrada = false;

    for (int i = 0; i < totalReservas; i++) {
        const char* codReserva = reservas[i]->getCodigoAlojamiento();

        // Comparar contra todos los alojamientos del anfitrión
        for (int j = 0; j < numAlojamientos; j++) {
            char buffer[10];
            sprintf(buffer, "%d", codigosAlojamientos[j]);

            if (strcmp(codReserva, buffer) == 0) {
                reservas[i]->mostrar();
                encontrada = true;
                break;
            }
        }
    }
    if (!encontrada) {
        cout << "No se encontraron reservaciones para sus alojamientos.\n";
    }
}

void Anfitrion::actualizarHistorico(Reservacion* reservas[], int& totalReservas, const Fecha& fechaCorte) {
    FILE* historico = fopen("Historico.txt", "a");
    if (!historico) {
        cout << "No se pudo abrir el archivo Historico.txt para escritura.\n";
        return;
    }
    FILE* original = fopen("Reservaciones_activas.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    if (!original || !temp) {
        cout << "Error al abrir archivos de reservaciones activas.\n";
        fclose(historico);
        return;
    }
    char linea[1024];
    while (fgets(linea, sizeof(linea), original)) {
        char copia[1024];
        strcpy(copia, linea);
        copia[strcspn(copia, "\n")] = '\0';

        char* token = strtok(copia, ";");
        if (!token) continue;
        char codigo[15]; strcpy(codigo, token);

        token = strtok(NULL, ";"); if (!token) continue;
        char documento[20]; strcpy(documento, token);

        token = strtok(NULL, ";"); if (!token) continue;
        char codAloj[10]; strcpy(codAloj, token);

        token = strtok(NULL, ";"); if (!token) continue;
        int d, m, a;
        sscanf(token, "%d/%d/%d", &d, &m, &a);
        Fecha inicio(d, m, a);

        token = strtok(NULL, ";"); if (!token) continue;
        int duracion = atoi(token);
        Fecha fin = inicio.sumarDias(duracion - 1);

        bool esDelAnfitrion = false;
        for (int j = 0; j < numAlojamientos; j++) {
            char codAnf[10];
            sprintf(codAnf, "%d", codigosAlojamientos[j]);
            if (strcmp(codAloj, codAnf) == 0) {
                esDelAnfitrion = true;
                break;
            }
        }
        if (esDelAnfitrion && fin.esMenorQue(fechaCorte)) {
            fputs(linea, historico);
            // eliminar el arreglo de reservas en la memoria
            for (int i = 0; i < totalReservas; i++) {
                if (strcmp(reservas[i]->getCodigo(), codigo) == 0) {
                    delete reservas[i];
                    for (int k = i; k < totalReservas - 1; k++)
                        reservas[k] = reservas[k + 1];
                    totalReservas--;
                    break;
                }
            }
            // Aqui eliminamos fechas del alojamiento
            for (int i = 0; i < 1000; i++) {
                if (reservas[i] && strcmp(reservas[i]->getCodigo(), codigo) == 0) {
                    break;
                }
            }
            Alojamiento a;
            a.actualizarFechasAlojamiento(codAloj, inicio, duracion);
        } else {
            fputs(linea, temp);
        }
    }
    fclose(original);
    fclose(temp);
    fclose(historico);

    remove("Reservaciones_activas.txt");
    rename("temp.txt", "Reservaciones_activas.txt");
    cout << "Reservas actualizadas. Las finalizadas se movieron al historico.\n";
}
