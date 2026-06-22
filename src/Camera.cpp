#include "Camera.h"
#include "Globals.h"

// Definição dos parâmetros da câmera
float eyeX = 0.0f;
float eyeY = 0.0f;
float eyeZ = 5.0f;

float centerX = 0.0f;
float centerY = 0.0f;
float centerZ = 0.0f;

float upX = 0.0f;
float upY = 1.0f;
float upZ = 0.0f;

void inicializarCamera() {
    resetarCamera();
}

void aplicarCamera() {
    gluLookAt(
        eyeX, eyeY, eyeZ,
        centerX, centerY, centerZ,
        upX, upY, upZ
    );
}

void resetarCamera() {
    eyeX = 0.0f;
    eyeY = 0.0f;
    eyeZ = 5.0f;
    centerX = 0.0f;
    centerY = 0.0f;
    centerZ = 0.0f;
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
}

void gerenciarTecladoCamera(unsigned char key) {
    float passo = 0.1f;

    switch (key) {
        case 'w':
        case 'W':
            eyeZ -= passo; // Aproxima a câmera do objeto
            break;
        case 's':
        case 'S':
            eyeZ += passo; // Afasta a câmera do objeto
            break;
        case 'a':
        case 'A':
            eyeX -= passo; // Move a câmera para a esquerda
            break;
        case 'd':
        case 'D':
            eyeX += passo; // Move a câmera para a direita
            break;
        case 'q':
        case 'Q':
            eyeY += passo; // Move a câmera para cima
            break;
        case 'e':
        case 'E':
            eyeY -= passo; // Move a câmera para baixo
            break;
        case 'r':
        case 'R':
            resetarCamera(); // Reseta para os valores padrões
            break;
    }
}
