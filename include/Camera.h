#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

// Parâmetros de posicionamento da câmera (Módulo 3: Projeções e Câmera)
extern float eyeX;
extern float eyeY;
extern float eyeZ;

extern float centerX;
extern float centerY;
extern float centerZ;

extern float upX;
extern float upY;
extern float upZ;

// Inicializa a posição padrão da câmera
void inicializarCamera();

// Aplica a matriz de visualização gluLookAt
void aplicarCamera();

// Gerencia a entrada de teclado comum para movimentação da câmera
void gerenciarTecladoCamera(unsigned char key);

// Reseta a câmera para a posição original
void resetarCamera();

#endif // CAMERA_H
