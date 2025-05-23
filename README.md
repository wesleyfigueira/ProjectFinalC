# Jogo Snake 🐍

## Descrição

Este projeto é uma implementação clássica do jogo Snake, onde o jogador controla uma cobra que se move pela tela, com o objetivo de comer frutas para crescer e aumentar sua pontuação. O jogo termina quando a cobra colide com as paredes ou com seu próprio corpo.

## Mecânicas do Jogo

- **Movimento**: A cobra se move em uma direção (cima, baixo, esquerda, direita).
- **Crescimento**: A cobra aumenta de tamanho ao comer as frutas na tela.
- **Controles**: Use as teclas W (cima), A (esquerda), S (baixo) e D (direita) para mudar a direção da cobra.
- **Colisões**: O jogo termina se a cobra colidir com as paredes ou com seu próprio corpo.
- **Frutas**: Frutas aparecem aleatoriamente na tela. Comer uma fruta faz a cobra crescer e gera uma nova fruta.
- **Loop do Jogo**: O jogo segue um ciclo contínuo de capturar entrada do jogador, mover a cobra, verificar colisões e redesenhar a tela.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
github/
├── include/
│   ├── keyboard.h    # Declarações das funções do teclado
│   ├── screen.h      # Declarações das funções de tela
│   └── timer.h       # Declarações das funções de temporizador
├── src/
│   ├── jogo/         # Código da lógica do jogo
│   ├── keyboard.c    # Implementação das funções do teclado
│   ├── main.c        # Função principal (main)
│   ├── screen.c      # Implementação das funções de tela
│   └── timer.c       # Implementação das funções de temporizador
└── game              # Arquivo ou pasta relacionado ao núcleo do jogo

```

## Como Compilar e Executar

1. Certifique-se de ter um compilador C instalado (como GCC).
2. Verifique se o seu sistema operacional é compatível com as bibliotecas padrão de C. Se estiver usando o Windows você vai precisa instalar o Linux com o WSL (Windows Subsystem for Linux)
3. Clone o repositório ou baixe os arquivos do projeto.
4. Navegue até a pasta `src/` e compile o projeto usando o comando:
    
    ```bash
    gcc src/*.c -Iinclude -o game./game
        
    ```
## Dependências

- Bibliotecas padrão do C: `stdio.h`, `stdlib.h`, `string.h`.
- Bibliotecas específicas do projeto: `screen.h`, `keyboard.h`, `timer.h`.

## Nome dos Membros e GitHub: 

Allan D'Avila Souza Filho (@allandavilafilho)
Fábio Gomes dos Reis (@fabiogreis15)
Victor Gabriel Figueira dos Santos (@FIGU3IR4)
Wesley Wandelson Figueira dos Santos (wesleyfigueira)

Nome da disciplina: Programação Imperativa e Funcional - 2025.1

Nome do professor: Diego de Freitas Bezerra

Nome da instituição de ensino: CESAR School.

## Observações

- O jogo foi desenvolvido como parte de um projeto acadêmico ou pessoal pelos autores listados.
- Para mais detalhes sobre a implementação, consulte os arquivos fonte no diretório `src/`.

Divirta-se! 🐍
