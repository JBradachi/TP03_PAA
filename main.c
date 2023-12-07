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
    char nomeArquivoEntrada[30] = "teste copy.txt", padrao[30];
    int opcao, casamento;
    FILE* arqEntrada, arqSaida;
    int cifra, random = 0;

    
    while (1)
    {
        clear();
        opcao = 0;
        strcpy(padrao, "");
        printf("\nEscolha uma das opcoes abaixo: \n1 - Entrar com arquivo \n2 - Encriptografar\n3 - Descriptografar\n4 - Buscar\n5 - Sair\n>>> ");
        // ignorar o \n na leitura da entrada
        scanf(" %d%*[^\n]",&opcao);
        switch (opcao)
        {
            case 1:
                printf("Digite o nome do arquivo (sem a extensao .txt)\n>>> ");
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
                printf("Digite o padrao a ser procurado (palavra ou frase sem paragrafo):\n>>> ");
                // scanf("%s", &padrao);
                fseek(stdin,0,SEEK_END);
                gets(padrao);
  
                manipulaCasamentos(nomeArquivoEntrada, padrao);
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