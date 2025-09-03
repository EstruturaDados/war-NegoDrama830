#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Agrupa as informações de cada território: nome, cor do exército e número de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor de structs para armazenar 5 territórios
    struct Territorio territorios[5];

    // Entrada de dados para os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome);  // lê a linha inteira com espaços

        // Entrada da cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %s", territorios[i].cor);

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Espaço entre os cadastros
    }

    // Exibição dos dados de todos os territórios
    printf("\n===== DADOS DOS TERRITÓRIOS CADASTRADOS =====\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------------------------\n");
    }

    return 0;
}
