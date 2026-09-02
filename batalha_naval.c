#include <stdio.h>

#define TAM_NAVIO 3

int main() {
    // Vetor para auxiliar na impressão das linhas com letras
    char linha[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    
    // 1. Criando o Tabuleiro (Matriz 10x10)
    int tabuleiro[10][10];

    // Inicializando todas as posições do tabuleiro com 0 (água)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Declarando os vetores dos navios (preenchidos com 3)
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO]   = {3, 3, 3};
    int navioDiagonal1[TAM_NAVIO]  = {3, 3, 3};
    int navioDiagonal2[TAM_NAVIO]  = {3, 3, 3};

    // Definindo coordenadas estáticas iniciais para os 4 navios
    // Escolhidas para não haver sobreposição
    int linhaH = 2, colunaH = 3;  // Horizontal
    int linhaV = 5, colunaV = 7;  // Vertical
    int linhaD1 = 0, colunaD1 = 0; // Diagonal 1 (Cresce Direita/Baixo)
    int linhaD2 = 0, colunaD2 = 9; // Diagonal 2 (Cresce Esquerda/Baixo)

    // --- POSICIONAMENTO E VALIDAÇÃO ---

    // Navio Horizontal (Linha constante, Coluna aumenta)
    int sobreposicaoH = 0;
    if (colunaH + TAM_NAVIO <= 10) { // Valida limite do tabuleiro
        for (int i = 0; i < TAM_NAVIO; i++) { // Verifica sobreposição
            if (tabuleiro[linhaH][colunaH + i] != 0) sobreposicaoH = 1;
        }
        if (sobreposicaoH == 0) { // Se livre, posiciona o navio
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
            }
        }
    }

    // Navio Vertical (Linha aumenta, Coluna constante)
    int sobreposicaoV = 0;
    if (linhaV + TAM_NAVIO <= 10) { // Valida limite do tabuleiro
        for (int i = 0; i < TAM_NAVIO; i++) { // Verifica sobreposição
            if (tabuleiro[linhaV + i][colunaV] != 0) sobreposicaoV = 1;
        }
        if (sobreposicaoV == 0) { // Se livre, posiciona o navio
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }
        }
    }

    // Navio Diagonal 1 (Linha aumenta, Coluna aumenta)
    int sobreposicaoD1 = 0;
    if (linhaD1 + TAM_NAVIO <= 10 && colunaD1 + TAM_NAVIO <= 10) { // Valida limites
        for (int i = 0; i < TAM_NAVIO; i++) { // Verifica sobreposição
            if (tabuleiro[linhaD1 + i][colunaD1 + i] != 0) sobreposicaoD1 = 1;
        }
        if (sobreposicaoD1 == 0) { // Se livre, posiciona o navio
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaD1 + i][colunaD1 + i] = navioDiagonal1[i];
            }
        }
    }

    // Navio Diagonal 2 (Linha aumenta, Coluna diminui)
    int sobreposicaoD2 = 0;
    // Valida limites: linha não pode passar de 9 e coluna não pode ficar menor que 0
    if (linhaD2 + TAM_NAVIO <= 10 && colunaD2 - TAM_NAVIO >= -1) { 
        for (int i = 0; i < TAM_NAVIO; i++) { // Verifica sobreposição
            if (tabuleiro[linhaD2 + i][colunaD2 - i] != 0) sobreposicaoD2 = 1;
        }
        if (sobreposicaoD2 == 0) { // Se livre, posiciona o navio
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaD2 + i][colunaD2 - i] = navioDiagonal2[i];
            }
        }
    }

    // 3. Exibindo o Tabuleiro Formatado
    printf("Tabuleiro de Batalha Naval:\n\n");
    
    // Imprime o cabeçalho das colunas numéricas
    printf("  0 1 2 3 4 5 6 7 8 9\n");

    for (int i = 0; i < 10; i++) {
        // Imprime a letra correspondente à linha atual usando o vetor 'linha'
        printf("%c ", linha[i]);
        
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}