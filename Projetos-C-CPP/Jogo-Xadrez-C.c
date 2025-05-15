#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char tipo;  // 'P' para peão, 'R' para torre, etc.
    char cor;   // 'B' para branco, 'P' para preto
} Peca;

#define VAZIO (Peca){' ', ' '}

void inicializarTabuleiro(Peca tab[8][8]) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            tab[i][j] = VAZIO;

    // Peões
    for (int j = 0; j < 8; j++) {
        tab[1][j] = (Peca){'P', 'P'};
        tab[6][j] = (Peca){'P', 'B'};
    }

    // Peças principais
    char pecas[] = {'T', 'C', 'B', 'D', 'R', 'B', 'C', 'T'};
    for (int j = 0; j < 8; j++) {
        tab[0][j] = (Peca){pecas[j], 'P'};
        tab[7][j] = (Peca){pecas[j], 'B'};
    }
}

void imprimirTabuleiro(Peca tab[8][8]) {
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", tab[i][j].tipo);
        }
        printf("\n");
    }
    printf("\n");
}

void moverPeca(Peca tab[8][8], int x1, int y1, int x2, int y2) {
    tab[x2][y2] = tab[x1][y1];
    tab[x1][y1] = VAZIO;
}

int movimentoValido(Peca tab[8][8], int x1, int y1, int x2, int y2) {
    Peca p = tab[x1][y1];

    if (p.tipo == ' ') return 0; // Nenhuma peça na posição inicial

    // Peões só andam para frente (simples, sem capturas ainda)
    if (p.tipo == 'P') {
        int direcao = (p.cor == 'B') ? -1 : 1;
        if (x2 == x1 + direcao && y1 == y2 && tab[x2][y2].tipo == ' ') {
            return 1;
        }
    }

    // Outras regras de movimento das peças ainda precisam ser implementadas

    return 0;
}

void jogo() {
    Peca tabuleiro[8][8];
    inicializarTabuleiro(tabuleiro);
    
    int turno = 0;  
    char entrada[10];

    while (1) {
        imprimirTabuleiro(tabuleiro);
        
        printf("Jogador %d, digite seu movimento (ex: e2e4): ", turno);
        scanf("%s", entrada);

        int y1 = entrada[0] - 'a';
        int x1 = 8 - (entrada[1] - '0');
        int y2 = entrada[2] - 'a';
        int x2 = 8 - (entrada[3] - '0');

        if (movimentoValido(tabuleiro, x1, y1, x2, y2)) {
            moverPeca(tabuleiro, x1, y1, x2, y2);
            turno = 1 - turno;
        } else {
            printf("Movimento inválido! Tente novamente.\n");
        }
    }
}

int main() {
    jogo();
    return 0;
}
