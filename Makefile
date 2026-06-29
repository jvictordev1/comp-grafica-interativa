# =========================================================================
# MAKEFILE PARA COMPILAÇÃO DO SIMULADOR OPENGL (UNIVASF - 2026.1)
# =========================================================================

# Compilador C++
CXX = g++

# Flags do compilador (ativa avisos e adiciona pasta de headers ao path de busca)
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

# Detecção do Sistema Operacional (OS)
ifeq ($(OS),Windows_NT)
    # Configurações para Windows (MinGW/MSYS2)
    TARGET = simulador.exe
    LIBS = -lopengl32 -lglu32 -lfreeglut
    CLEAN_CMD = rm -f $(TARGET) 2>/dev/null || del /q /f $(TARGET) 2>nul || true
else
    # Configurações para Linux e outros sistemas Unix-like
    TARGET = simulador
    LIBS = -lGL -lGLU -lglut
    CLEAN_CMD = rm -f $(TARGET)
endif

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

# Regra principal (padrão)
all: $(TARGET)

# Linkagem final do executável
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Limpeza de arquivos compilados
clean:
	$(CLEAN_CMD)

.PHONY: all clean
