#include "Curvas.h"
#include "Globals.h"
#include <cmath>

// Matrizes salvas durante a renderização para permitir projeções no callback do mouse
static GLdouble modelviewSalva[16];
static GLdouble projectionSalva[16];
static GLint viewportSalvo[4];

void renderizarCurvaBezier() {
    // Desabilita iluminação para renderizar linhas e pontos coloridos nítidos
    glDisable(GL_LIGHTING); 
    
    // Configura e avalia a curva de Bézier (Módulo 5)
    glColor3f(0.0f, 1.0f, 1.0f); // Cor ciano para a curva
    glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, 4, &pontosControleBezier[0][0]); 
    glEnable(GL_MAP1_VERTEX_3);
    
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 30; i++) {
        glEvalCoord1f((GLfloat)i / 30.0f);
    }
    glEnd();

    // Desenha os pontos de controle interativos
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++) {
        if (i == pontoSelecionadoBezier) {
            glColor3f(1.0f, 1.0f, 0.0f); // Amarelo se estiver selecionado
        } else {
            glColor3f(1.0f, 0.0f, 0.0f); // Vermelho caso contrário
        }
        glVertex3fv(pontosControleBezier[i]);
    }
    glEnd();

    // Desenha linhas tracejadas conectando os pontos de controle (polígono de controle)
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101); // Padrão tracejado
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 4; i++) {
        glVertex3fv(pontosControleBezier[i]);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    // Salva as matrizes de projeção correntes para uso na projeção do mouse
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewSalva);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionSalva);
    glGetIntegerv(GL_VIEWPORT, viewportSalvo);
}

void gerenciarCliqueMouseBezier(int button, int state, int x, int y) {
    if (!mostrarCurva) {
        return;
    }

    int alturaJanela = glutGet(GLUT_WINDOW_HEIGHT);
    // Inverte a coordenada Y do GLUT para ficar compatível com o OpenGL (origem no canto inferior esquerdo)
    int clickX = x;
    int clickY = alturaJanela - y;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            float menorDistancia = 9999.0f;
            int indiceMaisProximo = -1;

            // Encontra o ponto de controle mais próximo da posição do clique
            for (int i = 0; i < 4; i++) {
                GLdouble sx, sy, sz;
                gluProject(
                    pontosControleBezier[i][0], pontosControleBezier[i][1], pontosControleBezier[i][2],
                    modelviewSalva, projectionSalva, viewportSalvo,
                    &sx, &sy, &sz
                );

                float dx = (float)(sx - clickX);
                float dy = (float)(sy - clickY);
                float dist = std::sqrt(dx * dx + dy * dy);

                if (dist < menorDistancia) {
                    menorDistancia = dist;
                    indiceMaisProximo = i;
                }
            }

            // Seleciona o ponto se o clique estiver a menos de 20 pixels dele
            if (menorDistancia < 20.0f) {
                pontoSelecionadoBezier = indiceMaisProximo;
                glutPostRedisplay();
            }
        } else if (state == GLUT_UP) {
            pontoSelecionadoBezier = -1;
            glutPostRedisplay();
        }
    }
}

void gerenciarMovimentoMouseBezier(int x, int y) {
    if (!mostrarCurva || pontoSelecionadoBezier == -1) {
        return;
    }

    int alturaJanela = glutGet(GLUT_WINDOW_HEIGHT);
    int dragX = x;
    int dragY = alturaJanela - y;

    // Obtém o Z projetado do ponto atualmente selecionado
    GLdouble sx, sy, sz;
    gluProject(
        pontosControleBezier[pontoSelecionadoBezier][0],
        pontosControleBezier[pontoSelecionadoBezier][1],
        pontosControleBezier[pontoSelecionadoBezier][2],
        modelviewSalva, projectionSalva, viewportSalvo,
        &sx, &sy, &sz
    );

    // Desprojeta a coordenada 2D do mouse de volta para o espaço 3D do mundo
    GLdouble wx, wy, wz;
    gluUnProject(
        dragX, dragY, sz,
        modelviewSalva, projectionSalva, viewportSalvo,
        &wx, &wy, &wz
    );

    // Atualiza as coordenadas do ponto (mantendo o Z = 0 no plano de desenho)
    pontosControleBezier[pontoSelecionadoBezier][0] = (GLfloat)wx;
    pontosControleBezier[pontoSelecionadoBezier][1] = (GLfloat)wy;
    pontosControleBezier[pontoSelecionadoBezier][2] = 0.0f;

    glutPostRedisplay();
}
