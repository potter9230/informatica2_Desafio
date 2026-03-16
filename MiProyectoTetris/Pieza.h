#ifndef PIEZA_H
#define PIEZA_H

#include "Configuracion.h"

class Pieza {
private:
    int tipo;
    int rotacion;
    int x;
    int y;
    unsigned short mascaraActual;

public:
    Pieza(int _tipo, int _xInicial);

    void rotar();
    void mover(int dx, int dy);

    int getX() const { return x; }
    int getY() const { return y; }
    int getTipo() const { return tipo; }
    int getRotacion() const { return rotacion; }
    unsigned short getMascara() const { return mascaraActual; }
};

#endif