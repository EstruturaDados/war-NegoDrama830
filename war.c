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

// Liberação da memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int totalTerritorios;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*) malloc(totalTerritorios * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, totalTerritorios);

    // Exibição inicial
    exibirTerritorios(mapa, totalTerritorios);

    // Escolha de ataque
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

    // Exibição pós-ataque
    exibirTerritorios(mapa, totalTerritorios);

    // Liberação de memória
    liberarMemoria(mapa);

    return 0;
}
