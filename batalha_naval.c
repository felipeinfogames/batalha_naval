#include <stdio.h>

#define TAM_NAVIO 3

int main() {
    char linha[10]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J'};
    // 1. Criando o Tabuleiro (Matriz 10x10)
    int tabuleiro[10][10];

    // Inicializando todas as posições do tabuleiro com 0 (água)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Declarando os vetores dos navios
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO] = {3, 3, 3};

    // Definindo coordenadas estáticas iniciais
    int linhaH = 2, colunaH = 3; 
    int linhaV = 5, colunaV = 7;

    // Posicionamento e validação do Navio Horizontal
    int sobreposicaoH = 0;
    if (colunaH + TAM_NAVIO <= 10) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] != 0) sobreposicaoH = 1;
        }
        if (sobreposicaoH == 0) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
            }
        }
    }

    // Posicionamento e validação do Navio Vertical
    int sobreposicaoV = 0;
    if (linhaV + TAM_NAVIO <= 10) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] != 0) sobreposicaoV = 1;
        }
        if (sobreposicaoV == 0) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
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