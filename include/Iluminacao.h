#ifndef ILUMINACAO_H
#define ILUMINACAO_H

#include <GL/glut.h>

// Coordenadas da fonte de luz (Módulo 4: Iluminação e Materiais)
extern float luzX;
extern float luzY;
extern float luzZ;

// Inicializa o pipeline de iluminação (fontes de luz, materiais e modelos de shading)
void inicializarIluminacao();

// Atualiza a posição da luz em tempo de execução e habilita/desabilita se ligada
void aplicarIluminacao();

// Controla a movimentação da fonte de luz via teclado comum
void gerenciarTecladoLuz(unsigned char key);

// Reseta a luz para a posição padrão
void resetarLuz();

#endif // ILUMINACAO_H
