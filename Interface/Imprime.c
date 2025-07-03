#include "../Labyrinth.h"

// Imprime o menu principal
void imprimeMenuPrincipal (int NiveisConcluidos, int NivelSelecionado, int PvE, int Niveis) {

    // Imprime o logo
    imprimeLogo (0, 0);

    // Armazena os níveis concluídos
    int NC = NiveisConcluidos;

    // Decrementa NiveisConcluidos caso modo de jogo seja PvP
    if (PvE == 0) NiveisConcluidos--;

    // Indica ao jogador que deve selecionar um nível
    if (Niveis) printf (AZUL "                                                                                          Selecione um nível!\n\n" RESET);
    else printf (AZUL "                                                                                          Selecione um preset!\n\n" RESET);

    // Imprime os níveis
    NiveisConcluidos++;
    printf ("                                                                                         ╔═══╦═══╦═══╦═══╦═══╗\n");
    for (int i = 0; i < 5; i++) {
        printf ("                                                                                         ║");
        for (int j = 0; j < 5; j++) {
            int n = 5 * i + j + 1;
            if (n == NivelSelecionado) {
                if (NiveisConcluidos) {
                    NiveisConcluidos--;
                    printf (AZUL);
                } else printf (MAGENTA);
            } else if (NiveisConcluidos) {
                NiveisConcluidos--;
                printf (VERDE);
            } else printf (VERMELHO);
            if (n < 10) printf ("00");
            else putchar ('0');
            printf ("%d" RESET "║", 5 * i + j + 1);
        } putchar ('\n');
        if (i < 4) printf ("                                                                                         ╠═══╬═══╬═══╬═══╬═══╣\n");
        else printf ("                                                                                         ╚═══╩═══╩═══╩═══╩═══╝\n");
    }

    // Indica ao jogador o modo de jogo selecionado
    if (PvE) printf (AZUL "\n                                                                                       Modo de jogo: Player VS PC\n" RESET);
    else printf (AZUL "\n                                                                                     Modo de jogo: Player VS Player\n" RESET);

    // Easter egg
    if (NC == 25) printf (MAGENTA "\n                                                                                   Pressione 't' para acessar presets!\n" RESET);
}



// Imprime o menu de ajuda
void imprimeMenuAjuda (int NiveisConcluidos) {

    // Imprime o logo
    imprimeLogo (-1, 0);

    // Explica o jogo
    printf (MAGENTA "Tema do jogo\n\n"
            AZUL "Tom's Labyrinth" RESET " é um jogo de estratégia que pode ser jogado de duas formas: " AZUL "Player VS PC" RESET " ou " AZUL "Player VS Player.\n" RESET
            "O modo de jogo " AZUL "Player VS PC" RESET " é de um jogador e este controla o Jerry enquanto que o computador controla o Tom.\n"
            "O modo de jogo " AZUL "Player VS Player" RESET " é de dois jogadores, um que controla o Jerry e outro que controla o Tom.\n"
            "Os níveis só podem ser jogados no modo de jogo " AZUL "Player VS Player" RESET " após serem terminados no modo " AZUL "Player VS PC.\n\n" RESET
            MAGENTA "Objetivos\n\n"
            AZUL "Objetivo do Jerry (🐭):" RESET " Obter a chave para poder escapar do labirinto por uma porta.\n"
            AZUL "Objetivo do Tom (😼):" RESET " Apanhar o Jerry antes que escape do labirinto.\n\n"
            MAGENTA "Mecânicas do jogo\n\n"
            AZUL "Estamina (" VERDE " ⚡" AZUL "):" RESET " Os personagens podem mover uma vez por ponto de estamina e recebem um ponto de estamina sempre que o outro personagem fica sem estamina.\n"
            AZUL "Paredes (🧱):" RESET " Qualquer quadrado com parede previne a passagem de ambos os personagens.\n"
            AZUL "Chave (🔑):" RESET " Existe apenas uma chave no mapa e apenas pode ser obtida pelo Jerry. Portas não podem ser abertas sem a chave.\n"
            AZUL "Portas (🚪):" RESET " Portas funcionam como paredes até serem abertas (eliminadas) pelo Jerry após obter a chave.\n"
            AZUL "Grades (⛓️ ):" RESET " Grades são paredes que podem ser quebradas pelo Tom.\n"
            AZUL "Queijo (🧀):" RESET " Queijo é um objeto coletável por ambos os personagens. Se o Jerry obter queijo irá receber 5 de estamina extra.\n"
            AZUL "Peixe (🐟):" RESET " Peixe é um objeto coletável por ambos os personagens. Se o Tom obter peixe irá receber 5 de estamina extra.\n"
            AZUL "Bomba de névoa (💣):" RESET " Bomba de névoa é um objeto coletável por ambos os personagens. Quando coletada, o(s) jogadore(s) perdem a visão do mapa durante cinco turnos.\n\n"
            MAGENTA "Controlos\n\n"
            AZUL "w:" RESET " Sobe o nível selecionado ou o personagem a jogar.\n"
            AZUL "s:" RESET " Desce o nível selecionado ou o personagem a jogar.\n"
            AZUL "d:" RESET " Move o nível selecionado ou o personagem a jogar para a direita.\n"
            AZUL "a:" RESET " Move o nível selecionado ou o personagem a jogar para a esquerda.\n"
            AZUL "m:" RESET " Altera o modo de jogo no menu principal.\n"
            AZUL "q:" RESET " Termina o jogo ou o nível.\n\n");

    // Easter egg
    if (NiveisConcluidos == 25)
        printf (MAGENTA "Easter egg\n\n"
                AZUL "Pressione 't' no menu principal para acessar os presets!\n" RESET
                AZUL "Pressione 'e' para editar o preset selecionado!\n\n" RESET);
}



