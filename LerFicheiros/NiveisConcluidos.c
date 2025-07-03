#include "../Labyrinth.h"

// Lê quantos níveis foram concluídos
int leNiveisConcluidos (int *NiveisConcluidos) {

    // Inteiro que indica se houve um erro durante a execução do jogo
    int HouveErro = 0;

    // Abre o ficheiro
    FILE *F = fopen ("Ficheiros/NiveisConcluidos.txt", "r");

    // Verifica se o ficheiro foi aberto
    if (F == NULL) HouveErro = 1;
    
    // O ficheiro foi aberto corretamente
    else {
        
        // Lê o número de níveis concluídos
        if (fscanf (F, "%d", NiveisConcluidos) != 1) HouveErro = 1; 

        // Fecha o ficheiro
        fclose (F);
    }

    // Avisa se houve ou não um erro durante a execução do jogo
    return HouveErro;
}



// Guarda quantos níveis foram concluídos
int guardaNiveisConcluidos (int NiveisConcluidos) {

    // Inteiro que indica se houve um erro durante a execução do jogo
    int HouveErro = 0;

    // Abre o ficheiro
    FILE *F = fopen ("Ficheiros/NiveisConcluidos.txt", "w");

    // Verifica se o ficheiro foi aberto
    if (F == NULL) HouveErro = 1;

    // O ficheiro foi aberto corretamente
    else {

        // Guarda o número de níveis concluídos
        fprintf (F, "%d", NiveisConcluidos);

        // Fecha o ficheiro
        fclose (F);
    }

    // Avisa se houve ou não um erro durante a execução do jogo
    return HouveErro;
}