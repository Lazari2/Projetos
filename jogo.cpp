#include <stdio.h>

// Jogo da velha:
// Nome> Guilherme Augusto Lázari

void imprimirTabuleiro(char tabuleiro[3][3]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            printf("-----------\n");
        }
    }
    printf("\n");
}


int verificarVitoria(char tabuleiro[3][3], char jogador) {

    for (int i = 0; i < 3; i++) {
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) ||
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) {
            return 1;
        }
    }
    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) ||
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) {
        return 1;
    }
    return 0;
}

int main() {
    char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int jogadas = 0;
    char jogadorAtual = 'X';

    printf("Jogo da Velha:\n");

    while (1) {
        imprimirTabuleiro(tabuleiro);
        printf("Jogador %c. Informe a linha (1-3) e a coluna (1-3).\n", jogadorAtual);
        int linha, coluna;
        scanf("%d %d", &linha, &coluna);

        if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || tabuleiro[linha - 1][coluna - 1] != ' ') {
            printf("Jogada invalida. Tente novamente.\n");
            continue;
        }

        tabuleiro[linha - 1][coluna - 1] = jogadorAtual;
        jogadas++;

        if (verificarVitoria(tabuleiro, jogadorAtual)) {
            imprimirTabuleiro(tabuleiro);
            printf("Jogador %c! venceu!\n", jogadorAtual);
            printf ("\nNumero total de jogadas da partida: %d", jogadas);
            break;
        }

        if (jogadas == 9) {
            imprimirTabuleiro(tabuleiro);
            printf("Deu veia.\n");
            break;
        }

            if (jogadorAtual == 'X') {
                jogadorAtual = 'O';
                }
            else {
            jogadorAtual = 'X';
            }

    }

    return 0;
}