// Imprime o labirinto
void imprimeLabirinto (InfoNivel I, int NivelSelecionado, int Niveis) {

    // Verifica se o jogo ainda não terminou
    if (NivelSelecionado) imprimeLogo (NivelSelecionado, Niveis);

    // Indica a estamina dos personagens
    if (I -> Jerry.Stamina > 0) {
        printf ("🐭");
        for (int i = 0; i < I -> Jerry.Stamina; i++) printf (VERDE " ⚡" RESET);
    } else {
        printf ("😼");
        for (int i = 0; i < I -> Tom.Stamina; i++) printf (VERDE " ⚡" RESET);
    } putchar ('\n');

    // Imprime o labirinto
    for (int i = 0; i < I -> M.dL; i++) {
        for (int j = 0; j < I -> M.dC; j++)
            if (I -> M.Lab [i][j] == '#') printf ("🧱");
            else if (I -> M.Lab [i][j] == 'G') printf ("⛓️ ");
            else if (0 && I -> Nevoeiro && NivelSelecionado) printf ("🌫️ ");
            else if (i == I -> Jerry.L && j == I -> Jerry.C) printf ("🐭");
            else if (i == I -> Tom.L && j == I -> Tom.C) printf ("😼");
            else if (i == I -> Chave.L && j == I -> Chave.C) printf ("🔑");
            else if (I -> M.Lab [i][j] == 'B') printf ("💣");
            else if (I -> M.Lab [i][j] == 'p' || I -> M.Lab [i][j] == 'P') printf ("🚪");
            else if (I -> M.Lab [i][j] == 'F') printf ("🐟");
            else if (I -> M.Lab [i][j] == 'Q') printf ("🧀");
            else printf ("  ");
        putchar ('\n');
    }

    // Indica quanto nevoeiro ainda resta
    if (I -> Nevoeiro) {
        for (int i = 0; i < I -> Nevoeiro; i++) printf ("🌫️  ");
        putchar ('\n');
    }
}



// Imprime o menu de vitória do Jerry
void imprimeVitoriaJerry (InfoNivel I, int Niveis) {
    
    // Imprime a mensagem
    printf ("_______________________________________________________________________________________________________________________________________________________________________________________________________\n\n"
            "                                        ██████╗          ██╗███████╗██████╗ ██████╗ ██╗   ██╗    ███████╗███████╗ ██████╗ █████╗ ██████╗  ██████╗ ██╗   ██╗██╗\n"
            "                                       ██╔═══██╗         ██║██╔════╝██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗██╔═══██╗██║   ██║██║\n"
            "                                       ██║   ██║         ██║█████╗  ██████╔╝██████╔╝ ╚████╔╝     █████╗  ███████╗██║     ███████║██████╔╝██║   ██║██║   ██║██║\n"
            "                                       ██║   ██║    ██   ██║██╔══╝  ██╔══██╗██╔══██╗  ╚██╔╝      ██╔══╝  ╚════██║██║     ██╔══██║██╔═══╝ ██║   ██║██║   ██║╚═╝\n"
            "                                       ╚██████╔╝    ╚█████╔╝███████╗██║  ██║██║  ██║   ██║       ███████╗███████║╚██████╗██║  ██║██║     ╚██████╔╝╚██████╔╝██╗\n"
            "                                        ╚═════╝      ╚════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝      ╚═════╝  ╚═════╝ ╚═╝\n"
            "________________________________________________________________________________________________________________________________________________________________________________________________________\n\n");

    // Imprime o labirinto
    imprimeLabirinto (I, 0, Niveis);
}



