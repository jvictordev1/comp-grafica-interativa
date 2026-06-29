# Simulador Interativo OpenGL

Este projeto é um simulador didático interativo em C++/OpenGL desenvolvido para a disciplina de Computação Gráfica (2026.1) do curso de Engenharia de Computação da UNIVASF (Universidade Federal do Vale do São Francisco) pelos discentes José Victor Rebouças, Augusto Hawdani e Luiz Carlos Gonçalves.

O objetivo do simulador é auxiliar no aprendizado ativo de computação gráfica, renderizando em tempo real a cena 3D/2D juntamente com uma interface de console HUD que exibe o feedback exato da sintaxe de comandos OpenGL correspondentes ao estado atual.

---

## 🚀 Como Compilar e Executar

### 1. Requisitos do Sistema

#### Linux (Ubuntu/Debian e derivados)
Certifique-se de instalar as dependências de desenvolvimento do compilador C++, Make e as bibliotecas gráficas do OpenGL, GLU e FreeGLUT. Execute o seguinte comando no terminal:

```bash
sudo apt-get update
sudo apt-get install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

#### Windows (via MSYS2 / MinGW)
1. Instale o gerenciador de pacotes [MSYS2](https://www.msys2.org/).
2. Abra o terminal **MSYS2 MinGW 64-bit** e instale o compilador g++, make e as bibliotecas do FreeGLUT com o comando:
   ```bash
   pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-freeglut make
   ```
3. Certifique-se de executar os comandos de compilação dentro do terminal do MinGW ou adicione a pasta de binários (geralmente `C:\msys64\mingw64\bin`) ao `PATH` do seu Windows.

### 2. Compilação

Com as dependências instaladas, navegue até a raiz do projeto e execute o comando `make`:

```bash
# Compila o projeto detectando o SO e gerando 'simulador' (Linux) ou 'simulador.exe' (Windows)
make
```

### 3. Execução

Para iniciar o simulador, execute o executável correspondente ao seu sistema operacional:

- **No Linux**:
  ```bash
  ./simulador
  ```
- **No Windows**:
  ```bash
  ./simulador.exe
  ```

### 4. Limpeza

Para remover o executável compilado e limpar os arquivos temporários:

```bash
make clean
```

---

## 🛠️ Estrutura do Projeto

O projeto foi refatorado de forma limpa e modular em C++11, organizado sob o seguinte layout:

- **`include/`**: Contém todos os arquivos de cabeçalho do projeto (`.h`).
- **`src/`**: Contém os arquivos de implementação do código-fonte (`.cpp`).
- **`Makefile`**: Script de automação para compilação e linkagem do executável final.
- **`simulador`**: Arquivo executável final após a compilação.

---

## 🎮 Controles de Interatividade e Atalhos

O simulador é subdividido em 5 módulos que podem ser navegados clicando com o **botão direito do mouse** sobre qualquer ponto da janela para abrir o menu contextual.

### 🎥 Controle Geral de Câmera (`gluLookAt`)

Movimente o observador da câmera livremente pelo espaço 3D a qualquer momento através do teclado convencional:

- `W` / `S`: Mover câmera para frente/trás (ajusta `eyeZ`).
- `A` / `D`: Mover câmera para a esquerda/direita (ajusta `eyeX`).
- `Q` / `E`: Mover câmera para cima/baixo (ajusta `eyeY`).
- `R`: Reseta a câmera para as coordenadas padrão originais.

### 💡 Controle Geral de Iluminação (`GL_LIGHT0`)

Desloque a fonte de iluminação espacial interativa para visualizar as variações de sombra sob as primitivas:

- `I` / `K`: Deslocar fonte de luz para cima/baixo (ajusta `luzY`).
- `J` / `L`: Deslocar fonte de luz para a esquerda/direita (ajusta `luzX`).
- `U` / `O`: Deslocar fonte de luz para frente/trás (ajusta `luzZ`).
- `P`: Reseta a luz para a posição padrão de iluminação.

### 📐 Controle de Objetos e Transformações

Ao selecionar um objeto e um tipo de transformação pelo menu contextual (Rotação, Translação ou Escala), use as **Setas Teclado** (`UP`, `DOWN`, `LEFT`, `RIGHT`) para fazer ajustes:

- **Em Rotação**: Setas giram o objeto em torno dos eixos X e Y.
- **Em Translação**: Setas deslocam o objeto no plano bidimensional XY.
- **Em Escala**: Seta `UP` aumenta a escala uniforme do objeto e Seta `DOWN` diminui (limite de segurança de escala > 0).

### 🖱️ Manipulação Direta de Curvas (Bézier)

Quando o módulo de Curvas estiver ativo (`Alternar p/ Curva de Bezier` no menu):

- Passe o mouse por cima dos pontos de controle vermelhos.
- Clique com o **botão esquerdo do mouse** sobre um ponto de controle para selecioná-lo (o ponto ficará destacado em amarelo).
- Mantenha pressionado e **arraste o mouse** para mover o ponto livremente no plano de desenho, modificando a Curva de Bézier em tempo real.
