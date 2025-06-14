#include <stdio.h>

#define TAMANHO_TABULEIRO 10  // tamanho do tabuleiro
#define TAMANHO_NAVIO 3       // tamanho fixo dos navios
#define AGUA 0                // representação da água
#define NAVIO 3               // representação das partes do navio

// Inicializa todas as posições do tabuleiro com água (0)
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++)
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++)
            tabuleiro[linha][coluna] = AGUA;
}

// Verifica se é possível posicionar um navio sem sair dos limites ou colidir com outro navio
// horizontal == 1 => navio horizontal; horizontal == 0 => navio vertical
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int linha, int coluna, int horizontal) {
    if (horizontal) {
        // verifica limite à direita
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        // verifica sobreposição
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++)
            if (tabuleiro[linha][j] != AGUA) return 0;
    } else {
        // verifica limite abaixo
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        // verifica sobreposição
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++)
            if (tabuleiro[i][coluna] != AGUA) return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro, marcando as células com NAVIO (3)
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int linha, int coluna, int horizontal) {
    if (horizontal) {
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++)
            tabuleiro[linha][j] = NAVIO;
    } else {
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++)
            tabuleiro[i][coluna] = NAVIO;
    }
}

// Exibe o tabuleiro no console, com índices de linhas e colunas
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        printf("%2d ", j);
    printf("\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializar_tabuleiro(tabuleiro);

    // Coordenadas definidas diretamente no código:
    // Primeiro navio: horizontal a partir de (2,3)
    int linha1 = 2, coluna1 = 3, orientacao1 = 1;  // 1 = horizontal
    // Segundo navio: vertical a partir de (5,7)
    int linha2 = 5, coluna2 = 7, orientacao2 = 0;  // 0 = vertical

    // Valida e posiciona o primeiro navio
    if (!pode_posicionar(tabuleiro, linha1, coluna1, orientacao1)) {
        printf("Erro: não é possível posicionar o navio horizontal em (%d,%d)\n", linha1, coluna1);
        return 1;
    }
    posicionar_navio(tabuleiro, linha1, coluna1, orientacao1);

    // Valida e posiciona o segundo navio
    if (!pode_posicionar(tabuleiro, linha2, coluna2, orientacao2)) {
        printf("Erro: não é possível posicionar o navio vertical em (%d,%d)\n", linha2, coluna2);
        return 1;
    }
    posicionar_navio(tabuleiro, linha2, coluna2, orientacao2);

    // Exibe o tabuleiro
    exibir_tabuleiro(tabuleiro);

    return 0;
}
