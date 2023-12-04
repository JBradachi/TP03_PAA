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
    char nomeArquivoEntrada[30] = "teste copy.txt", padrao[20];
    int opcao, casamento;
    FILE* arqEntrada, arqSaida;
    int cifra, random = 0;
    clock_t t;

    
    while (1)
    {
        clear();
        printf("\nEscolha uma das opcoes abaixo: \n1 - Entrar com arquivo \n2 - Encriptografar\n3 - Descriptografar\n4 - Buscar\n5 - Sair\n>>> ");
        // ignorar o \n na leitura da entrada
        scanf(" %d%*[^\n]",&opcao);
        switch (opcao)
        {
            case 1:
                printf("Digite o nome do arquivo (sem a extensão .txt)\n>>> ");
                scanf("%s", nomeArquivoEntrada);
                strcpy(path, "./entradas/");
                strcat(path, nomeArquivoEntrada);
                strcat(path, ".txt");
                break;
            case 2:
                
                printf("Como deseja gerar a cifra?\n[ 0 ] Digitar\n[ 1 ] Geraração aleatória\n>>> ");
                scanf("%d", &random);
                
                if(random){
                    srand((unsigned)time(NULL));
                    cifra = 1+rand()%25;
                }else{
                    printf("Digite a cifra \n>>> ");
                    scanf("%d", &cifra); 
                }
                manipulaArquivo(path, cifra, random, 1);
                break;
            case 3: 

                printf("Digite o valor da cifra:\n>>> ");
                scanf("%d", &cifra);
                manipulaArquivo(path, cifra, random, 0);
                break;
            case 4: 
                printf("Digite o padrao a ser procurado (uma unica palavra):\n>>> ");
                scanf("%s", &padrao);
                printf("Qual algoritmo deseja usar:\n1 - Forca bruta\n2 - parara\n>>> ");
                scanf("%d", &casamento);
                switch (casamento)
                {
                case 1:
                    t = clock(); //tempo inicial
                    forcaBruta(path, padrao);
                    t = clock() - t; //tempo final - tempo inicial
                    printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                    break;
                
                default:
                    break;
                }
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


/*
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

    t = clock(); //tempo inicial
    manipulaArquivo(path, cifra, random, cripto);
    t = clock() - t; //tempo final - tempo inicial

    
    printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
    return 0;
}
*/