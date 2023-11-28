#include "./headers/criptografia.h"

int main(){
    FILE* arqEntrada, arqSaida;
    int cifra;
    char nomeArquivoEntrada[40];
    char path[100] = "./entradas/";

    printf("Digite o nome do arquivo (sem a extensão .txt)\n>>> ");
    scanf("%s", nomeArquivoEntrada);
    strcat(path, nomeArquivoEntrada);
    strcat(path, ".txt");

    printf("Digite a cifra\n>>> ");
    scanf("%d", &cifra);

    manipulaArquivo(path, cifra);
}