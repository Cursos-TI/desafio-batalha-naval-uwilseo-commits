#include <stdio.h>

// Definição de constantes para o jogo
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3       // Cada navio ocupa 3 posições
#define AGUA 0                // Valor representando água
#define NAVIO 3               // Valor representando parte do navio

// Orientações possíveis para os navios
#define HORIZONTAL 0
#define VERTICAL 1

/**
 * Função para inicializar o tabuleiro com água (zeros)
 * Parâmetros:
 *   tabuleiro: matriz 10x10 representando o campo de jogo
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;
    
    // Percorre todas as linhas
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Percorre todas as colunas
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;  // Inicializa com água
        }
    }
}

/**
 * Função para validar se a posição do navio está dentro dos limites do tabuleiro
 * Parâmetros:
 *   linha: linha inicial do navio
 *   coluna: coluna inicial do navio
 *   orientacao: HORIZONTAL (0) ou VERTICAL (1)
 * Retorna: 1 se válido, 0 se inválido
 */
int validarPosicao(int linha, int coluna, int orientacao) {
    // Verifica se a posição inicial está dentro do tabuleiro
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return 0;  // Posição inválida
    }
    
    // Verifica se o navio horizontal cabe no tabuleiro
    if (orientacao == HORIZONTAL && coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Navio ultrapassa o limite direito
    }
    
    // Verifica se o navio vertical cabe no tabuleiro
    if (orientacao == VERTICAL && linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;  // Navio ultrapassa o limite inferior
    }
    
    return 1;  // Posição válida
}

/**
 * Função para verificar se há sobreposição com navios já posicionados
 * Parâmetros:
 *   tabuleiro: matriz do jogo
 *   linha: linha inicial do navio
 *   coluna: coluna inicial do navio
 *   orientacao: HORIZONTAL (0) ou VERTICAL (1)
 * Retorna: 1 se não há sobreposição, 0 se há sobreposição
 */
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         int linha, int coluna, int orientacao) {
    int i;
    
    // Verifica sobreposição para navio horizontal
    if (orientacao == HORIZONTAL) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != AGUA) {
                return 0;  // Há sobreposição
            }
        }
    }
    // Verifica sobreposição para navio vertical
    else {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != AGUA) {
                return 0;  // Há sobreposição
            }
        }
    }
    
    return 1;  // Não há sobreposição
}

/**
 * Função para posicionar um navio no tabuleiro
 * Parâmetros:
 *   tabuleiro: matriz do jogo
 *   navio: vetor representando o navio (todas posições com valor 3)
 *   linha: linha inicial do navio
 *   coluna: coluna inicial do navio
 *   orientacao: HORIZONTAL (0) ou VERTICAL (1)
 * Retorna: 1 se posicionado com sucesso, 0 se falhou
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int navio[TAMANHO_NAVIO], int linha, int coluna, int orientacao) {
    int i;
    
    // Valida a posição
    if (!validarPosicao(linha, coluna, orientacao)) {
        printf("Erro: Posicao invalida! Navio fora dos limites do tabuleiro.\n");
        return 0;
    }
    
    // Verifica sobreposição
    if (!verificarSobreposicao(tabuleiro, linha, coluna, orientacao)) {
        printf("Erro: Sobreposicao detectada! Ja existe um navio nesta posicao.\n");
        return 0;
    }
    
    // Posiciona o navio horizontalmente
    if (orientacao == HORIZONTAL) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = navio[i];
        }
        printf("Navio horizontal posicionado com sucesso na linha %d, colunas %d-%d.\n", 
               linha, coluna, coluna + TAMANHO_NAVIO - 1);
    }
    // Posiciona o navio verticalmente
    else {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = navio[i];
        }
        printf("Navio vertical posicionado com sucesso na coluna %d, linhas %d-%d.\n", 
               coluna, linha, linha + TAMANHO_NAVIO - 1);
    }
    
    return 1;  // Sucesso
}

/**
 * Função para exibir o tabuleiro no console
 * Parâmetros:
 *   tabuleiro: matriz do jogo
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;
    
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    
    // Exibe o cabeçalho com os números das colunas
    printf("    ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d  ", j);
    }
    printf("\n");
    
    // Exibe a linha separadora
    printf("   ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");
    
    // Exibe cada linha do tabuleiro
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Exibe o número da linha
        printf("%d | ", i);
        
        // Exibe cada célula da linha
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d  ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    printf("\nLegenda: 0 = Agua | 3 = Navio\n\n");
}

/**
 * Função principal do programa
 */
int main() {
    // Declaração do tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Declaração dos dois navios (vetores com tamanho 3)
    int navio1[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};  // Navio horizontal
    int navio2[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};  // Navio vertical
    
    // Coordenadas dos navios (podem ser modificadas)
    int linha_navio1 = 2;    // Linha inicial do navio horizontal
    int coluna_navio1 = 1;   // Coluna inicial do navio horizontal
    int linha_navio2 = 5;    // Linha inicial do navio vertical
    int coluna_navio2 = 7;   // Coluna inicial do navio vertical
    
    printf("=== JOGO DE BATALHA NAVAL ===\n");
    printf("Inicializando o tabuleiro...\n\n");
    
    // Passo 1: Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Passo 2: Posicionar o primeiro navio (horizontal)
    printf("Posicionando navio 1 (horizontal)...\n");
    if (!posicionarNavio(tabuleiro, navio1, linha_navio1, coluna_navio1, HORIZONTAL)) {
        printf("Falha ao posicionar navio 1!\n");
        return 1;  // Encerra o programa com erro
    }
    
    // Passo 3: Posicionar o segundo navio (vertical)
    printf("Posicionando navio 2 (vertical)...\n");
    if (!posicionarNavio(tabuleiro, navio2, linha_navio2, coluna_navio2, VERTICAL)) {
        printf("Falha ao posicionar navio 2!\n");
        return 1;  // Encerra o programa com erro
    }
    
    // Passo 4: Exibir o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    printf("Navios posicionados com sucesso!\n");
    printf("Total de navios no tabuleiro: 2\n");
    printf("Tamanho de cada navio: %d posicoes\n", TAMANHO_NAVIO);
    
    return 0;  // Programa executado com sucesso
}
