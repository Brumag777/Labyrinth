#include "../Labyrinth.h"

// Verifica se o jogo terminou
int fimJogo (InfoNivel I, int NivelSelecionado, int *NiveisConcluidos, int Niveis) {

    // Verifica se o Jerry ganhou
    if (vitoriaJerry (I)) {
        menuVitoria (1, I, Niveis);
        if (NivelSelecionado > *NiveisConcluidos) *NiveisConcluidos = NivelSelecionado;
        return 1;
    }

    // Verifica se o Tom ganhou
    if (vitoriaTom (I)) {
        menuVitoria (0, I, Niveis);
        return 1;
    }

    // Avisa que o jogo ainda não terminou
    return 0;
}



// Realiza uma jogada
int realizaJogada (InfoNivel I, char Input) {

    // É uma jogada do Jerry
    if (I -> Jerry.Stamina > 0) {
        if (realizaJogadaJerry (I, Input)) {
            I -> Jerry.Stamina--;
            if (I -> Jerry.Stamina == 0) I -> Tom.Stamina++;
            if (I -> Nevoeiro) I -> Nevoeiro--;
            return 1;
        } return 0;
    }

    // É uma jogada do Tom
    if (realizaJogadaTom (I, Input)) {
        I -> Tom.Stamina--;
        if (I -> Tom.Stamina == 0) I -> Jerry.Stamina++;
        if (I -> Nevoeiro) I -> Nevoeiro--;
        return 1;
    } return 0;
}



// Realiza uma jogada do Jerry
int realizaJogadaJerry (InfoNivel I, char Input) {

    // Coordenadas finais do Jerry
    int lF = I -> Jerry.L, cF = I -> Jerry.C;

    // Determina as coordenadas finais do Jerry
    if (Input == 'w') lF--;
    else if (Input == 's') lF++;
    else if (Input == 'a') cF--;
    else cF++;

    // Verifica se a jogada é inválida
    if (!jogadaJerryValida (I, lF, cF)) return 0;

    // Verifica se foi alcançada a chave
    if (lF == I -> Chave.L && cF == I -> Chave.C) {
        I -> Chave.Ativo = 1;
        I -> Chave.L = I -> Chave.C = -1;
    }

    // Verifica se foi alcançado queijo
    else if (I -> M.Lab [lF][cF] == 'Q') {
        I -> M.Lab [lF][cF] = '-';
        I -> Jerry.Stamina += 5;
    }

    // Verifica se foi alcançado peixe
    else if (I -> M.Lab [lF][cF] == 'F') I -> M.Lab [lF][cF] = '-';

    // Verifica se foi alcançada uma porta interior
    else if (I -> M.Lab [lF][cF] == 'p') I -> M.Lab [lF][cF] = '-';

    // Verifica se foi atingida uma bomba de névoa
    else if (I -> M.Lab [lF][cF] == 'B') {
        I -> M.Lab [lF][cF] = '-';
        I -> Nevoeiro = 6;
    }

    // Atualiza a posição do Jerry
    I -> Jerry.L = lF;
    I -> Jerry.C = cF;

    // Avisa que foi realizada uma jogada
    return 1;
}



// Verifica se uma jogada do Jerry é válida
int jogadaJerryValida (InfoNivel I, int lF, int cF) {

    // Verifica se a coordenada é inválida
    if (lF < 0 || cF < 0 || lF == I -> M.dL || cF == I -> M.dC) return 0;

    // Verifica se a jogada é inválida
    if (I -> M.Lab [lF][cF] == '#' || I -> M.Lab [lF][cF] == 'G' || ((I -> M.Lab [lF][cF] == 'p' || I -> M.Lab [lF][cF] == 'P') && I -> Chave.Ativo == 0)) return 0;

    // A jogada é válida
    return 1;
}



// Realiza uma jogada do Tom
int realizaJogadaTom (InfoNivel I, char Input) {

    // Coordenadas finais do Tom
    int lF = I -> Tom.L, cF = I -> Tom.C;

    // Determina as coordenadas finais do Jerry
    if (Input == 'w') lF--;
    else if (Input == 's') lF++;
    else if (Input == 'a') cF--;
    else cF++;

    // Verifica se a jogada é inválida
    if (!jogadaTomValida (I, lF, cF)) return 0;

    // Verifica se foi alcançado peixe
    if (I -> M.Lab [lF][cF] == 'F') {
        I -> M.Lab [lF][cF] = '-';
        I -> Tom.Stamina += 5;
    }

    // Verifica se foi alcançado queijo
    else if (I -> M.Lab [lF][cF] == 'Q') I -> M.Lab [lF][cF] = '-';

    // Verifica se foram alcançadas grades
    else if (I -> M.Lab [lF][cF] == 'G') I -> M.Lab [lF][cF] = '-';

    // Verifica se foi atingida uma bomba de névoa
    else if (I -> M.Lab [lF][cF] == 'B') {
        I -> M.Lab [lF][cF] = '-';
        I -> Nevoeiro = 6;
    }

    // Atualiza a posição do Tom
    I -> Tom.L = lF;
    I -> Tom.C = cF;

    // Avisa que foi realizada uma jogada
    return 1;
}



// Verifica se uma jogada do Tom é válida
int jogadaTomValida (InfoNivel I, int lF, int cF) {

    // Verifica se a coordenada é inválida
    if (lF < 0 || cF < 0 || lF == I -> M.dL || cF == I -> M.dC) return 0;

    // Verifica se a jogada é inválida
    if (I -> M.Lab [lF][cF] == '#' || (lF == I -> Chave.L && cF == I -> Chave .C) || I -> M.Lab [lF][cF] == 'p' || I -> M.Lab [lF][cF] == 'P') return 0;

    // A jogada é válida
    return 1;
}