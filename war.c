#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funções para manipulação de missões
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    // Sorteia uma missão aleatória para o jogador
    int indiceMissao = rand() % totalMissoes;
    strcpy(destino, missoes[indiceMissao]);
}

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n===== ESTADO ATUAL DOS TERRITÓRIOS =====\n");
    for (int i = 0; i < total; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("----------------------------------------\n");
    }
}

// Função que simula o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    // Validação: não pode atacar território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é permitido atacar um território da mesma cor!\n");
        return;
    }

    // Simulação de dados (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nSimulando ataque...\n");
    printf("Dado do atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Ataque bem-sucedido!\n");

        // Transferência da cor e metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        printf("%s conquistou o território %s!\n", atacante->nome, defensor->nome);
    } else {
        printf("Resultado: Ataque fracassado.\n");

        // O atacante perde uma tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Função para verificar se o jogador cumpriu a missão
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Verificando a missão de "conquistar 3 territórios seguidos"
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho - 1; i++) {
            if (strcmp(mapa[i].cor, mapa[i + 1].cor) == 0 && mapa[i].tropas > 0 && mapa[i + 1].tropas > 0) {
                consecutivos++;
            }
        }
        if (consecutivos >= 2) {
            return 1; // Missão cumprida
        }
    }

    // Verificação para "Eliminar todas as tropas da cor vermelha"
    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) {
                return 0; // Missão não cumprida, ainda existem tropas vermelhas
            }
        }
        return 1; // Missão cumprida
    }

    // Caso não haja missões cumpridas
    return 0;
}

// Função de liberação da memória alocada
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Vetor de missões possíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar todos os territórios de uma cor",
        "Ter mais tropas do que qualquer jogador",
        "Destruir a maior cidade inimiga"
    };

    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    int totalTerritorios;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*) malloc(totalTerritorios * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Alocação dinâmica para armazenar a missão do jogador
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para missão!\n");
        return 1;
    }

    // Cadastro de territórios
    cadastrarTerritorios(mapa, totalTerritorios);

    // Sorteio e atribuição de missão para o jogador
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("\nSua missão é: %s\n", missaoJogador);

    // Exibição dos territórios
    exibirTerritorios(mapa, totalTerritorios);

    // Verificação da missão após o ataque
    int idAtacante, idDefensor;
    printf("\nEscolha o número do território ATACANTE (1 a %d): ", totalTerritorios);
    scanf("%d", &idAtacante);

    printf("Escolha o número do território DEFENSOR (1 a %d): ", totalTerritorios);
    scanf("%d", &idDefensor);

    // Validação básica
    if (idAtacante < 1 || idAtacante > totalTerritorios ||
        idDefensor < 1 || idDefensor > totalTerritorios ||
        idAtacante == idDefensor) {
        printf("IDs inválidos. O ataque não será realizado.\n");
    } else {
        atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
    }

    // Verificar missão
    if (verificarMissao(missaoJogador, mapa, totalTerritorios)) {
        printf("Parabéns! Você cumpriu sua missão e venceu o jogo!\n");
    }

    // Liberação de memória
    liberarMemoria(mapa, missaoJogador);

    return 0;
}
