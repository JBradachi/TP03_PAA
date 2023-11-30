#include "./headers/criptografia.h"

int main(){
    FILE* arqEntrada, arqSaida;
    int cifra, random, cripto;
    char nomeArquivoEntrada[40];
    char path[100] = "./entradas/";

    printf("Digite o nome do arquivo (sem a extensão .txt)\n>>> ");
    scanf("%s", nomeArquivoEntrada);
    strcat(path, nomeArquivoEntrada);
    strcat(path, ".txt");

    printf("Deseja desencriptografar[ 0 ] ou encriptografar[ 1 ]?");
    scanf("%d", &cripto);

    printf("Como deseja gerar a cifra?\n[ 0 ] Digitar\n[ 1 ] Geraração aleatória\n>>> ");
    scanf("%d", &random);
    if(random){
        srand((unsigned)time(NULL));
        cifra = 1+rand()%25;
    }else{
        printf("Digite a cifra \n>>> ");
        scanf("%d", &cifra); 
    }


    manipulaArquivo(path, cifra, random, cripto);
}