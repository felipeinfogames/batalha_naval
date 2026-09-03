#include <stdio.h>

#define TAM_NAVIO 3
#define TAM_HABILIDADE 5 // Tamanho 5x5 para as matrizes de habilidade

int main() {
    // Vetor para auxiliar na impressão das linhas com letras
    char linha[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    
    // ==========================================
    // 1. CRIANDO E INICIALIZANDO O TABULEIRO
    // ==========================================
    int tabuleiro[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // Preenche com água (0)
        }
    }

    // ==========================================
    // 2. POSICIONAMENTO DOS NAVIOS (Valor 3)
    // ==========================================
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO]   = {3, 3, 3};
    int navioDiagonal1[TAM_NAVIO]  = {3, 3, 3};
    int navioDiagonal2[TAM_NAVIO]  = {3, 3, 3};

    // Coordenadas fixas para os navios
    int linhaH = 0, colunaH = 6;   // Horizontal no topo à direita
    int linhaV = 4, colunaV = 9;   // Vertical na extrema direita
    int linhaD1 = 0, colunaD1 = 0; // Diagonal 1
    int linhaD2 = 7, colunaD2 = 3; // Diagonal 2

    // Posicionando Horizontal (sem sobreposição pois estão separados por design)
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
    }
    // Posicionando Vertical
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = navioVertical[i];
    }
    // Posicionando Diagonal 1 (cresce direita/baixo)
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaD1 + i][colunaD1 + i] = navioDiagonal1[i];
    }
    // Posicionando Diagonal 2 (cresce esquerda/baixo)
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaD2 + i][colunaD2 - i] = navioDiagonal2[i];
    }


    // ==========================================
    // 3. CRIAÇÃO DINÂMICA DAS HABILIDADES
    // ==========================================
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Construção das matrizes 5x5 utilizando loops aninhados e condicionais
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Inicializa a posição atual como não afetada (0)
            cone[i][j] = 0;
            cruz[i][j] = 0;
            octaedro[i][j] = 0;

            // Lógica do CONE: Origem (topo) no centro da primeira linha (i=0, j=2)
            // A largura aumenta 1 para cada lado a cada linha descida (até a linha 2)
            if (i <= 2 && j >= (2 - i) && j <= (2 + i)) {
                cone[i][j] = 1;
            }

            // Lógica da CRUZ: Ocupa inteiramente a linha central (i=2) e a coluna central (j=2)
            if (i == 2 || j == 2) {
                cruz[i][j] = 1;
            }

            // Lógica do OCTAEDRO (Losango): A distância do centro (2,2) para a borda não pode ser maior que 2
            // Cálculo manual de valor absoluto para determinar a distância no grid
            int dist_i = (i > 2) ? (i - 2) : (2 - i);
            int dist_j = (j > 2) ? (j - 2) : (2 - j);
            if (dist_i + dist_j <= 2) {
                octaedro[i][j] = 1;
            }
        }
    }


    // ==========================================
    // 4. SOBREPOSIÇÃO DAS HABILIDADES NO TABULEIRO (Valor 5)
    // ==========================================
    
    // Coordenadas de origem (alvo) no tabuleiro para cada habilidade
    int origemConeX = 2, origemConeY = 2;       // Ponto do topo do cone
    int origemCruzX = 7, origemCruzY = 7;       // Centro da cruz
    int origemOctaX = 3, origemOctaY = 6;       // Centro do octaedro

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            // --- Aplicando o Cone ---
            if (cone[i][j] == 1) {
                // Como a origem do cone é o topo (i=0, j=2 na matriz de habilidade)
                int r = origemConeX + i - 0; 
                int c = origemConeY + j - 2; 
                // Validação para garantir que não vai estourar o limite do tabuleiro (0 a 9)
                if (r >= 0 && r < 10 && c >= 0 && c < 10) tabuleiro[r][c] = 5;
            }

            // --- Aplicando a Cruz ---
            if (cruz[i][j] == 1) {
                // A origem da cruz é o centro (i=2, j=2 na matriz de habilidade)
                int r = origemCruzX + i - 2;
                int c = origemCruzY + j - 2;
                // Validação de limites
                if (r >= 0 && r < 10 && c >= 0 && c < 10) tabuleiro[r][c] = 5;
            }

            // --- Aplicando o Octaedro ---
            if (octaedro[i][j] == 1) {
                // A origem do octaedro também é o centro (i=2, j=2)
                int r = origemOctaX + i - 2;
                int c = origemOctaY + j - 2;
                // Validação de limites
                if (r >= 0 && r < 10 && c >= 0 && c < 10) tabuleiro[r][c] = 5;
            }
        }
    }


    // ==========================================
    // 5. EXIBINDO O TABULEIRO FINAL
    // ==========================================
    printf("Tabuleiro de Batalha Naval (Navios = 3 | Efeitos = 5):\n\n");
    
    // Imprime o cabeçalho das colunas numéricas
    printf("  0 1 2 3 4 5 6 7 8 9\n");

    for (int i = 0; i < 10; i++) {
        // Imprime a letra correspondente à linha atual
        printf("%c ", linha[i]);
        
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}