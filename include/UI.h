#ifndef UI_H
#define UI_H

#include <GL/glut.h>
#include <string>

// Altura em pixels reservada para o painel HUD na base da janela
const int H_HUD = 200;

// Renderiza a interface do console de comandos OpenGL e status na viewport inferior
void renderizarHUD(int larguraJanela, int alturaJanela);

// Renderiza um texto em uma coordenada 2D específica usando fontes bitmap do GLUT
void desenharTexto2D(float x, float y, void* fonte, const std::string& texto, float r, float g, float b);

#endif // UI_H
