#include <time.h>
#include "headers/casamento.h"


void pausar(){
    printf("\n\nPressione ENTER para continuar... ");
    
    // Aguarda até que o usuário pressione Enter
    getchar();
    getchar();
}

int main(){
    char mostrarPossibilidades, mostraTempReal, c;
    char path[100] = "./entradas/";
    char nomeArquivoEntrada[30] = "teste copy.txt", padrao[150];
    int opcao, casamento, i;
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
        printf("\n");
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
                i = 0;
                getchar();
                while ((c = getchar()) != '\n' && c != EOF && i < sizeof(padrao) - 1) {
                    padrao[i] = c;
                    i++;
                }
                padrao[i] = '\0'; 


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