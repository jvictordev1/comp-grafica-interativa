#include "Objetos.h"
#include "Globals.h"

void gerarTexturaXadrez() {
    const int texLargura = 64;
    const int texAltura = 64;
    GLubyte imagemXadrez[texAltura][texLargura][4];

    for (int i = 0; i < texAltura; i++) {
        for (int j = 0; j < texLargura; j++) {
            int c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;
            imagemXadrez[i][j][0] = (GLubyte)c;       
            imagemXadrez[i][j][1] = (GLubyte)(c * 0.6f); 
            imagemXadrez[i][j][2] = (GLubyte)(c * 0.2f); 
            imagemXadrez[i][j][3] = (GLubyte)255;     
        }
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &checkboardTexID);
    glBindTexture(GL_TEXTURE_2D, checkboardTexID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texLargura, texAltura, 
                 0, GL_RGBA, GL_UNSIGNED_BYTE, imagemXadrez);
}

void renderizarCuboTexturizado() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, checkboardTexID);
    
    glBegin(GL_QUADS);
    // Face Frontal
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.75f, -0.75f,  0.75f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.75f, -0.75f,  0.75f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.75f,  0.75f,  0.75f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f,  0.75f,  0.75f);
    // Face Traseira
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.75f, -0.75f, -0.75f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.75f,  0.75f, -0.75f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.75f,  0.75f, -0.75f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.75f, -0.75f, -0.75f);
    // Face Superior
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f,  0.75f, -0.75f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.75f,  0.75f,  0.75f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.75f,  0.75f,  0.75f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.75f,  0.75f, -0.75f);
    // Face Inferior
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.75f, -0.75f, -0.75f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.75f, -0.75f, -0.75f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.75f, -0.75f,  0.75f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.75f, -0.75f,  0.75f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void renderizarObjetoAtual() {
    // Cor sólida para o material/vértices do objeto
    glColor3f(0.0f, 0.8f, 0.2f); 
    
    // Definições de propriedades de material sob o pipeline de iluminação
    GLfloat mat_difusa[] = { 0.0f, 0.8f, 0.2f, 1.0f };   // Verde brilhante sob luz direta
    GLfloat mat_ambiente[] = { 0.0f, 0.3f, 0.0f, 1.0f }; // Tom escuro refletido nas sombras
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

    if (texturaAtiva && objetoAtual == OBJ_CUBO) {
        renderizarCuboTexturizado();
    } else {
        if (texturaAtiva) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, checkboardTexID);
            // Geração automática de coordenadas para esferas, bules, etc.
            glEnable(GL_TEXTURE_GEN_S); 
            glEnable(GL_TEXTURE_GEN_T);
        }

        switch (objetoAtual) {
            case OBJ_CUBO:
                glutSolidCube(1.5f); 
                break; 
            case OBJ_ESFERA:
                glutSolidSphere(1.0f, 32, 32); 
                break; 
            case OBJ_BULE:
                glutSolidTeapot(0.8f); 
                break; 
            case OBJ_TRIANGULO:
                glBegin(GL_TRIANGLES); 
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
                glEnd();
                break;
            case OBJ_QUADRILATERO:
                glBegin(GL_QUADS);
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
                glEnd();
                break;
        }

        if (texturaAtiva) {
            glDisable(GL_TEXTURE_GEN_S); 
            glDisable(GL_TEXTURE_GEN_T);
            glDisable(GL_TEXTURE_2D);
        }
    }
}
