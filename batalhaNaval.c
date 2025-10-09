#include <stdio.h>

// Definição de constantes para o jogo
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3       // Cada navio ocupa 3 posições
#define TAMANHO_HABILIDADE 7  // Tamanho das matrizes de habilidade 7x7
#define AGUA 0                // Valor representando água
#define NAVIO 3               // Valor representando parte do navio
#define HABILIDADE 5          // Valor representando área afetada por habilidade

// Orientações possíveis para os navios
#define HORIZONTAL 0
#define VERTICAL 1

// Tipos de habilidades
#define CONE 0
#define CRUZ 1
#define OCTAEDRO 2

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
 * Função para criar a matriz de habilidade em formato de CONE
 * O cone tem o ponto de origem no topo e expande para baixo
 * Parâmetros:
 *   habilidade: matriz 7x7 que será preenchida
 */
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int i, j;
    int centro = TAMANHO_HABILIDADE / 2;  // Centro da matriz (índice 3)
    
    // Inicializa toda a matriz com 0
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Cria o formato de cone usando condicionais
    // A cada linha, a largura aumenta em relação ao centro
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a distância do centro na horizontal
            int distancia = (j > centro) ? (j - centro) : (centro - j);
            
            // Se a distância horizontal for menor ou igual à linha atual, marca como afetado
            if (distancia <= i) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Função para criar a matriz de habilidade em formato de CRUZ
 * A cruz tem o ponto de origem no centro
 * Parâmetros:
 *   habilidade: matriz 7x7 que será preenchida
 */
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int i, j;
    int centro = TAMANHO_HABILIDADE / 2;  // Centro da matriz (índice 3)
    
    // Inicializa toda a matriz com 0
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Cria o formato de cruz usando condicionais
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Marca as posições na linha central ou coluna central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Função para criar a matriz de habilidade em formato de OCTAEDRO (losango)
 * O octaedro visto de frente forma um losango com centro no meio da matriz
 * Parâmetros:
 *   habilidade: matriz 7x7 que será preenchida
 */
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int i, j;
    int centro = TAMANHO_HABILIDADE / 2;  // Centro da matriz (índice 3)
    
    // Inicializa toda a matriz com 0
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Cria o formato de losango (octaedro visto de frente) usando condicionais
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a distância Manhattan do centro
            int distanciaLinha = (i > centro) ? (i - centro) : (centro - i);
            int distanciaColuna = (j > centro) ? (j - centro) : (centro - j);
            int distanciaTotal = distanciaLinha + distanciaColuna;
            
            // Se a soma das distâncias for menor ou igual ao raio, marca como afetado
            if (distanciaTotal <= centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * Função para aplicar uma habilidade ao tabuleiro
 * Sobrepõe a matriz de habilidade ao tabuleiro, marcando as áreas afetadas
 * Parâmetros:
 *   tabuleiro: matriz do jogo
 *   habilidade: matriz de habilidade 7x7
 *   linha_origem: linha do ponto de origem no tabuleiro
 *   coluna_origem: coluna do ponto de origem no tabuleiro
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int linha_origem, int coluna_origem) {
    int i, j;
    int offset = TAMANHO_HABILIDADE / 2;  // Offset para centralizar a habilidade
    
    // Percorre a matriz de habilidade
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a posição correspondente no tabuleiro
            int linha_tab = linha_origem - offset + i;
            int coluna_tab = coluna_origem - offset + j;
            
            // Verifica se a posição está dentro dos limites do tabuleiro
            if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO &&
                coluna_tab >= 0 && coluna_tab < TAMANHO_TABULEIRO) {
                
                // Se a habilidade afeta esta posição e não há navio, marca como afetada
                if (habilidade[i][j] == 1 && tabuleiro[linha_tab][coluna_tab] != NAVIO) {
                    tabuleiro[linha_tab][coluna_tab] = HABILIDADE;
                }
            }
        }
    }
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
    
    printf("\nLegenda: 0 = Agua | 3 = Navio | 5 = Area de Habilidade\n\n");
}

/**
 * Função para exibir uma matriz de habilidade (para visualização)
 * Parâmetros:
 *   habilidade: matriz de habilidade 7x7
 *   nome: nome da habilidade
 */
void exibirHabilidade(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], char* nome) {
    int i, j;
    
    printf("\n=== HABILIDADE: %s ===\n\n", nome);
    
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        printf("  ");
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d  ", habilidade[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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
    
    // Declaração das matrizes de habilidade
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Coordenadas dos navios
    int linha_navio1 = 2;
    int coluna_navio1 = 1;
    int linha_navio2 = 7;
    int coluna_navio2 = 7;
    
    // Pontos de origem das habilidades no tabuleiro
    int linha_cone = 3;
    int coluna_cone = 5;
    int linha_cruz = 6;
    int coluna_cruz = 2;
    int linha_octaedro = 5;
    int coluna_octaedro = 8;
    
    printf("=== JOGO DE BATALHA NAVAL COM HABILIDADES ESPECIAIS ===\n\n");
    
    // ETAPA 1: Criar as matrizes de habilidade
    printf("Criando matrizes de habilidade...\n");
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    printf("Matrizes de habilidade criadas com sucesso!\n\n");
    
    // Exibir as matrizes de habilidade
    exibirHabilidade(habilidadeCone, "CONE");
    exibirHabilidade(habilidadeCruz, "CRUZ");
    exibirHabilidade(habilidadeOctaedro, "OCTAEDRO");
    
    // ETAPA 2: Inicializar o tabuleiro
    printf("Inicializando o tabuleiro...\n");
    inicializarTabuleiro(tabuleiro);
    
    // ETAPA 3: Posicionar os navios
    printf("\nPosicionando navios...\n");
    if (!posicionarNavio(tabuleiro, navio1, linha_navio1, coluna_navio1, HORIZONTAL)) {
        return 1;
    }
    if (!posicionarNavio(tabuleiro, navio2, linha_navio2, coluna_navio2, VERTICAL)) {
        return 1;
    }
    
    // Exibir tabuleiro apenas com navios
    printf("\n--- TABULEIRO COM NAVIOS ---");
    exibirTabuleiro(tabuleiro);
    
    // ETAPA 4: Aplicar habilidades ao tabuleiro
    printf("Aplicando habilidades ao tabuleiro...\n\n");
    
    printf("Aplicando habilidade CONE na posicao (%d, %d)...\n", linha_cone, coluna_cone);
    aplicarHabilidade(tabuleiro, habilidadeCone, linha_cone, coluna_cone);
    
    printf("Aplicando habilidade CRUZ na posicao (%d, %d)...\n", linha_cruz, coluna_cruz);
    aplicarHabilidade(tabuleiro, habilidadeCruz, linha_cruz, coluna_cruz);
    
    printf("Aplicando habilidade OCTAEDRO na posicao (%d, %d)...\n", linha_octaedro, coluna_octaedro);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, linha_octaedro, coluna_octaedro);
    
    // ETAPA 5: Exibir o tabuleiro final com navios e habilidades
    printf("\n--- TABULEIRO FINAL COM NAVIOS E HABILIDADES ---");
    exibirTabuleiro(tabuleiro);
    
    printf("Programa executado com sucesso!\n");
    printf("Total de navios: 2\n");
    printf("Total de habilidades aplicadas: 3 (Cone, Cruz, Octaedro)\n");
    
    return 0;
}
