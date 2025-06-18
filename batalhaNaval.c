#include <stdio.h>

#define TAMANHO_TABULEIRO 10  // tamanho do tabuleiro
#define TAMANHO_NAVIO     3   // tamanho fixo dos navios
#define AGUA              0   // representação da água
#define NAVIO             3   // representação das partes do navio

// Inicializa todas as posições do tabuleiro com água (0)
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }
}

// Verifica se é possível posicionar um navio de tamanho fixo sem sair dos limites
// e sem colidir com outro navio. O deslocamento (dLinha, dColuna) define a orientação:
// horizontal (0,1), vertical (1,0), diagonal descendente (1,1) ou ascendente (1,-1).
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int linha, int coluna,
                    int dLinha, int dColuna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        // verifica limites do tabuleiro
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;
        // verifica sobreposição com outro navio
        if (tabuleiro[l][c] != AGUA)
            return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro marcando com NAVIO (3) nas posições calculadas
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int linha, int coluna,
                      int dLinha, int dColuna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        tabuleiro[l][c] = NAVIO;
    }
}

// Exibe o tabuleiro no console com índices de linha e coluna
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // cabeçalho de colunas
    printf("   ");
    for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
        printf(" %2d", c);
    }
    printf("\n");

    // cada linha com seu índice
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        printf("%2d ", l);
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            printf("  %d", tabuleiro[l][c]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // 1) Inicializa o tabuleiro com água
    inicializar_tabuleiro(tabuleiro);

    // Definição dos quatro navios (tamanho = 3) com orientação definida por (dLinha, dColuna)
    //  - Navio 1: horizontal a partir de (2,3)
    int linha1 = 2, coluna1 = 3, dLinha1 = 0, dColuna1 = 1;
    //  - Navio 2: vertical a partir de (5,7)
    int linha2 = 5, coluna2 = 7, dLinha2 = 1, dColuna2 = 0;
    //  - Navio 3: diagonal descendente a partir de (0,0)
    int linha3 = 0, coluna3 = 0, dLinha3 = 1, dColuna3 = 1;
    //  - Navio 4: diagonal ascendente a partir de (9,3)
    int linha4 = 9, coluna4 = 3, dLinha4 = -1, dColuna4 = 1;

    // 2) Valida e posiciona cada navio, abortando em caso de erro
    if (!pode_posicionar(tabuleiro, linha1, coluna1, dLinha1, dColuna1)) {
        printf("Erro: não é possível posicionar navio horizontal em (%d,%d)\n", linha1, coluna1);
        return 1;
    }
    posicionar_navio(tabuleiro, linha1, coluna1, dLinha1, dColuna1);

    if (!pode_posicionar(tabuleiro, linha2, coluna2, dLinha2, dColuna2)) {
        printf("Erro: não é possível posicionar navio vertical em (%d,%d)\n", linha2, coluna2);
        return 1;
    }
    posicionar_navio(tabuleiro, linha2, coluna2, dLinha2, dColuna2);

    if (!pode_posicionar(tabuleiro, linha3, coluna3, dLinha3, dColuna3)) {
        printf("Erro: não é possível posicionar navio diagonal descendente em (%d,%d)\n", linha3, coluna3);
        return 1;
    }
    posicionar_navio(tabuleiro, linha3, coluna3, dLinha3, dColuna3);

    if (!pode_posicionar(tabuleiro, linha4, coluna4, dLinha4, dColuna4)) {
        printf("Erro: não é possível posicionar navio diagonal ascendente em (%d,%d)\n", linha4, coluna4);
        return 1;
    }
    posicionar_navio(tabuleiro, linha4, coluna4, dLinha4, dColuna4);

    // 3) Exibe o tabuleiro final com todos os navios posicionados
    exibir_tabuleiro(tabuleiro);

    return 0;
}
