#include <stdio.h>
#include <stdlib.h>  // para abs()

#define TAMANHO_TABULEIRO 10  // tamanho do tabuleiro
#define TAMANHO_NAVIO      3  // tamanho fixo dos navios
#define TAMANHO_HABILIDADE  5  // tamanho das matrizes de habilidade (ímpar)

#define AGUA       0  // representação da água
#define NAVIO      3  // representação das partes do navio
#define HABILIDADE 5  // representação das áreas afetadas por habilidade

// Inicializa todas as posições do tabuleiro com água (0)
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            tabuleiro[l][c] = AGUA;
        }
    }
}

// Função que gera a matriz de efeito em forma de cone (ponta para baixo)
void gerar_cone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // só desenha até o centro vertical
            if (i <= centro && j >= centro - i && j <= centro + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função que gera a matriz de efeito em forma de cruz
void gerar_cruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função que gera a matriz de efeito em forma de octaedro (losango)
void gerar_octaedro(int octa[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // condição de losango: soma das distâncias <= centro
            if (abs(i - centro) + abs(j - centro) <= centro)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }
}

// Aplica matriz de habilidade ao tabuleiro, marcando com o valor HABILIDADE (5)
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int hab[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (hab[i][j] == 1) {
                int l = origemLinha + (i - centro);
                int c = origemColuna + (j - centro);
                // verifica limites do tabuleiro antes de aplicar
                if (l >= 0 && l < TAMANHO_TABULEIRO &&
                    c >= 0 && c < TAMANHO_TABULEIRO) {
                    tabuleiro[l][c] = HABILIDADE;
                }
            }
        }
    }
}

// Exibe o tabuleiro no console, usando números para cada tipo de célula
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // cabeçalho de colunas
    printf("   ");
    for (int c = 0; c < TAMANHO_TABULEIRO; c++)
        printf(" %2d", c);
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

    // 2) Posiciona quatro navios como antes (horizontal, vertical e duas diagonais)
    // Coordenadas e direções fixas
    int navios[4][4] = {
        {2, 3, 0, 1},  // (linha, coluna, dLinha, dColuna): horizontal
        {5, 7, 1, 0},  // vertical
        {0, 0, 1, 1},  // diagonal descendente
        {9, 3,-1, 1}   // diagonal ascendente
    };
    for (int n = 0; n < 4; n++) {
        int l = navios[n][0], c = navios[n][1];
        int dL = navios[n][2], dC = navios[n][3];
        // valida limites e sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int li = l + i*dL;
            int ci = c + i*dC;
            if (li < 0 || li >= TAMANHO_TABULEIRO ||
                ci < 0 || ci >= TAMANHO_TABULEIRO) {
                printf("Erro: navio %d fora dos limites\n", n+1);
                return 1;
            }
        }
        // posiciona
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int li = l + i*dL;
            int ci = c + i*dC;
            tabuleiro[li][ci] = NAVIO;
        }
    }

    // 3) Gera matrizes de habilidade dinamicamente
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octa[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    gerar_cone(cone);
    gerar_cruz(cruz);
    gerar_octaedro(octa);

    // 4) Define pontos de origem no tabuleiro e aplica cada habilidade
    aplicar_habilidade(tabuleiro, cone, 4, 4);  // ex: cone com origem em (4,4)
    aplicar_habilidade(tabuleiro, cruz, 6, 6);  // cruz em (6,6)
    aplicar_habilidade(tabuleiro, octa, 2, 8);  // octaedro em (2,8)

    // 5) Exibe o tabuleiro final com navios e áreas de habilidade
    exibir_tabuleiro(tabuleiro);

    return 0;
}
