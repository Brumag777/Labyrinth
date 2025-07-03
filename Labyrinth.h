#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAGENTA "\033[38;2;255;0;255m"
#define VERMELHO "\033[38;2;255;0;0m"
#define AZUL "\033[38;2;50;50;255m"
#define VERDE "\033[38;2;0;255;0m"
#define RESET "\033[0m"

// Mapa do jogo
typedef struct mapa {
    int dL, dC;
    char **Lab;
} Mapa;

// Informação sobre um personagem
typedef struct personagem {
    int Stamina;
    int L, C;
} Personagem;

// Informação sobre um objeto
typedef struct objeto {
    int Ativo;
    int L, C;
} Objeto;

// Informação sobre um nível
typedef struct infoNivel {
    Mapa M;
    Personagem Jerry;
    Personagem Tom;
    Objeto Chave;
    int PvE;
    int Nevoeiro;
} INFONIVEL, *InfoNivel;





// Menus.c

// Corre o menu principal
int menuPrincipal (int *NiveisConcluidos);

// Corre o menu de ajuda
void menuAjuda (int NiveisConcluidos);

// Corre o menu de um nível
int jogo (int NivelSelecionado, int *NiveisConcluidos, int PvE, int Niveis);

// Corre o menu de vitória do Jerry
void menuVitoria (int EJerry, InfoNivel I, int Niveis);

// Corre o menu de edição de presets
void menuEditar (int NivelSelecionado);

// Corre o menu de ajuda da edição de presets
void menuAjudaEditar ();





// MemoryManagement.c

// Liberta a memória alocada para a informação do nível
void libertaInfo (InfoNivel *I, int dL);

// Inicia um nível
InfoNivel iniciaNivel (int NivelSelecionado, int PvE, int Niveis);





// NiveisConcluidos.c

// Lê quantos níveis foram concluídos
int leNiveisConcluidos (int *NiveisConcluidos);

// Guarda quantos níveis foram concluídos
int guardaNiveisConcluidos (int NiveisConcluidos);





// Niveis.c

// Lê as posicões dos personagens e da chave
int lePosicoes (InfoNivel I, FILE *F);

// Lê o labirinto
int leLabirinto (Mapa *M, FILE *F);

// Lê um nível
int leNivel (InfoNivel I, int NivelSelecionado, int Niveis);

// Edita um preset
void editaPreset (char Preset [52][52], int L, int NivelSelecionado);





// Imprime.c

// Imprime o menu principal
void imprimeMenuPrincipal (int NiveisConcluidos, int NivelSelecionado, int PvE, int Niveis);

// Imprime o menu de ajuda
void imprimeMenuAjuda (int NiveisConcluidos);

// Imprime o labirinto
void imprimeLabirinto (InfoNivel I, int NivelSelecionado, int Niveis);

// Imprime o menu de vitória do Jerry
void imprimeVitoriaJerry (InfoNivel I, int Niveis);

// Imprime o menu de vitória do Tom
void imprimeVitoriaTom (InfoNivel I, int Niveis);

// Imprime o menu de edição de presets
void imprimeMenuEdicao (int NivelSelecionado, char Preset [52][52], int L);

// Imprime um preset até a uma dada linha e uma dada coluna
void imprimePreset (char Preset [52][52], int L);

// Imprime o menu de ajuda edição de presets
void imprimeMenuAjudaEdicao ();





// Logo.c

// Imprime um logo
void imprimeLogo (int NivelSelecionado, int Niveis);





// Auxiliares.c

// Altera o nível selecionado no menu principal
void alteraNivelSelecionado (int *NivelSelecionado, char Input);

// Inicializa os componentes da informação do nível
void inicializaInfo (InfoNivel I, int PvE);

// Verifica se o Jerry ganhou
int vitoriaJerry (InfoNivel I);

// Verifica se o Tom ganhou
int vitoriaTom (InfoNivel I);

// Calcula o mínimo de quatro valores
int minimo (int a, int b, int c, int d);

// Verifica se o próximo passo é uma chave ou uma porta
void verificaBloqueio (InfoNivel I, char *direcao);

// Verifica se um dado preset é válido
int presetValido (char Preset [52][52], int L);





// LogicaNivel.c

// Verifica se o jogo terminou
int fimJogo (InfoNivel I, int NivelSelecionado, int *NiveisConcluidos, int Niveis);

// Realiza uma jogada
int realizaJogada (InfoNivel I, char Input);

// Realiza uma jogada do Jerry
int realizaJogadaJerry (InfoNivel I, char Input);

// Verifica se uma jogada do Jerry é válida
int jogadaJerryValida (InfoNivel I, int lF, int cF);

// Realiza uma jogada do Tom
int realizaJogadaTom (InfoNivel I, char Input);

// Verifica se uma jogada do Tom é válida
int jogadaTomValida (InfoNivel I, int lF, int cF);





// AI.c

// Encontra a direção do caminho mais curto do Tom até ao Jerry
char encontraDirecao (InfoNivel I, int L, int C);

// Indica o tamanho do caminho mais curto do Tom até ao Jerry
int encontraCaminho (InfoNivel I, int L, int C, int PortasBloqueiam);