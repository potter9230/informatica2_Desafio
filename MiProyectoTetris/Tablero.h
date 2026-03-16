#ifndef TABLERO_H
#define TABLERO_H

class Tablero {
private:
    int ancho;  
    int alto;   
    int anchoBytes;
    unsigned char** rejilla;

public:
    // Constructor y Destructor
    Tablero(int _ancho, int _alto);
    ~Tablero();

    void inicializar();
    void liberarMemoria();
    
    void pintar();
    bool verificarFilaLlena(int fila);
    void eliminarFila(int fila);
    
    int getAncho() const { return ancho; }
    int getAlto() const { return alto; }
    unsigned char** getRejilla() { return rejilla; }
};

#endif