#include "anfitrion.h"
#include "reservacion.h"
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

Anfitrion::Anfitrion(const char* doc, int ant, int punt, int* cods, int numCods) {
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



//Esta funcion solo se uso de prueba para comprobar que el programara leyera correctamente la informacion del .txt, se borrara en un commit despues
/*
void Anfitrion::mostrarInfo() const {
    cout << "Documento: " << documento << endl;
    cout << "Antigüedad: " << antiguedad << " meses" << endl;
    cout << "Puntuación: " << puntuacion << "/5" << endl;
    cout << "Alojamientos: ";
    if (numAlojamientos == 0) {
        cout << "Ninguno";
    } else {
        for (int i = 0; i < numAlojamientos; i++) {
            cout << codigosAlojamientos[i];
            if (i < numAlojamientos - 1)
                cout << ", ";
        }
    }
    cout << "\n-----------------------------\n";
}*/

void Anfitrion::verReservas(Reservacion* reservas[], int totalReservas) const {
    cout << "Reservas activas para el anfitrión con documento: " << documento << endl;
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
        cout << "No se pudo abrir el archivo reservas_historico.txt para escritura.\n";
        return;
    }

    int nuevasReservas = 0;
    Reservacion* nuevas[1000]; // temporal

    for (int i = 0; i < totalReservas; i++) {
        const char* codAloj = reservas[i]->getCodigoAlojamiento();
        bool esDelAnfitrion = false;

        // Verifica si este alojamiento lo administra el anfitrión
        for (int j = 0; j < numAlojamientos; j++) {
            char buffer[10];
            sprintf(buffer, "%d", codigosAlojamientos[j]);

            if (strcmp(codAloj, buffer) == 0) {
                esDelAnfitrion = true;
                break;
            }
        }

        if (esDelAnfitrion && !reservas[i]->activa(fechaCorte)) {
            // Reservación terminada → mover a historico.txt
            fprintf(historico, "%s;%s;%s;%02d/%02d/%04d;%d;%s;%.2f;%02d/%02d/%04d;%s\n",
                    reservas[i]->getCodigo(),
                    reservas[i]->getDocumentoHuesped(),
                    reservas[i]->getCodigoAlojamiento(),
                    reservas[i]->getFechaInicio().getDia(),
                    reservas[i]->getFechaInicio().getMes(),
                    reservas[i]->getFechaInicio().getAnio(),
                    reservas[i]->getDuracion(),
                    reservas[i]->getMetodoPago(),
                    reservas[i]->getMonto(),
                    reservas[i]->getFechaPago().getDia(),
                    reservas[i]->getFechaPago().getMes(),
                    reservas[i]->getFechaPago().getAnio(),
                    reservas[i]->getAnotaciones()
                    );

            // Liberar memoria
            delete reservas[i];
        }
        else {
            nuevas[nuevasReservas++] = reservas[i];
        }
    }

    fclose(historico);
    // Copiar solo las activas de vuelta al arreglo original
    for (int i = 0; i < nuevasReservas; i++) {
        reservas[i] = nuevas[i];
    }
    totalReservas = nuevasReservas;

    cout << "Reservas actualizadas. Las finalizadas se movieron al histórico.\n";
}

