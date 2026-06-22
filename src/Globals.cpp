#include "Globals.h"

// Estados atuais do simulador (valores iniciais correspondentes ao main.cpp original)
int moduloAtual = MODULO_TRANSFORMACOES;
int objetoAtual = OBJ_CUBO;
int transformacaoAtiva = TRANS_ROTACAO;
int projecaoAtual = PROJ_PERSPECTIVA;
bool ilumLigada = true;
bool texturaAtiva = false;
bool mostrarCurva = false;

// Parâmetros interativos (controlados via teclado)
float rotX = 20.0f;
float rotY = 45.0f;
float transX = 0.0f;
float transY = 0.0f;
float transZ = 0.0f; // No original era -5.0f, mas agora a camera com gluLookAt afasta o ponto de vista
float escalaX = 1.0f;
float escalaY = 1.0f;
float escalaZ = 1.0f;

// ID da textura procedural
GLuint checkboardTexID = 0;

// Pontos de controle iniciais da curva de Bézier (Módulo 5)
GLfloat pontosControleBezier[4][3] = {
    { -2.0f, -1.5f, 0.0f },
    { -0.5f,  2.5f, 0.0f },
    {  0.5f, -2.5f, 0.0f },
    {  2.0f,  1.5f, 0.0f },
};

// Controle de seleção do mouse para a curva de Bézier
int pontoSelecionadoBezier = -1;
