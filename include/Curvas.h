#ifndef CURVAS_H
#define CURVAS_H

#include <GL/glut.h>

// Renderiza a curva de Bézier e os pontos de controle (Módulo 5)
void renderizarCurvaBezier();

// Trata o clique do botão do mouse na seleção de pontos de controle
void gerenciarCliqueMouseBezier(int button, int state, int x, int y);

// Trata o arrasto do mouse ao mover os pontos de controle selecionados
void gerenciarMovimentoMouseBezier(int x, int y);

#endif // CURVAS_H
