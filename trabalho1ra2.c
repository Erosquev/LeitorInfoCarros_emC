#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAMANHO_MARCA 20
#define MAX_TAMANHO_CARRO 30
#define INCREMENTAR 10

typedef struct {
    char marcaCarro[MAX_TAMANHO_MARCA];
    char modeloCarro[MAX_TAMANHO_CARRO];
    int anoFabCarro;
    int kmAtualCarro;
    float precoCarro;
} Carro;

//  essa função vai ser usada mais tarde em inserir_novo_carro para colocar os carros no vetor em ordem crescente de preço
int ordenar_carros(const void *a, const void *b){
    const Carro *carroA = (const Carro *)a;
    const Carro *carroB = (const Carro *)b;
    return (carroA->precoCarro > carroB->precoCarro) - (carroA->precoCarro < carroB->precoCarro);
}

// função para inserir um novo carro usando realloc
void inserir_novo_carro(Carro **vetor, int *tamanho, int *capacidade, Carro novo_carro) {
    if (*tamanho >= *capacidade) {
        *capacidade += INCREMENTAR;
        Carro *temporaria = realloc(*vetor, *capacidade * sizeof(Carro));
        if (temporaria == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }
        *vetor = temporaria;
    }

    (*vetor)[*tamanho] = novo_carro;
    (*tamanho)++;
    qsort(*vetor, *tamanho, sizeof(Carro), ordenar_carros);
};

void remover_registros(Carro *vetor, int *tamanho, int km_fornecido){
    // a variável i percorre o vetor e j procura a proxima posição válida no vetor
    int i, j = 0;
    for (int i = 0; i < *tamanho; i++) {
        if (vetor[i].kmAtualCarro <= km_fornecido) {
            vetor[j++] = vetor[i];
        }
    }
    // se a km do carro estiver dentro do limite, esse é copiado para j, e no final j é o novo tamanho do vetor
    // ja que representa a quantidade de carros validos
    *tamanho = j;

};

int main() {
    int capacidade = INCREMENTAR;
    int tamanho = 0;
    Carro *vetor;
    Carro *carros = malloc(capacidade * sizeof(Carro));

    if (carros == NULL){
        printf("erro ao alocar a memória inicial.");
        return 1;
    }

    FILE *arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL){
        printf("Erro ao tentar abrir o arquivo.\n");
        free(carros);
        return 1;
    }
    
    Carro carro;
    char linha[100];


    if(arquivo == NULL){
        printf("Erro ao abrir arquivo. \n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL){

        sscanf(linha, "%s", carro.marcaCarro); 

        fgets(linha, sizeof(linha), arquivo);
        sscanf(linha, "%s", carro.modeloCarro);

        fgets(linha, sizeof(linha), arquivo);
        sscanf(linha, "%d", carro.anoFabCarro);

        fgets(linha, sizeof(linha), arquivo);
        sscanf(linha, "%d", carro.kmAtualCarro);

        fgets(linha, sizeof(linha), arquivo);
        sscanf(linha, "%f", carro.precoCarro);
    }

    fclose(arquivo);
    int operacoes_usuario;

    do {
        printf("\nPossiveis Operações:\n");
        printf("1. Imprimir todos os registros\n");
        printf("2. Exibir registros de uma marca específica\n");
        printf("3. Exibir registros com preço entre um valor mínimo e máximo\n");
        printf("4. Inserir um novo registro\n");
        printf("5. Remover registros com kilometragem superior ao valor desejado\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &operacoes_usuario);
    if (operacoes_usuario == 1){
        printf("Carros ordenados:\n");
        for (int i = 0; i < tamanho; i++){
            printf("Modelo: %s, Preço: %.2f\n", carros[i].modeloCarro, carros[i].precoCarro);
        }
    }else if (operacoes_usuario == 4){
        Carro novo_carro;
        printf("Marca: ");
            scanf("%s", novo_carro.marcaCarro);
            printf("Modelo: ");
            scanf(" %[^\n]", novo_carro.modeloCarro);
            printf("Ano: ");
            scanf("%d", &novo_carro.anoFabCarro);
            printf("Kilometragem: ");
            scanf("%d", &novo_carro.kmAtualCarro);
            printf("Preço: ");
            scanf("%f", &novo_carro.precoCarro);
            inserir_novo_carro(&vetor, &tamanho, &capacidade, novo_carro);
    } else if (operacoes_usuario == 5) {
        int km_fornecido;
        printf("Digite a kilometragem limite: ");
        scanf("%d", &km_fornecido);
        remover_registros(carros, &tamanho, km_fornecido);
        printf("Os carros com kilometragem acima do valor dado foram removidos, os carros abaixo do limite são: \n");
        for (int i = 0; i < tamanho; i++){
            printf("Modelo: %s, Preço: %.2f, Kilometragem: %d\n", carros[i].modeloCarro, carros[i].precoCarro, carros[i].kmAtualCarro);
        }
    }
    } while (operacoes_usuario != 6);
    
    free(carros);
    return 0;

}
