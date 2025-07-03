#include "Labyrinth.h"

// Função principal
int main () {

    // Armazena as configurações originais da terminal
    struct termios Original;
    tcgetattr (STDIN_FILENO, &Original);

    // Altera as configurações da terminal
    struct termios Novo = Original;
    Novo.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &Novo);

    // Inteiro que indica quantos níveis já foram concluídos
    int NiveisConcluidos = 0;

    // Inteiro que indica se houve um erro durante a execução do jogo
    int HouveErro = 0;

    // Lê quantos níveis foram concluídos
    if (leNiveisConcluidos (&NiveisConcluidos)) HouveErro = 1;

    // Abre o menu principal
    else if (menuPrincipal (&NiveisConcluidos)) HouveErro = 1;

    // Guarda quantos níveis foram concluídos
    else if (guardaNiveisConcluidos (NiveisConcluidos)) HouveErro = 1;

    // Restaura a configuração original da terminal
    tcsetattr (STDIN_FILENO, TCSANOW, &Original);

    // Avisa se houve um erro durante a execução do jogo
    if (HouveErro) printf (VERMELHO "Ocorreu um erro!\n" RESET);

    // Retorna o valor de sucesso da função
    return HouveErro;
}