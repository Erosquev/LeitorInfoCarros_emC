#include <stdio.h>

struct Carro {
    char marcaCarro[20];
    char modeloCarro[30];
    int anoFabCarro;
    int kmAtualCarro;
    float precoCarro;
};

int main() {

    struct Carro carros[];
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("carros.txt", "r");

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

    return 0;

}