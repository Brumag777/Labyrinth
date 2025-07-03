#include "Labyrinth.h"

// Corre o menu principal
int menuPrincipal (int *NiveisConcluidos) {

    // Inteiro que indica o nível que está selecionado no momento
    int NivelSelecionado = 1;

    // Inteiro que indica se o modo de jogo é PvE
    int PvE = 1;

    // Inteiro que indica se o tipo de jogo é Níveis
    int Niveis = 1;

    // Corre o menu principal
    while (1) {

        // Limpa a terminal
        printf ("\033[2J\033[H");

        // Imprime o menu principal
        imprimeMenuPrincipal (*NiveisConcluidos, NivelSelecionado, PvE, Niveis);

        // Recebe o input do jogador
        char Input = getchar ();

        // Verifica se o jogador pretende sair do jogo
        if (Input == 'q') break;

        // Verifica se o jogador pretende mudar o modo de jogo
        else if (Input == 'm') PvE = !PvE;

        // Verifica se o jogador pretende saber mais sobre o jogo
        else if (Input == 'h') menuAjuda (*NiveisConcluidos);

        // Verifica se o jogador pretende mudar o tipo do jogo
        else if (*NiveisConcluidos == 25 && Input == 't') Niveis = !Niveis;

        // Verifica se o jogador pretende editar um preset
        else if (Niveis == 0 && Input == 'e') menuEditar (NivelSelecionado);

        // Verifica se o jogador pretende jogar o nível ou preset selecionado
        else if (Input == '\n') {
            if (jogo (NivelSelecionado, NiveisConcluidos, PvE, Niveis)) return 1;
        }

        // Verifica se o jogador pretende selecionar outro nível
        else if (Input == 'w' || Input == 's' || Input == 'd' || Input == 'a')
            alteraNivelSelecionado (&NivelSelecionado, Input);
    }

    // Avança uma linha
    putchar ('\n');

    // A função correu corretamente
    return 0;
}



// Corre o menu de ajuda
void menuAjuda (int NiveisConcluidos) {

    // Mantém o menu aberto até ao jogador pressionar 'q'
    while (1) {

        // Limpa a terminal
        printf ("\033[2J\033[H");

        // Imprime o menu de ajuda
        imprimeMenuAjuda (NiveisConcluidos);

        // Recebe o input do jogador
        if (getchar () == 'q') break;
    }
}



// Corre o menu de um nível
int jogo (int NivelSelecionado, int *NiveisConcluidos, int PvE, int Niveis) {

    // Verifica se o nível é acessível
    if (PvE) {
        if (NivelSelecionado > *NiveisConcluidos + 1) return 0;
    } else if (NivelSelecionado > *NiveisConcluidos) return 0;

    // Inicia o nível
    InfoNivel I = iniciaNivel (NivelSelecionado, PvE, Niveis);

    // Verifica se houve um erro ao iniciar o nível
    if (I == NULL) return 1;

    // Corre o nível
    while (1) {

        // Limpa a terminal
        printf ("\033[2J\033[H");

        // Imprime o labirinto
        imprimeLabirinto (I, NivelSelecionado, Niveis);

        // Indica ao jogador que deve pressionar algum caractere
        if (I -> PvE && I -> Tom.Stamina > 0) printf (AZUL "\nPressione qualquer botão para proceder!\n\n" RESET);

        // Input do jogador
        char Input = getchar ();

        // Verifica se o jogador pretende terminar o nível
        if (Input == 'q') break;

        // É a jogada do PC
        if (I -> PvE && I -> Tom.Stamina > 0) Input = encontraDirecao (I, I -> Tom.L, I -> Tom.C);

        // Verifica se o jogador pretende mover o personagem
        if (Input == 'w' || Input == 's' || Input == 'd' || Input == 'a') {

            // Realiza a jogada
            if (realizaJogada (I, Input))

            // Verifica se o jogo terminou
            if (fimJogo (I, NivelSelecionado, NiveisConcluidos, Niveis)) break;
        }
    }

    // Finaliza o nível
    if (I) libertaInfo (&I, I -> M.dL);

    // A função correu corretamente
    return 0;
}



// Corre o menu de vitória do Jerry
void menuVitoria (int EJerry, InfoNivel I, int Niveis) {

    // Corre o menu
    while (1) {

        // Limpa a terminal
        printf ("\033[2J\033[H");

        // Imprime o menu
        if (EJerry) imprimeVitoriaJerry (I, Niveis);
        else imprimeVitoriaTom (I, Niveis);

        // Avisa ao jogador que deve pressionar uma tecla para proceder
        printf (AZUL "\nPressione qualquer botão para proceder!\n\n" RESET);

        // Aguarda o input do jogador
        getchar ();
        
        // Termina o ciclo
        break;
    }
}



// Corre o menu de edição de presets
void menuEditar (int NivelSelecionado) {

    // Cria o novo preset
    char Preset [52][52] = {0};

    // Inteiro que indica se o preset foi editado com sucesso
    int FoiEditado = 0;

    // Inteiros que indicam a linha e a coluna nas quais se está a trabalhar
    int L = 0, C = 0;

    // Corre o menu
    while (1) {

        // Limpa a terminal
        printf ("\033[2J\033[H");

        // Imprime o menu de edição
        imprimeMenuEdicao (NivelSelecionado, Preset, L);

        // Recebe o input do jogador
        char Input = getchar ();

        // Verifica se o jogador pretende sair do menu de edição
        if (Input == 's') break;

        // Verifica se o jogador pretende saber mais sobre a edição de presets
        else if (Input == 'h') menuAjudaEditar ();

        // Verifica se o jogador pretende terminar a edição
        else if (Input == 't' || L > 50) {

            // Verifica se o preset é válido
            if (presetValido (Preset, L)) {
                FoiEditado = 1;
                break;
            }
        }

        // Verifica se o jogador pretende avançar uma linha
        else if (Input == '\n' && C) {
            L++;
            C = 0;
        }

        // Verifica se o jogador adicionou algo ao labirinto
        else if (Input == '#' || Input == 'Q' || Input == 'F' || Input == 'J' || Input == 'T' || Input == 'B' ||
                 Input == 'G' || Input == '-' || Input == 'P' || Input == 'p' || Input == 'C') {
                    Preset [L][C++] = Input;
                    if (C > 50) {
                        L++;
                        C = 0;
                    }
                 }

        // Verifica se o jogador eliminou algo do labirinto
        else if (Input == 'u' && (L || C)) {
            if (C == 0) for (L--; Preset [L][C]; C++);
            else Preset [L][--C] = 0;
        }
    }

    // Edita o preset
    if (FoiEditado) editaPreset (Preset, L, NivelSelecionado);
}



// Corre o menu de ajuda da edição de presets
void menuAjudaEditar () {

    // Mantém o menu aberto até ao jogador pressionar 's'
    while (1) {

        // Limpa a terminal
        printf ("\033[2J\033[H");

        // Imprime o menu de ajuda de edição
        imprimeMenuAjudaEdicao ();

        // Recebe o input do jogador
        if (getchar () == 'q') break;
    }
}