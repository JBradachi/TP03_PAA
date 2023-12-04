#include "./headers/casamento.h"
#include <time.h>
#include "headers/casamento.h"


void pausar(){
    printf("\n\nPressione ENTER para continuar... ");
    
    // Aguarda até que o usuário pressione Enter
    getchar();
    getchar();
}

int main(){
    char mostrarPossibilidades, mostraTempReal;
    char path[100] = "./entradas/";
    char nomeArquivoEntrada[30] = "teste copy.txt";
    int opcao;
    FILE* arqEntrada, arqSaida;
    int cifra, random = 0;
    char path[100] = "./entradas/";
    clock_t t;

    
    while (1)
    {
        clear();
        printf("\nEscolha uma das opcoes abaixo: \n 1 - Entrar com arquivo \n 2 - Encriptografar\n 3 - Descriptografar\n 5 - Sair\n>>> ");
        // ignorar o \n na leitura da entrada
        scanf(" %d%*[^\n]",&opcao);
        switch (opcao)
        {
            case 1:
                printf("Digite o nome do arquivo (sem a extensão .txt)\n>>> ");
                scanf("%s", nomeArquivoEntrada);
                strcat(path, nomeArquivoEntrada);
                strcat(path, ".txt");
                break;
            case 2:
                if(random){
                    srand((unsigned)time(NULL));
                    cifra = 1+rand()%25;
                }else{
                    printf("Digite a cifra \n>>> ");
                    scanf("%d", &cifra); 
                }
                break;
            case 3: 
                t = clock(); //tempo inicial
                manipulaArquivo(path, cifra, random, cripto);
                t = clock() - t; //tempo final - tempo inicial
                break;
            case 4:
                printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                break;
            case 5:
                exit(0);
            default:
                printf("\nERRO!! Opcao inexistente\n");
                break;
        }
       pausar();
    }

    return 0;
}