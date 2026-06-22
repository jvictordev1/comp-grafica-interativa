#include "UI.h"
#include "Globals.h"
#include "Camera.h"
#include "Iluminacao.h"
#include <iomanip>
#include <sstream>

void desenharTexto2D(float x, float y, void* fonte, const std::string& texto, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (char c : texto) {
        glutBitmapCharacter(fonte, c);
    }
}

void renderizarHUD(int larguraJanela, int /* alturaJanela */) {
    // Configura a Viewport correspondente à área do HUD (toda a largura, H_HUD de altura na base)
    glViewport(0, 0, larguraJanela, H_HUD);
    
    // Configura a projeção ortográfica 2D baseada na largura atual
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, larguraJanela, 0.0, H_HUD);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Desabilita estados de 3D para renderização 2D limpa
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // 1. Desenha o fundo escuro do HUD (Gradiente elegante)
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.06f, 0.08f); // Cinza azulado muito escuro na base
    glVertex2f(0.0f, 0.0f);
    glVertex2f(larguraJanela, 0.0f);
    glColor3f(0.09f, 0.11f, 0.15f); // Tom ligeiramente mais claro no topo
    glVertex2f(larguraJanela, H_HUD);
    glVertex2f(0.0f, H_HUD);
    glEnd();

    // 2. Desenha a linha divisória do topo
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(0.18f, 0.22f, 0.30f); // Azul acinzentado de borda
    glVertex2f(0.0f, H_HUD - 2);
    glVertex2f(larguraJanela, H_HUD - 2);
    glEnd();

    // 3. Desenha a divisória vertical entre o Console e o painel de Informações
    float divisorX = larguraJanela * 0.68f;
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor3f(0.14f, 0.16f, 0.22f);
    glVertex2f(divisorX, H_HUD - 10);
    glVertex2f(divisorX, 10.0f);
    glEnd();

    // 4. --- COLUNA ESQUERDA: CONSOLE DE RETORNO OPENGL (FEEDBACK DE CÓDIGO) ---
    float xConsole = 25.0f;
    float yStart = H_HUD - 25.0f;
    float yStep = 16.0f;

    desenharTexto2D(xConsole, yStart, GLUT_BITMAP_8_BY_13, "// ==================== CONSOLE DE COMANDOS OPENGL ====================", 0.35f, 0.65f, 1.0f);
    
    // Projeção
    std::stringstream ssProj;
    ssProj << "glMatrixMode(GL_PROJECTION); glLoadIdentity(); ";
    if (projecaoAtual == PROJ_PERSPECTIVA) {
        ssProj << "gluPerspective(45.0, aspecto_tela, 1.0, 20.0);";
    } else {
        ssProj << "glOrtho(-2.5, 2.5, -2.5, 2.5, 1.0, 20.0);";
    }
    desenharTexto2D(xConsole, yStart - yStep, GLUT_BITMAP_8_BY_13, ssProj.str(), 0.9f, 0.9f, 0.9f);

    // Câmera (gluLookAt)
    std::stringstream ssCam;
    ssCam << std::fixed << std::setprecision(1);
    ssCam << "gluLookAt(" << eyeX << "f, " << eyeY << "f, " << eyeZ << "f, " 
          << centerX << "f, " << centerY << "f, " << centerZ << "f, " 
          << upX << "f, " << upY << "f, " << upZ << "f); // Camera";
    desenharTexto2D(xConsole, yStart - 2 * yStep, GLUT_BITMAP_8_BY_13, ssCam.str(), 0.9f, 0.9f, 0.9f);

    // Iluminação
    std::stringstream ssIlum;
    if (ilumLigada) {
        ssIlum << "glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); ";
        ssIlum << std::fixed << std::setprecision(1);
        ssIlum << "GLfloat pos[] = {" << luzX << "f, " << luzY << "f, " << luzZ << "f, 1.0f}; glLightfv(GL_LIGHT0, GL_POSITION, pos);";
    } else {
        ssIlum << "glDisable(GL_LIGHTING); // Pipeline de iluminacao desativado";
    }
    desenharTexto2D(xConsole, yStart - 3 * yStep, GLUT_BITMAP_8_BY_13, ssIlum.str(), 0.9f, 0.9f, 0.9f);

    // Transformações
    std::stringstream ssTrans;
    ssTrans << std::fixed << std::setprecision(2);
    ssTrans << "glTranslatef(" << transX << "f, " << transY << "f, " << transZ << "f); ";
    ssTrans << "glRotatef(" << rotX << "f, 1.f, 0.f, 0.f); glRotatef(" << rotY << "f, 0.f, 1.f, 0.f); ";
    ssTrans << "glScalef(" << escalaX << "f, " << escalaY << "f, " << escalaZ << "f);";
    desenharTexto2D(xConsole, yStart - 4 * yStep, GLUT_BITMAP_8_BY_13, ssTrans.str(), 0.9f, 0.9f, 0.9f);

    // Renderização do objeto / curva
    std::stringstream ssObj;
    if (mostrarCurva) {
        ssObj << "glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &pontosControle[0][0]); glEnable(GL_MAP1_VERTEX_3);";
    } else {
        if (texturaAtiva) {
            ssObj << "glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, id_tex); ";
        }
        switch (objetoAtual) {
            case OBJ_CUBO: ssObj << "glutSolidCube(1.5f);"; break;
            case OBJ_ESFERA: ssObj << "glutSolidSphere(1.0f, 32, 32);"; break;
            case OBJ_BULE: ssObj << "glutSolidTeapot(0.8f);"; break;
            case OBJ_TRIANGULO: ssObj << "glBegin(GL_TRIANGLES); /* ... vertices ... */ glEnd();"; break;
            case OBJ_QUADRILATERO: ssObj << "glBegin(GL_QUADS); /* ... vertices ... */ glEnd();"; break;
        }
        if (texturaAtiva) {
            ssObj << " glDisable(GL_TEXTURE_2D);";
        }
    }
    desenharTexto2D(xConsole, yStart - 5 * yStep, GLUT_BITMAP_8_BY_13, ssObj.str(), 0.9f, 0.9f, 0.9f);

    // Rodapé de instruções rápidas
    std::string rodape = "Botoes: SETAS (Transformar) | W/S/A/D/Q/E (Mover Camera) | I/K/J/L/U/O (Mover Luz) | Mouse (Arrastar Bezier)";
    desenharTexto2D(xConsole, 15.0f, GLUT_BITMAP_8_BY_13, rodape, 0.6f, 0.7f, 0.8f);

    // 5. --- COLUNA DIREITA: PAINEL DE INFORMAÇÕES DE STATUS ---
    float xInfo = divisorX + 20.0f;
    desenharTexto2D(xInfo, yStart, GLUT_BITMAP_9_BY_15, "INFORMAÇÕES", 0.0f, 0.9f, 0.4f);

    desenharTexto2D(xInfo, yStart - 1.2f * yStep, GLUT_BITMAP_8_BY_13, "FPS: 60.0 (Fixo)", 0.8f, 0.8f, 0.8f);

    // Objeto e malha
    std::string objNome = "Nenhum";
    std::string vertices = "0";
    std::string faces = "0";
    std::string modo = "Nenhum";
    if (mostrarCurva) {
        objNome = "Curva de Bezier";
        vertices = "4 (Controle)";
        faces = "0";
        modo = "GL_LINE_STRIP";
    } else {
        switch (objetoAtual) {
            case OBJ_CUBO: objNome = "Cubo 3D"; vertices = "8"; faces = "6"; modo = texturaAtiva ? "GL_QUADS + Tex" : "GL_QUADS"; break;
            case OBJ_ESFERA: objNome = "Esfera 3D"; vertices = "1024"; faces = "960"; modo = "GL_TRIANGLE_STRIP"; break;
            case OBJ_BULE: objNome = "Bule de Cha"; vertices = "~2000"; faces = "~2000"; modo = "GL_TRIANGLES"; break;
            case OBJ_TRIANGULO: objNome = "Triangulo 2D"; vertices = "3"; faces = "1"; modo = "GL_TRIANGLES"; break;
            case OBJ_QUADRILATERO: objNome = "Quadrilatero 2D"; vertices = "4"; faces = "1"; modo = "GL_QUADS"; break;
        }
    }
    desenharTexto2D(xInfo, yStart - 2.2f * yStep, GLUT_BITMAP_8_BY_13, "Objeto: " + objNome, 0.8f, 0.8f, 0.8f);
    desenharTexto2D(xInfo, yStart - 3.2f * yStep, GLUT_BITMAP_8_BY_13, "Vertices: " + vertices + " | Faces: " + faces, 0.8f, 0.8f, 0.8f);
    desenharTexto2D(xInfo, yStart - 4.2f * yStep, GLUT_BITMAP_8_BY_13, "Modo: " + modo, 0.8f, 0.8f, 0.8f);

    // Modo ativo de transformação
    std::string transModo = "Nenhum";
    switch (transformacaoAtiva) {
        case TRANS_ROTACAO: transModo = "ROTACAO (Setas)"; break;
        case TRANS_TRANSLACAO: transModo = "TRANSLACAO XY (Setas)"; break;
        case TRANS_ESCALA: transModo = "ESCALA UNIFORME (Setas)"; break;
    }
    desenharTexto2D(xInfo, yStart - 5.2f * yStep, GLUT_BITMAP_8_BY_13, "Modo Ativo: " + transModo, 1.0f, 0.85f, 0.2f);

    // Restaura as matrizes anteriores para não bagunçar o pipeline 3D da cena principal
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
}
