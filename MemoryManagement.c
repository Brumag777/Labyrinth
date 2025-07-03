#include "Labyrinth.h"

// Liberta a memória alocada para a informação do nível
void libertaInfo (InfoNivel *I, int dL) {
    if (*I) {
        if ((*I) -> M.Lab) {
            for (int i = 0; i < dL; i++)
                if ((*I) -> M.Lab [i]) free ((*I) -> M.Lab [i]);
            free ((*I) -> M.Lab);
        } free (*I);
        *I = NULL;
    }
}



// Inicia um nível
InfoNivel iniciaNivel (int NivelSelecionado, int PvE, int Niveis) {

    // Aloca memória o struct
    InfoNivel I = malloc (sizeof (INFONIVEL));

    // Verifica se houve um erro ao alocar memória
    if (I == NULL) return NULL;

    // Inicializa os componentes do struct
    inicializaInfo (I, PvE);

    // Lê o ficheiro
    int n = leNivel (I, NivelSelecionado, Niveis);

    // Verifica se houve um erro ao ler o ficheiro
    if (n) libertaInfo (&I, n);

    // Retorna o struct
    return I;
}