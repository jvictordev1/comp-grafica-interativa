#include "Iluminacao.h"
#include "Globals.h"

// Coordenadas padrão da fonte de luz
float luzX = 3.0f;
float luzY = 4.0f;
float luzZ = 3.0f;

void inicializarIluminacao() {
    glEnable(GL_LIGHT0);
    
    // Configurações padrão da fonte de luz 0 (GL_LIGHT0)
    GLfloat luzAmbiente[]  = { 0.3f, 0.3f, 0.3f, 1.0f }; 
    GLfloat luzDifusa[]    = { 0.9f, 0.9f, 0.9f, 1.0f }; 
    GLfloat luzEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Configuração de material padrão para reagir à iluminação
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat especularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularMaterial);
    glMateriali(GL_FRONT, GL_SHININESS, 80);
}

void aplicarIluminacao() {
    if (ilumLigada) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        
        // A posição da luz deve ser aplicada no modelview atual para sofrer transformações (ou se manter no espaço)
        GLfloat posicao[] = { luzX, luzY, luzZ, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, posicao);
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
}

void resetarLuz() {
    luzX = 3.0f;
    luzY = 4.0f;
    luzZ = 3.0f;
}

void gerenciarTecladoLuz(unsigned char key) {
    float passo = 0.1f;

    switch (key) {
        case 'i':
        case 'I':
            luzY += passo; // Sobe a luz
            break;
        case 'k':
        case 'K':
            luzY -= passo; // Desce a luz
            break;
        case 'j':
        case 'J':
            luzX -= passo; // Move a luz para a esquerda
            break;
        case 'l':
        case 'L':
            luzX += passo; // Move a luz para a direita
            break;
        case 'u':
        case 'U':
            luzZ -= passo; // Move a luz para frente
            break;
        case 'o':
        case 'O':
            luzZ += passo; // Move a luz para trás
            break;
        case 'p':
        case 'P':
            resetarLuz(); // Reseta para a posição padrão
            break;
    }
}
