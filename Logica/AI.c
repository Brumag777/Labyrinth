#include "../Labyrinth.h"

// Encontra a direção do caminho mais curto do Tom até ao Jerry
char encontraDirecao (InfoNivel I, int L, int C) {

    // Armazena o caractere na posição do Tom
    char c = I -> M.Lab [L][C];

    // Bloqueia a posição do Tom
    I -> M.Lab [L][C] = '#';
    
    // Encontra os quatro possíveis caminhos
    int Cima = encontraCaminho (I, L - 1, C, 1);
    int Baixo = encontraCaminho (I, L + 1, C, 1);
    int Esquerda = encontraCaminho (I, L, C - 1, 1);
    int Direita = encontraCaminho (I, L, C + 1, 1);

    // Calcula o tamanho máximo do caminho
    int max = I -> M.dL * I -> M.dC;

    // Caso em que não existe caminho se as portas bloqueiam
    if (Cima >= max && Baixo >= max && Esquerda >= max && Direita >= max) {
        Cima = encontraCaminho (I, L - 1, C, 0);
        Baixo = encontraCaminho (I, L + 1, C, 0);
        Esquerda = encontraCaminho (I, L, C - 1, 0);
        Direita = encontraCaminho (I, L, C + 1, 0); 
    }

    // Retorna o caractere original
    I -> M.Lab [L][C] = c;

    // Calcula o menor dos quatro caminhos
    int min = minimo (Cima, Baixo, Esquerda, Direita);

    // Direção correspondente
    char direcao = 0;

    // Determina a direção correspondente
    if (min == Cima) direcao = 'w';
    else if (min == Baixo) direcao = 's';
    else if (min == Esquerda) direcao = 'a';
    else direcao = 'd';

    // Verifica se o próximo passo é uma chave ou uma porta
    verificaBloqueio (I, &direcao);

    // Retorna a direção correspondente
    return direcao;
}



// Indica o tamanho do caminho mais curto do Tom até ao Jerry
int encontraCaminho (InfoNivel I, int L, int C, int PortasBloqueiam) {

    // Verifica se a coordenada é inválida
    if (L < 0 || C < 0 || L == I -> M.dL || C == I -> M.dC) return I -> M.dL * I -> M.dC;

    // Verifica se a posição é inválida
    if ((PortasBloqueiam && (I -> M.Lab [L][C] == 'p' || I -> M.Lab [L][C] == 'P')) || I -> M.Lab [L][C] == '#') return I -> M.dL * I -> M.dC;

    // Verifica se já foi alcançado o Jerry
    if (L == I -> Jerry.L && C == I -> Jerry.C) return 0;

    // Armazena o caractere na posição do Tom
    char c = I -> M.Lab [L][C];

    // Bloqueia a posição do Tom
    I -> M.Lab [L][C] = '#';

    // Encontra os quatro possíveis caminhos
    int Cima = encontraCaminho (I, L - 1, C, PortasBloqueiam);
    int Baixo = encontraCaminho (I, L + 1, C, PortasBloqueiam);
    int Esquerda = encontraCaminho (I, L, C - 1, PortasBloqueiam);
    int Direita = encontraCaminho (I, L, C + 1, PortasBloqueiam);

    // Retorna o caractere original
    I -> M.Lab [L][C] = c;

    // Retorna o tamanho do caminho
    return 1 + minimo (Cima, Baixo, Esquerda, Direita);
}