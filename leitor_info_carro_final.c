#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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


void buscar_marca(Carro *vetor, int tamanho, char *marca){
    
    printf("\n Carros da marca %s:\n", marca);
    int encontrados = 0;
    for (int i = 0; i < tamanho; i++){
        if(strcmp(vetor[i].marcaCarro, marca) == 0){
            printf("Modelo: %s, Ano: %d, Kilometragem: %d, Preço: %.2f\n", vetor[i].modeloCarro, vetor[i].anoFabCarro, vetor[i].kmAtualCarro, vetor[i].precoCarro);
            encontrados++;
        };
    };

    if (encontrados == 0) {
        printf("Nenhum carro encontrado desta marca.");
    };
};

void buscar_preco(Carro *vetor, int tamanho){
    float valorMinimo;
    float valorMaximo;
    printf("Digite o valor mínimo para buscar: ");
    scanf("%f", &valorMinimo);
    printf("Digite o valor máximo para buscar: ");
    scanf("%f", &valorMaximo);
    printf("\n");
    printf("Os carros dentro da faixa de preço digitada são: \n");
    int encontrados = 0;
    for (int i = 0; i< tamanho; i++){
        if(vetor[i].precoCarro >= valorMinimo && vetor[i].precoCarro <= valorMaximo){
            printf("Marca: %s, Modelo: %s, Ano: %d, Kilometragem: %d, Preço: %.2f\n",
                   vetor[i].marcaCarro, vetor[i].modeloCarro, vetor[i].anoFabCarro,
                   vetor[i].kmAtualCarro, vetor[i].precoCarro);
                   encontrados++;
        }
    }
    if (encontrados == 0){
        printf("Nenhum carro foi encontrado nessa faixa de preço\n");
    }
}; 

int main() {
    int capacidade = INCREMENTAR;
    int tamanho = 0;
    
    Carro *vetor = malloc(capacidade * sizeof(Carro));

    if (vetor == NULL){
        printf("erro ao alocar a memória inicial.");
        return 1;
    }

    FILE *arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL){
        printf("Erro ao tentar abrir o arquivo.\n");
        free(vetor);
        return 1;
    }
    
    Carro carro;
    char linha[100];


    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%19s", carro.marcaCarro) != 1) {
            printf("Erro ao ler a marca do carro.\n");
            continue;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL || sscanf(linha, "%29s", carro.modeloCarro) != 1) {
            printf("Erro ao ler o modelo do carro.\n");
            continue;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL || sscanf(linha, "%d", &carro.anoFabCarro) != 1) {
            printf("Erro ao ler o ano do carro.\n");
            continue;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL || sscanf(linha, "%d", &carro.kmAtualCarro) != 1) {
            printf("Erro ao ler a kilometragem do carro.\n");
            continue;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL || sscanf(linha, "%f", &carro.precoCarro) != 1) {
            printf("Erro ao ler o preço do carro.\n");
            continue;
        }

        inserir_novo_carro(&vetor, &tamanho, &capacidade, carro);}

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
            printf("Modelo: %s, Preço: %.2f, Marca: %s, Kilometragem Atual: %d\n", vetor[i].modeloCarro, vetor[i].precoCarro, vetor[i].marcaCarro, vetor[i].kmAtualCarro);
        }
    } else if (operacoes_usuario == 2){

        char marca[MAX_TAMANHO_MARCA];
        printf("Digite uma marca para buscar: \n");
        scanf("%s", marca);
        buscar_marca(vetor, tamanho, marca);

    } else if (operacoes_usuario == 3){
        
        buscar_preco(vetor, tamanho);


    } else if (operacoes_usuario == 4){
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
        remover_registros(vetor, &tamanho, km_fornecido);
        printf("Os carros com kilometragem acima do valor dado foram removidos, os carros abaixo do limite são: \n");
        for (int i = 0; i < tamanho; i++){
            printf("Modelo: %s, Preço: %.2f, Kilometragem: %d\n", vetor[i].modeloCarro, vetor[i].precoCarro, vetor[i].kmAtualCarro);
        }
    } else if (operacoes_usuario == 6){
        printf("Programa encerrado.");
    }
    } while (operacoes_usuario != 6);

    
    free(vetor);
    return 0;

    }
