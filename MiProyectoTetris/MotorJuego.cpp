#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MotorJuego.h"

MotorJuego::MotorJuego(int ancho, int alto) {
    std::srand(std::time(0));
    tablero = new Tablero(ancho, alto);
    gameOver = false;
    piezaActual = nullptr;
}

MotorJuego::~MotorJuego() {
    delete tablero;
    if (piezaActual != nullptr) delete piezaActual;
}

void MotorJuego::spawnPieza() {
    int tipo = std::rand() % 7;
    int xInicial = (tablero->getAncho() / 2) - 2;
    piezaActual = new Pieza(tipo, xInicial);

    if (verificarColision(0, 0, false)) {
        gameOver = true;
    }
}

bool MotorJuego::verificarColision(int dx, int dy, bool rotar) {
    int nextX = piezaActual->getX() + dx;
    int nextY = piezaActual->getY() + dy;
    unsigned short mascara = piezaActual->getMascara();

    if (rotar) {
        int nextRot = (piezaActual->getRotacion() + 1) % 4;
        mascara = TETRIMINOS[piezaActual->getTipo()][nextRot];
    }

    for (int i = 0; i < 4; i++) {
        int filaTablero = nextY + i;
        unsigned short filaPieza = (mascara >> (4 * (3 - i))) & 0xF;

        if (filaPieza == 0) continue;
        if (filaTablero >= tablero->getAlto() || filaTablero < 0) return true;

        for (int j = 0; j < 4; j++) {
            if ((filaPieza >> (3 - j)) & 1) {
                int colTablero = nextX + j;
                if (colTablero < 0 || colTablero >= tablero->getAncho()) return true;

                int byteIdx = colTablero / 8;
                int bitIdx = 7 - (colTablero % 8);
                if ((tablero->getRejilla()[filaTablero][byteIdx] >> bitIdx) & 1) return true;
            }
        }
    }
    return false;
}

void MotorJuego::fijarPieza() {
    unsigned short mascara = piezaActual->getMascara();
    for (int i = 0; i < 4; i++) {
        int filaTablero = piezaActual->getY() + i;
        unsigned short filaPieza = (mascara >> (4 * (3 - i))) & 0xF;

        for (int j = 0; j < 4; j++) {
            if ((filaPieza >> (3 - j)) & 1) {
                int colTablero = piezaActual->getX() + j;
                int byteIdx = colTablero / 8;
                int bitIdx = 7 - (colTablero % 8);
                tablero->getRejilla()[filaTablero][byteIdx] |= (1 << bitIdx);
            }
        }
    }
    delete piezaActual;
    piezaActual = nullptr;
}

void MotorJuego::limpiarFilasCompletas() {
    for (int i = 0; i < tablero->getAlto(); i++) {
        if (tablero->verificarFilaLlena(i)) {
            tablero->eliminarFila(i);
        }
    }
}

void MotorJuego::procesarEntrada(char comando) {
    switch (comando) {
        case 'a': case 'A':
            if (!verificarColision(-1, 0, false)) piezaActual->mover(-1, 0);
            break;
        case 'd': case 'D':
            if (!verificarColision(1, 0, false)) piezaActual->mover(1, 0);
            break;
        case 's': case 'S':
            if (!verificarColision(0, 1, false)) piezaActual->mover(0, 1);
            else {
                fijarPieza();
                limpiarFilasCompletas();
                spawnPieza();
            }
            break;
        case 'w': case 'W':
            if (!verificarColision(0, 0, true)) piezaActual->rotar();
            break;
    }
}

void MotorJuego::iniciar() {
    spawnPieza();
    while (!gameOver) {
        tablero->pintar();
        std::cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
        char accion;
        std::cin >> accion;
        if (accion == 'q' || accion == 'Q') break;
        procesarEntrada(accion);
    }
    if (gameOver) std::cout << "--- GAME OVER ---" << std::endl;
}