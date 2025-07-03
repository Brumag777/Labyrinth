#include "../Labyrinth.h"

// Altera o nível selecionado no menu principal
void alteraNivelSelecionado (int *NivelSelecionado, char Input) {

    // Procura a direção para a qual o jogador pretende mudar
    if (Input == 'w') {
        if (*NivelSelecionado - 5 >= 1) *NivelSelecionado -= 5;
        else *NivelSelecionado += 20;
    } else if (Input == 's') {
        if (*NivelSelecionado + 5 <= 25) *NivelSelecionado += 5;
        else *NivelSelecionado -= 20;
    } else if (Input == 'd') {
        if (*NivelSelecionado % 5 != 0) (*NivelSelecionado)++;
        else *NivelSelecionado -= 4;
    } else if (Input == 'a') {
        if (*NivelSelecionado % 5 != 1) (*NivelSelecionado)--;
        else *NivelSelecionado += 4;
    }
}



// Inicializa os componentes da informação do nível
void inicializaInfo (InfoNivel I, int PvE) {

    // Inicializa o labirinto
    I -> M.dL = I -> M.dC = 0;
    I -> M.Lab = NULL;

    // Inicializa o Jerry
    I -> Jerry.Stamina = 1;
    I -> Jerry.L = I -> Jerry.C = -1;

    // Inicializa o Tom
    I -> Tom.Stamina = 0;
    I -> Tom.L = I -> Tom.C = -1;

    // Inicializa a chave
    I -> Chave.Ativo = 0;
    I -> Chave.L = I -> Chave.C = -1;

    // Define o PvE
    I -> PvE = PvE;

    // Define o nevoeiro
    I -> Nevoeiro = 0;
}



// Verifica se o Jerry ganhou
int vitoriaJerry (InfoNivel I) {
    return I -> M.Lab [I -> Jerry.L][I -> Jerry.C] == 'P';
}



// Verifica se o Tom ganhou
int vitoriaTom (InfoNivel I) {
    
    // Estão na mesma linha
    if (I -> Jerry.L == I -> Tom.L) return I -> Jerry.C == I -> Tom.C + 1 || I -> Jerry.C == I -> Tom.C - 1;

    // Estão na mesma coluna
    if (I -> Jerry.C == I -> Tom.C) return I -> Jerry.L == I -> Tom.L + 1 || I -> Jerry.L == I -> Tom.L - 1;

    // O Tom ainda não venceu
    return 0;
}



// Calcula o mínimo de quatro valores
int minimo (int a, int b, int c, int d) {

    // Inteiro a retornar
    int minimo = a;

    // Verifica se o mínimo é maior que os restantes
    if (minimo > b) minimo = b;
    if (minimo > c) minimo = c;
    if (minimo > d) minimo = d;

    // Retorna o mínimo
    return minimo;
}



// Verifica se o próximo passo é uma chave ou uma porta
void verificaBloqueio (InfoNivel I, char *direcao) {

    // Coordenadas finais
    int L = I -> Tom.L, C = I -> Tom.C;

    // Determina as coordenadas finais
    if (*direcao == 'w') L--;
    else if (*direcao == 's') L++;
    else if (*direcao == 'a') C--;
    else C++;

    // Verifica se o próximo passo não é a chave nem uma porta
    if ((L != I -> Chave.L || C != I -> Chave.C) && I -> M.Lab [L][C] != 'P' && I -> M.Lab [L][C] != 'p') return;

    // Atualiza as coordenadas para as atuais
    L = I -> Tom.L;
    C = I -> Tom.C;

    // Procura uma jogada válida
    if (jogadaTomValida (I, L - 1, C)) *direcao = 'w';
    else if (jogadaTomValida (I, L + 1, C)) *direcao = 's';
    else if (jogadaTomValida (I, L, C - 1)) *direcao = 'a';
    else *direcao = 'd';
}



// Verifica se um dado preset é válido
int presetValido (char Preset [52][52], int L) {

    // Número de Jerrys, Toms, chaves e portas exteriores
    int NJ = 0, NT = 0, NC = 0, NP = 0;

    // Percorre o labirinto
    for (int i = 0; i <= L; i++)
        for (int j = 0; Preset [i][j]; j++)
            if (Preset [i][j] == 'J') NJ++;
            else if (Preset [i][j] == 'T') NT++;
            else if (Preset [i][j] == 'C') NC++;
            else if (Preset [i][j] == 'P') NP++;

    // Retorna a condição
    return NJ == 1 && NT == 1 && NC == 1 && NP;
}