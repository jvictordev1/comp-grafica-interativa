# Simulador Interativo OpenGL

Este projeto é um simulador didático interativo em C++/OpenGL desenvolvido para a disciplina de Computação Gráfica (2026.1) do curso de Engenharia de Computação da UNIVASF (Universidade Federal do Vale do São Francisco) pelos discentes José Victor Rebouças, Augusto Hawdani e Luiz Carlos Gonçalves.

O objetivo do simulador é auxiliar no aprendizado ativo de computação gráfica, renderizando em tempo real a cena 3D/2D juntamente com uma interface de console HUD que exibe o feedback exato da sintaxe de comandos OpenGL correspondentes ao estado atual.

---

## 🚀 Como Compilar e Executar

### 1. Requisitos do Sistema

Para executar o simulador no Linux (Ubuntu/Debian e derivados), certifique-se de instalar as dependências de desenvolvimento do compilador C++, Make e as bibliotecas gráficas do OpenGL, GLU e FreeGLUT.

Execute o seguinte comando no terminal para instalar todos os pacotes necessários:

```bash
sudo apt-get update
sudo apt-get install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

### 2. Compilação

Com as dependências instaladas, navegue até a raiz do projeto e execute o comando `make` utilizando o arquivo utilitário de build:

```bash
# Compila todos os arquivos e gera o executável 'simulador'
make
```

### 3. Execução

Para iniciar o simulador, execute o executável gerado:

```bash
./simulador
```

### 4. Limpeza

Para remover o executável compilado e limpar o espaço de build:

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
