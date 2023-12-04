#include "./headers/criptografia.h"
#include <time.h>


int main(){
    FILE* arqEntrada, arqSaida;
    int cifra, random, cripto;
    char nomeArquivoEntrada[40];
    char path[100] = "./entradas/";
    clock_t t;


    printf("Digite o nome do arquivo (sem a extensão .txt)\n>>> ");
    scanf("%s", nomeArquivoEntrada);
    strcat(path, nomeArquivoEntrada);
    strcat(path, ".txt");

    printf("Deseja: \n[ 0 ] desencriptografar\n[ 1 ] encriptografar\n>>> ");
    scanf("%d", &cripto);
    if(cripto){
        printf("Como deseja gerar a cifra?\n[ 0 ] Digitar\n[ 1 ] Geraração aleatória\n>>> ");
        scanf("%d", &random);
    }else{
        random = 0;
    }
    
    if(random){
        srand((unsigned)time(NULL));
        cifra = 1+rand()%25;
    }else{
        printf("Digite a cifra \n>>> ");
        scanf("%d", &cifra); 
    }

    /**
     * MEDINDO TEMPO
     * o t = clock() antes da funcao marca o inicio da execucao
     * o t = clock() - t calcula o tempo gasto
     */

    t = clock(); //tempo inicial
    manipulaArquivo(path, cifra, random, cripto);
    t = clock() - t; //tempo final - tempo inicial

    
    printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
    return 0;
}