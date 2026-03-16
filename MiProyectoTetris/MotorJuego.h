#ifndef MOTORJUEGO_H
#define MOTORJUEGO_H

#include "Tablero.h"
#include "Pieza.h"

class MotorJuego {
private:
    Tablero* tablero;
    Pieza* piezaActual;
    bool gameOver;

    // Métodos privados de lógica interna
    void spawnPieza();
    bool verificarColision(int dx, int dy, bool rotar);
    void fijarPieza();
    void limpiarFilasCompletas();

public:
    MotorJuego(int ancho, int alto);
    ~MotorJuego();

    void iniciar(); // Bucle principal del juego
    void procesarEntrada(char comando);
};

#endif