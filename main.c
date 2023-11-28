#include "./headers/criptografia.h"

int main(){
    FILE* arqEntrada, arqSaida;
    int cifra, random;
    char nomeArquivoEntrada[40];
    char path[100] = "./entradas/";

    printf("Digite o nome do arquivo (sem a extensão .txt)\n>>> ");
    scanf("%s", nomeArquivoEntrada);
    strcat(path, nomeArquivoEntrada);
    strcat(path, ".txt");

    printf("Como deseja gerar a cifra?\n[ 0 ] Digitar\n[ 1 ] Geraração aleatória\n>>> ");
    scanf("%d", &random);
    if(random){
        printf("Digite a cifra \n>>> ");
        scanf("%d", &cifra);    
    }else{
        srand((unsigned)time(NULL));
        cifra = 1+rand()%25;
    }


    manipulaArquivo(path, cifra, random, 1);
}