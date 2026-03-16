#include "Pieza.h"

Pieza::Pieza(int _tipo, int _xInicial) {
    tipo = _tipo;
    x = _xInicial;
    y = 0;
    rotacion = 0;
    
    mascaraActual = TETRIMINOS[tipo][rotacion];
}

void Pieza::rotar() {
    rotacion = (rotacion + 1) % 4;
    
    mascaraActual = TETRIMINOS[tipo][rotacion];
}

void Pieza::mover(int dx, int dy) {
    x += dx;
    y += dy;
}