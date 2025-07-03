#include "../Labyrinth.h"

// Lê as posicões dos personagens e da chave
int lePosicoes (InfoNivel I, FILE *F) {

    // Inteiro que indica se houve um erro durante a execução do jogo
    int HouveErro = 0;

    // Lê a posição do Jerry
    if (fscanf (F, " %d %d", &I -> Jerry.L, &I -> Jerry.C) != 2) HouveErro = 1;

    // Lê a posição do Tom
    else if (fscanf (F, " %d %d", &I -> Tom.L, &I -> Tom.C) != 2) HouveErro = 1;

    // Lê a posição da chave
    else if (fscanf (F, " %d %d", &I -> Chave.L, &I -> Chave.C) != 2) HouveErro = 1;

    // Avisa se houve ou não um erro durante a execução do jogo
    return HouveErro;
}



// Lê o labirinto
int leLabirinto (Mapa *M, FILE *F) {

    // Lê o número de linhas e de colunas
    if (fscanf (F, " %d %d", &M -> dL, &M -> dC) != 2) return 1;

    // Aloca memória para o labirinto
    M -> Lab = malloc (M -> dL * sizeof (char *));

    // Verifica se houve um erro ao alocar memória
    if (M -> Lab == NULL) return 1;

    // Lê o labirinto
    for (int i = 0; i < M -> dL; i++) {

        // Aloca memória para a linha
        M -> Lab [i] = malloc ((M -> dC + 1) * sizeof (char));

        // Verifica se houve um erro ao alocar memória
        if (M -> Lab [i] == NULL) return i;

        // Lê a linha
        if (fscanf (F, " %s", M -> Lab [i]) != 1) return i + 1;
    }

    // Avisa que a função funcionou corretamente
    return 0; 
}



// Lê um nível
int leNivel (InfoNivel I, int NivelSelecionado, int Niveis) {

    // Inteiro que indica se houve um erro durante a execução do jogo
    int HouveErro = 0;

    // Cria o nome do ficheiro
    char NomeFicheiro [18] = {0};
    sprintf (NomeFicheiro, "Ficheiros/N%d.txt", NivelSelecionado);
    if (Niveis == 0) NomeFicheiro [10] = 'P';

    // Abre o ficheiro
    FILE *F = fopen (NomeFicheiro, "r");

    // Verifica se o ficheiro foi aberto
    if (F == NULL) HouveErro = 1;

    // O ficheiro foi aberto corretamente
    else {

        // Lê as posições dos personagens e da chave
        if (lePosicoes (I, F)) HouveErro = 1;

        // Não houve erro ao ler as posições
        else {

            // Lê o labirinto
            int n = leLabirinto (&I -> M, F);

            // Verifica se houve um erro ao ler o labirinto
            if (n) {

                // Liberta a memória alocada para a informação do nível
                libertaInfo (&I, n);

                // Indica que houve um erro
                HouveErro = 1;
            }
        }

        // Fecha o ficheiro
        fclose (F);
    }

    // Avisa se houve ou não um erro durante a execução do jogo
    return HouveErro;
}



// Edita um preset
void editaPreset (char Preset [52][52], int L, int NivelSelecionado) {

    // Coordenadas da chave, do Jerry e do Tom
    int LC = 0, CC = 0, LJ = 0, CJ = 0, LT = 0, CT = 0;

    // Colunas do labirinto
    int C = 0;

    // Procura as coordenadas
    for (int i = 0; i <= L; i++) {
        int j;
        for (j = 0; Preset [i][j]; j++)
            if (Preset [i][j] == 'C') {
                LC = i;
                CC = j;
            } else if (Preset [i][j] == 'J') {
                LJ = i;
                CJ = j;
            } else if (Preset [i][j] == 'T') {
                LT = i;
                CT = j;
            }
        if (j > C) C = j;
    }

    // Cria o nome do ficheiro
    char NomeFicheiro [18] = {0};
    sprintf (NomeFicheiro, "Ficheiros/P%d.txt", NivelSelecionado);

    // Abre o ficheiro
    FILE *F = fopen (NomeFicheiro, "w");

    // Guarda as posições dos personagens e da chave
    fprintf (F, "%d %d\n%d %d\n%d %d\n", LJ, CJ, LT, CT, LC, CC);

    // Guarda as dimensões do labirinto
    fprintf (F, "%d %d\n", L + 1, C);

    // Guarda o labirinto
    for (int i = 0; i < L; i++)
        fprintf (F, "%s\n", Preset [i]);
    fprintf (F, "%s", Preset [L]);

    // Fecha o ficheiro
    fclose (F);
}