// Imprime o menu de vitória do Tom
void imprimeVitoriaTom (InfoNivel I, int Niveis) {

    // Imprime a mensagem
    printf ("_______________________________________________________________________________________________________________________________________________________________________________________________________\n\n"
            "                       ██████╗          ██╗███████╗██████╗ ██████╗ ██╗   ██╗    ███████╗ ██████╗ ██╗     █████╗ ██████╗  █████╗ ███╗   ██╗██╗  ██╗ █████╗ ██████╗  ██████╗ ██╗\n"
            "                      ██╔═══██╗         ██║██╔════╝██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔════╝██╔═══██╗██║    ██╔══██╗██╔══██╗██╔══██╗████╗  ██║██║  ██║██╔══██╗██╔══██╗██╔═══██╗██║\n"
            "                      ██║   ██║         ██║█████╗  ██████╔╝██████╔╝ ╚████╔╝     █████╗  ██║   ██║██║    ███████║██████╔╝███████║██╔██╗ ██║███████║███████║██║  ██║██║   ██║██║\n"
            "                      ██║   ██║    ██   ██║██╔══╝  ██╔══██╗██╔══██╗  ╚██╔╝      ██╔══╝  ██║   ██║██║    ██╔══██║██╔═══╝ ██╔══██║██║╚██╗██║██╔══██║██╔══██║██║  ██║██║   ██║╚═╝\n"
            "                      ╚██████╔╝    ╚█████╔╝███████╗██║  ██║██║  ██║   ██║       ██║     ╚██████╔╝██║    ██║  ██║██║     ██║  ██║██║ ╚████║██║  ██║██║  ██║██████╔╝╚██████╔╝██╗\n"
            "                       ╚═════╝      ╚════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚═╝      ╚═════╝ ╚═╝    ╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝\n"
            "________________________________________________________________________________________________________________________________________________________________________________________________________\n\n");

    // Imprime o labirinto
    imprimeLabirinto (I, 0, Niveis);
}



// Imprime o menu de edição de presets
void imprimeMenuEdicao (int NivelSelecionado, char Preset [52][52], int L) {

    // Imprime o logo
    imprimeLogo (NivelSelecionado, 0);

    // Indica ao jogador que pode pressionar 'h' para uma explicação da edição
    printf (AZUL "\nPressione 'h' para saber mais!\n\n" RESET);

    // Imprime o novo preset
    imprimePreset (Preset, L);
}



// Imprime um preset até a uma dada linha e uma dada coluna
void imprimePreset (char Preset [52][52], int L) {

    // Percorre o preset
    for (int i = 0; i <= L; i++) {
        for (int j = 0; Preset [i][j]; j++)
            if (Preset [i][j] == '#') printf ("🧱");
            else if (Preset [i][j] == 'G') printf ("⛓️ ");
            else if (Preset [i][j] == 'J') printf ("🐭");
            else if (Preset [i][j] == 'T') printf ("😼");
            else if (Preset [i][j] == 'C') printf ("🔑");
            else if (Preset [i][j] == 'B') printf ("💣");
            else if (Preset [i][j] == 'p' || Preset [i][j] == 'P') printf ("🚪");
            else if (Preset [i][j] == 'F') printf ("🐟");
            else if (Preset [i][j] == 'Q') printf ("🧀");
            else printf ("  ");
        if (i < L) putchar ('\n');
    }
}



// Imprime o menu de ajuda edição de presets
void imprimeMenuAjudaEdicao () {

    // Imprime o logo
    imprimeLogo (-1, 0);

    // Explica a edição de presets
    printf (MAGENTA "Caracteres\n\n"
            AZUL "#" RESET " representa as paredes (🧱).\n"
            AZUL "G" RESET " representa as grades (⛓️ ).\n"
            AZUL "J" RESET " representa o Jerry (🐭).\n"
            AZUL "T" RESET " representa o Tom (😼).\n"
            AZUL "C" RESET " representa a chave (🔑).\n"
            AZUL "B" RESET " representa a bomba de névoa (💣).\n"
            AZUL "p" RESET " representa uma porta interior (🚪), isto é, o Jerry não ganha ao atravessá-la.\n"
            AZUL "P" RESET " representa uma porta exterior (🚪), isto é, o Jerry ganha ao atravessá-la.\n"
            AZUL "F" RESET " representa peixe (🐟).\n"
            AZUL "Q" RESET " representa queijo (🧀).\n\n"
            MAGENTA "Restrições\n\n"
            AZUL "Deve haver exatamente um Jerry, um Tom, uma chave e pelo menos uma porta exterior.\n" RESET
            AZUL "O número máximo de linhas e de colunas é 50.\n\n" RESET
            MAGENTA "Nota:" AZUL " Pressione 's' para sair do menu de edição.\n\n" RESET);
}