#include <GL/glut.h>
#include <iostream>
#include "Globals.h"
#include "Camera.h"
#include "Objetos.h"
#include "Iluminacao.h"
#include "Curvas.h"
#include "UI.h"

// =========================================================================
// 1. RENDERIZAÇÃO PRINCIPAL E GERENCIAMENTO DE VIEWPORTS
// =========================================================================
void desenharCena() {
    // Limpa a tela e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    // ---------------------------------------------------------------------
    // VIEWPORT 3D (Parte Superior - Cena OpenGL)
    // ---------------------------------------------------------------------
    int alturaViewport3D = h - H_HUD;
    if (alturaViewport3D < 1) {
        alturaViewport3D = 1;
    }
    
    // Define a região de desenho 3D acima do painel do console HUD
    glViewport(0, H_HUD, w, alturaViewport3D);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspecto = (float)w / (float)alturaViewport3D;

    // Aplica a projeção selecionada
    if (projecaoAtual == PROJ_PERSPECTIVA) {
        gluPerspective(45.0, aspecto, 1.0, 20.0);
    } else {
        if (aspecto >= 1.0) {
            glOrtho(-2.5 * aspecto, 2.5 * aspecto, -2.5, 2.5, 1.0, 20.0);
        } else {
            glOrtho(-2.5, 2.5, -2.5 / aspecto, 2.5 / aspecto, 1.0, 20.0);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Aplica a visualização da Câmera (Módulo 3: gluLookAt)
    aplicarCamera();

    // Aplica as matrizes de transformações do objeto (Módulo 2)
    glTranslatef(transX, transY, transZ);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glScalef(escalaX, escalaY, escalaZ);

    // Aplica o pipeline de iluminação (Módulo 4)
    aplicarIluminacao();

    // Desenha o objeto ou a Curva de Bézier (Módulo 1 & Módulo 5)
    if (mostrarCurva) {
        renderizarCurvaBezier();
    } else {
        renderizarObjetoAtual();
    }

    // ---------------------------------------------------------------------
    // VIEWPORT 2D HUD (Parte Inferior - Console & Status)
    // ---------------------------------------------------------------------
    renderizarHUD(w, h);

    // Efetua a troca de buffers para exibição na tela (Double Buffering)
    glutSwapBuffers();
}

// Callback de redimensionamento da janela gráfica
void alterarProjecaoEPipeline(int /* w */, int h) {
    // Garante que a janela nunca possua tamanho nulo
    if (h == 0) {
        h = 1;
    }
    // Repassa o redesenhar. O cálculo da projeção e das viewports é dinâmico em desenharCena()
    glutPostRedisplay();
}

// =========================================================================
// 2. CALLBACKS DE ENTRADA (Teclado e Menus)
// =========================================================================
void gerenciarTecladoComum(unsigned char key, int /* x */, int /* y */) {
    // Encaminha a entrada para o módulo correspondente
    gerenciarTecladoCamera(key);
    gerenciarTecladoLuz(key);
    
    // Força o redesenho da tela a cada tecla pressionada
    glutPostRedisplay();
}

void gerenciarTecladoEspecial(int key, int /* x */, int /* y */) {
    float passoMover = 0.1f;
    float passoAngulo = 5.0f;
    float passoEscala = 0.05f;

    switch (transformacaoAtiva) {
        case TRANS_ROTACAO:
            if (key == GLUT_KEY_LEFT)  rotY -= passoAngulo;
            if (key == GLUT_KEY_RIGHT) rotY += passoAngulo;
            if (key == GLUT_KEY_UP)    rotX -= passoAngulo;
            if (key == GLUT_KEY_DOWN)  rotX += passoAngulo;
            break;
        case TRANS_TRANSLACAO:
            if (key == GLUT_KEY_LEFT)  transX -= passoMover;
            if (key == GLUT_KEY_RIGHT) transX += passoMover;
            if (key == GLUT_KEY_UP)    transY += passoMover;
            if (key == GLUT_KEY_DOWN)  transY -= passoMover;
            break;
        case TRANS_ESCALA:
            // Impede escala nula ou negativa (Senior Checklist)
            if (key == GLUT_KEY_UP) {
                escalaX += passoEscala;
                escalaY += passoEscala;
                escalaZ += passoEscala;
            }
            if (key == GLUT_KEY_DOWN) {
                if (escalaX > 0.06f) {
                    escalaX -= passoEscala;
                    escalaY -= passoEscala;
                    escalaZ -= passoEscala;
                }
            }
            break;
    }
    glutPostRedisplay(); 
}

void escutarMenu(int opcao) {
    switch (opcao) {
        // Seleção de Objetos
        case OBJ_CUBO:          objetoAtual = OBJ_CUBO; mostrarCurva = false; break;
        case OBJ_ESFERA:        objetoAtual = OBJ_ESFERA; mostrarCurva = false; break;
        case OBJ_BULE:          objetoAtual = OBJ_BULE; mostrarCurva = false; break;
        case OBJ_TRIANGULO:     objetoAtual = OBJ_TRIANGULO; mostrarCurva = false; break;
        case OBJ_QUADRILATERO:  objetoAtual = OBJ_QUADRILATERO; mostrarCurva = false; break;

        // Seleção de Transformações
        case TRANS_ROTACAO:    transformacaoAtiva = TRANS_ROTACAO; break;
        case TRANS_TRANSLACAO: transformacaoAtiva = TRANS_TRANSLACAO; break;
        case TRANS_ESCALA:     transformacaoAtiva = TRANS_ESCALA; break;

        // Seleção de Projeções
        case PROJ_PERSPECTIVA: projecaoAtual = PROJ_PERSPECTIVA; break;
        case PROJ_ORTOGRAFICA: projecaoAtual = PROJ_ORTOGRAFICA; break;

        // Modos de Iluminação
        case ILUM_LIGADA:    ilumLigada = true; break;
        case ILUM_DESLIGADA: ilumLigada = false; break;

        // Efeitos
        case EXIBIR_TEXTURA:      texturaAtiva = !texturaAtiva; mostrarCurva = false; break;
        case EXIBIR_CURVA_BEZIER: mostrarCurva = !mostrarCurva; break;
    }
    glutPostRedisplay();
}

void construirMenuContextual() {
    int subMenuObjetos = glutCreateMenu(escutarMenu); 
    glutAddMenuEntry("Primitiva Cubo 3D", OBJ_CUBO);
    glutAddMenuEntry("Primitiva Esfera 3D", OBJ_ESFERA);
    glutAddMenuEntry("Primitiva Bule 3D", OBJ_BULE);
    glutAddMenuEntry("Primitiva Triangulo 2D (glBegin)", OBJ_TRIANGULO);
    glutAddMenuEntry("Primitiva Quadrilatero 2D (glBegin)", OBJ_QUADRILATERO);

    int subMenuTransformacoes = glutCreateMenu(escutarMenu); 
    glutAddMenuEntry("Controlar Rotacao", TRANS_ROTACAO);
    glutAddMenuEntry("Controlar Translacao XY", TRANS_TRANSLACAO);
    glutAddMenuEntry("Controlar Escala Uniforme", TRANS_ESCALA);

    int subMenuProjecoes = glutCreateMenu(escutarMenu); 
    glutAddMenuEntry("Projecao Perspectiva", PROJ_PERSPECTIVA);
    glutAddMenuEntry("Projecao Ortografica (glOrtho)", PROJ_ORTOGRAFICA);

    int subMenuIluminacao = glutCreateMenu(escutarMenu); 
    glutAddMenuEntry("Ativar Iluminacao (GL_LIGHT0)", ILUM_LIGADA);
    glutAddMenuEntry("Desativar Iluminacao", ILUM_DESLIGADA);

    int subMenuTexturasCurvas = glutCreateMenu(escutarMenu); 
    glutAddMenuEntry("Alternar Textura Xadrez (On/Off)", EXIBIR_TEXTURA);
    glutAddMenuEntry("Alternar p/ Curva de Bezier", EXIBIR_CURVA_BEZIER);

    glutCreateMenu(escutarMenu); 
    glutAddSubMenu("Modulo 1: Objetos", subMenuObjetos);
    glutAddSubMenu("Modulo 2: Transformacoes", subMenuTransformacoes);
    glutAddSubMenu("Modulo 3: Projecoes & Camera", subMenuProjecoes);
    glutAddSubMenu("Modulo 4: Iluminacao & Materiais", subMenuIluminacao);
    glutAddSubMenu("Modulo 5: Texturas & Curvas", subMenuTexturasCurvas);

    glutAttachMenu(GLUT_RIGHT_BUTTON); 
}

// =========================================================================
// 3. INICIALIZAÇÃO E MAIN
// =========================================================================
void inicializarConfiguracoesGlobais() {
    // Cor de fundo do simulador (cinza azulado escuro)
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f); 
    
    // Habilita teste de profundidade para renderização 3D correta
    glEnable(GL_DEPTH_TEST);

    // Inicializa a iluminação (Módulo 4)
    inicializarIluminacao();

    // Inicializa a textura procedural (Módulo 5)
    gerarTexturaXadrez();

    // Inicializa os parâmetros da câmera (Módulo 3)
    inicializarCamera();

    // Configuração de textura automática (geração esférica)
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768); // Resolução aprimorada para caber o HUD confortavelmente
    glutCreateWindow("Simulador Interativo OpenGL - UNIVASF (2026.1)");

    inicializarConfiguracoesGlobais();
    construirMenuContextual();

    // Registro de callbacks
    glutDisplayFunc(desenharCena);
    glutReshapeFunc(alterarProjecaoEPipeline);
    glutKeyboardFunc(gerenciarTecladoComum);
    glutSpecialFunc(gerenciarTecladoEspecial); 
    
    // Callbacks do mouse para a curva interativa
    glutMouseFunc(gerenciarCliqueMouseBezier);
    glutMotionFunc(gerenciarMovimentoMouseBezier);

    glutMainLoop();
    return 0;
}