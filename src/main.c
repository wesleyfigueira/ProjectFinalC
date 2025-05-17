/**
 * jogo_da_cobrinha.c
 * Criado em 23 de agosto de 2023
 * Autor: Tiago Barros (adaptado por ChatGPT)
 * Baseado no "From C to C++ course - 2002"
 */

#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define TAMANHO_MAX_COBRA 100

// Estrutura que define uma posição na tela
typedef struct {
    int x;
    int y;
} Posicao;

// União para armazenar a pontuação de maneira flexível
typedef union {
    int valor;
    char texto[10];
} Pontuacao;

Posicao corpo_cobra[TAMANHO_MAX_COBRA];
int tamanho_cobra = 3;
int direcao = 77; // Direção inicial: 72 (cima), 75 (esquerda), 80 (baixo), 77 (direita)
Posicao comida;
int jogo_encerrado = 0;
Pontuacao pontuacao_atual;

// Inicializa a cobra com posições iniciais
void inicializarCobra(Posicao *cobra, int *tamanho) {
    for (int i = 0; i < *tamanho; i++) {
        cobra[i].x = 10 - i;
        cobra[i].y = 10;
    }
}

// Gera uma nova posição para a comida
void gerarComida(Posicao *comida) {
    comida->x = MINX + 2 + (rand() % (MAXX - MINX - 4));
    comida->y = MINY + 2 + (rand() % (MAXY - MINY - 4));
}

// Exibe a cobra na tela
void exibirCobra() {
    screenSetColor(GREEN, DARKGRAY);
    for (int i = 0; i < tamanho_cobra; i++) {
        screenGotoxy(corpo_cobra[i].x, corpo_cobra[i].y);
        printf("*");
    }
}

// Remove a exibição da cobra na tela
void limparCobra() {
    screenSetColor(DARKGRAY, DARKGRAY);
    for (int i = 0; i < tamanho_cobra; i++) {
        screenGotoxy(corpo_cobra[i].x, corpo_cobra[i].y);
        printf(" ");
    }
}

// Exibe a comida na tela
void exibirComida() {
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(comida.x, comida.y);
    printf("L");
}

// Exibe a pontuação atual na tela
void exibirPontuacao(Pontuacao *p, int tamanho_cobra) {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(0, 0);
    sprintf(p->texto, "%d", tamanho_cobra - 5);
    printf("Pontuação: %s", p->texto);
}

// Atualiza o estado da cobra (movimento e colisões)
void atualizarCobra(Posicao *cobra, int *tamanho, int *direcao, Posicao *comida, int *jogo_encerrado) {
    for (int i = *tamanho - 1; i > 0; i--) {
        cobra[i] = cobra[i - 1];
    }

    switch (*direcao) {
        case 72: cobra[0].y--; break; // Cima
        case 75: cobra[0].x--; break; // Esquerda
        case 80: cobra[0].y++; break; // Baixo
        case 77: cobra[0].x++; break; // Direita
    }

    if (cobra[0].x <= MINX || cobra[0].x >= MAXX || cobra[0].y <= MINY || cobra[0].y >= MAXY) {
        *jogo_encerrado = 1;
    }

    for (int i = 1; i < *tamanho; i++) {
        if (cobra[0].x == cobra[i].x && cobra[0].y == cobra[i].y) {
            *jogo_encerrado = 1;
        }
    }

    if (cobra[0].x == comida->x && cobra[0].y == comida->y) {
        if (*tamanho < TAMANHO_MAX_COBRA) {
            (*tamanho)++;
        }
        gerarComida(comida);
    }
}

// Lida com a entrada do usuário (teclas)
void lidarEntrada() {
    int tecla = readch();
    if (tecla == 27 && keyhit()) { // Detecta sequência de escape
        if (readch() == 91) { // Teclas de seta
            tecla = readch();
            switch (tecla) {
                case 65: if (direcao != 80) direcao = 72; break; // Cima
                case 66: if (direcao != 72) direcao = 80; break; // Baixo
                case 67: if (direcao != 75) direcao = 77; break; // Direita
                case 68: if (direcao != 77) direcao = 75; break; // Esquerda
            }
        }
    }
}

int main() {
    screenInit(1);
    keyboardInit();
    timerInit(150); // Define a velocidade da cobra (tempo em ms)

    inicializarCobra(corpo_cobra, &tamanho_cobra);
    gerarComida(&comida);

    while (!jogo_encerrado) {
        if (keyhit()) {
            lidarEntrada();
        }

        if (timerTimeOver()) {
            limparCobra();
            atualizarCobra(corpo_cobra, &tamanho_cobra, &direcao, &comida, &jogo_encerrado);
            exibirCobra();
            exibirComida();
            exibirPontuacao(&pontuacao_atual, tamanho_cobra);
            screenUpdate();
        }
    }

    // Tela de fim de jogo
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(MAXX / 2 - 3, MAXY / 2);
    printf("FIM DE JOGO!");
    screenGotoxy(MAXX / 2 - 4, MAXY / 2 + 1);
    printf("Pontuação Final: %d", tamanho_cobra - 3);
    screenUpdate();

    // Limpeza
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
