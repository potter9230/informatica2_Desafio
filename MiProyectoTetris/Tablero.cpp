#include <iostream>
#include "Tablero.h"

Tablero::Tablero(int _ancho, int _alto) {
    ancho = (_ancho < 8) ? 8 : _ancho;
    if (ancho % 8 != 0) ancho = ((ancho / 8) + 1) * 8;
    
    alto = (_alto < 8) ? 8 : _alto;
    anchoBytes = ancho / 8;

    inicializar();
}

void Tablero::inicializar() {
    rejilla = new unsigned char*[alto];
    for (int i = 0; i < alto; i++) {
        rejilla[i] = new unsigned char[anchoBytes];
        for (int j = 0; j < anchoBytes; j++) {
            rejilla[i][j] = 0;
        }
    }
}

Tablero::~Tablero() {
    liberarMemoria();
}

void Tablero::liberarMemoria() {
    if (rejilla != nullptr) {
        for (int i = 0; i < alto; i++) {
            delete[] rejilla[i];
        }
        delete[] rejilla;
        rejilla = nullptr;
    }
}

void Tablero::pintar() {
    for (int i = 0; i < alto; i++) {
        std::cout << "|";
        for (int b = 0; b < anchoBytes; b++) {
            unsigned char byteActual = rejilla[i][b];
            for (int bit = 7; bit >= 0; bit--) {
                if ((byteActual >> bit) & 1) {
                    std::cout << "#";
                } else {
                    std::cout << ".";
                }
            }
        }
        std::cout << "|" << std::endl;
    }
}

bool Tablero::verificarFilaLlena(int fila) {
    for (int j = 0; j < anchoBytes; j++) {
        if (rejilla[fila][j] != 0xFF) return false;
    }
    return true;
}

void Tablero::eliminarFila(int fila) {
    delete[] rejilla[fila];
    
    for (int i = fila; i > 0; i--) {
        rejilla[i] = rejilla[i - 1];
    }
    
    rejilla[0] = new unsigned char[anchoBytes];
    for (int j = 0; j < anchoBytes; j++) {
        rejilla[0][j] = 0;
    }
}