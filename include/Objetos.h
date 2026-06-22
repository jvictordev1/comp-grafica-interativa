#ifndef OBJETOS_H
#define OBJETOS_H

#include <GL/glut.h>

// Gera a textura procedural de xadrez
void gerarTexturaXadrez();

// Desenha um cubo mapeando a textura manualmente nas coordenadas de vértice
void renderizarCuboTexturizado();

// Desenha o objeto geométrico selecionado no estado atual
void renderizarObjetoAtual();

#endif // OBJETOS_H
