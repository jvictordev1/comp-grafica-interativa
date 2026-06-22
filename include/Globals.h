#ifndef GLOBALS_H
#define GLOBALS_H

#include <GL/glut.h>

// Módulos principais do simulador
enum ModulosSimulador {
    MODULO_OBJETOS,
    MODULO_TRANSFORMACOES,
    MODULO_PROJECOES,
    MODULO_ILUMINACAO,
    MODULO_TEXTURAS_CURVAS,
};

// Opções gerais do menu contextual
enum OpcoesMenu {
    OBJ_CUBO,
    OBJ_ESFERA,
    OBJ_BULE,
    OBJ_TRIANGULO,
    OBJ_QUADRILATERO,
    TRANS_ROTACAO,
    TRANS_TRANSLACAO,
    TRANS_ESCALA,
    PROJ_PERSPECTIVA,
    PROJ_ORTOGRAFICA,
    ILUM_LIGADA,
    ILUM_DESLIGADA,
    EXIBIR_TEXTURA,
    EXIBIR_CURVA_BEZIER,
};

// Estados globais compartilhados
extern int moduloAtual;
extern int objetoAtual;
extern int transformacaoAtiva;
extern int projecaoAtual;
extern bool ilumLigada;
extern bool texturaAtiva;
extern bool mostrarCurva;

// Parâmetros de transformações geométricas do objeto (Módulo 2)
extern float rotX;
extern float rotY;
extern float transX;
extern float transY;
extern float transZ;
extern float escalaX;
extern float escalaY;
extern float escalaZ;

// ID da textura procedural
extern GLuint checkboardTexID;

// Pontos de controle da curva de Bézier (Módulo 5)
extern GLfloat pontosControleBezier[4][3];
extern int pontoSelecionadoBezier; // Ponto selecionado pelo mouse (-1 se nenhum)

#endif // GLOBALS_H
