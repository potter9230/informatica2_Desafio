#include <iostream>
#include "MotorJuego.h"
#include "Configuracion.h"

int main() {
    int ancho, alto;

    std::cout << "--- TETRIS BITWISE (UdeA) ---" << std::endl;
    
    // Validación de dimensiones según requerimientos [cite: 27, 28]
    do {
        std::cout << "Ingrese el ancho del tablero (minimo 8 y multiplo de 8): ";
        std::cin >> ancho;
    } while (ancho < ANCHO_MIN || ancho % 8 != 0); // [cite: 29]

    do {
        std::cout << "Ingrese el alto del tablero (minimo 8): ";
        std::cin >> alto;
    } while (alto < ALTO_MIN);

    // Inicialización del motor en memoria dinámica [cite: 62, 78]
    MotorJuego* juego = new MotorJuego(ancho, alto);
    
    juego->iniciar();

    // Liberación de memoria para evitar leaks [cite: 62]
    delete juego;

    return 0;
}