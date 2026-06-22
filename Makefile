# =========================================================================
# MAKEFILE PARA COMPILAÇÃO DO SIMULADOR OPENGL (UNIVASF - 2026.1)
# =========================================================================

# Compilador C++
CXX = g++

# Flags do compilador (ativa avisos e adiciona pasta de headers ao path de busca)
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

# Bibliotecas do OpenGL e GLUT necessárias para compilação no Linux
LIBS = -lGL -lGLU -lglut

# Caminho para os cabeçalhos (.h)
HEADERS = include/Globals.h \
          include/Camera.h \
          include/Objetos.h \
          include/Iluminacao.h \
          include/Curvas.h \
          include/UI.h

# Caminho para os arquivos de código-fonte (.cpp)
SRCS = src/main.cpp \
       src/Globals.cpp \
       src/Camera.cpp \
       src/Objetos.cpp \
       src/Iluminacao.cpp \
       src/Curvas.cpp \
       src/UI.cpp

# Nome do executável final gerado
TARGET = simulador

# Regra principal (padrão)
all: $(TARGET)

# Linkagem final do executável
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Limpeza de arquivos compilados
clean:
	rm -f $(TARGET)

.PHONY: all clean
