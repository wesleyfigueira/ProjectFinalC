#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define TAMANHO_MAX_COBRA 100

typedef struct {
    int x;
    int y;
} Posicao;

typedef union {
    int valor;
    char texto[10];
} Pontuacao;

Posicao corpo_cobra[TAMANHO_MAX_COBRA];
int tamanho_cobra = 3;
int direcao = 77; // 72 (cima), 75 (esquerda), 80 (baixo), 77 (direita)
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
void exibirCobra(Posicao *cobra, int tamanho) {
    screenSetColor(GREEN, DARKGRAY);
    for (int i = 0; i < tamanho; i++) {
        screenGotoxy(cobra[i].x, cobra[i].y);
        printf("●");
    }
}

// Limpa a cobra da tela
void limparCobra(Posicao *cobra, int tamanho) {
    screenSetColor(DARKGRAY, DARKGRAY);
    for (int i = 0; i < tamanho; i++) {
        screenGotoxy(cobra[i].x, cobra[i].y);
        printf(" ");
    }
}

// Exibe a comida
void exibirComida(Posicao *comida) {
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(comida->x, comida->y);
    printf("🍎");
}

// Exibe a pontuação
void exibirPontuacao(int tamanho) {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(0, 0);
    sprintf(pontuacao_atual.texto, "%d", tamanho - 3);
    printf("Pontuação:| %s |", pontuacao_atual.texto);
}

// Atualiza a velocidade conforme a cobra cresce
void atualizarVelocidade(int tamanho_atual) {
    int novo_intervalo = 150 - (tamanho_atual - 3) * 5;

    

    if (novo_intervalo < 50) {
        novo_intervalo = 50;
    }
    timerInit(novo_intervalo);
};

// Atualiza a posição da cobra, verifica colisões e comida
void atualizarCobra(Posicao *cobra, int *tamanho, int *direcao, Posicao *comida, int *jogo_encerrado) {
    for (int i = *tamanho - 1; i > 0; i--) {
        cobra[i] = cobra[i - 1];
    }

    switch (*direcao) {

        case 72: cobra[0].y--;
        break; // Cima
        case 75: cobra[0].x--; 
        break; // Esquerda
        case 80: cobra[0].y++; 
        break; // Baixo
        case 77: cobra[0].x++; 
        break; // Direita
    }

    // Colisão com bordas
    if (cobra[0].x <= MINX || cobra[0].x >= MAXX || cobra[0].y <= MINY || cobra[0].y >= MAXY) {
        *jogo_encerrado = 1;
    }

    // Colisão com corpo
    for (int i = 1; i < *tamanho; i++) {
        if (cobra[0].x == cobra[i].x && cobra[0].y == cobra[i].y) {
            *jogo_encerrado = 1;
        }
    }

    // Comeu a comida
    if (abs(cobra[0].x - comida->x) <= 1 && cobra[0].y == comida->y) {
        if (*tamanho < TAMANHO_MAX_COBRA) {
            (*tamanho)++;
        }
        gerarComida(comida);
        atualizarVelocidade(*tamanho); // Aumenta a velocidade!
    }
}

// Lida com entrada do jogador
void lidarEntrada(int *direcao) {
    int tecla = readch();
    if (tecla == 27 && keyhit()) {
        if (readch() == 91) {
            tecla = readch();
            switch (tecla) {
                case 65: if (*direcao != 80) *direcao = 72; break;
                case 66: if (*direcao != 72) *direcao = 80; break;
                case 67: if (*direcao != 75) *direcao = 77; break;
                case 68: if (*direcao != 77) *direcao = 75; break;
            }
        }
    }
}

int main() {
    screenInit(1);
    keyboardInit();
    timerInit(150);

    inicializarCobra(corpo_cobra, &tamanho_cobra);
    gerarComida(&comida);

    while (!jogo_encerrado) {
        if (keyhit()) {
            lidarEntrada(&direcao);
        }

        if (timerTimeOver()) {
            limparCobra(corpo_cobra, tamanho_cobra);
            atualizarCobra(corpo_cobra, &tamanho_cobra, &direcao, &comida, &jogo_encerrado);
            exibirCobra(corpo_cobra, tamanho_cobra);
            exibirComida(&comida);
            exibirPontuacao(tamanho_cobra);
            screenUpdate();
        }
    }

    // Fim de jogo
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(MAXX / 2 - 7, MAXY / 2);
    printf("FIM DE JOGO!");
    screenGotoxy(MAXX / 2 - 7, MAXY / 2 + 1);
    printf("Pontuação Final: %d", tamanho_cobra - 3);
    screenUpdate();
    getchar(); 


    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
