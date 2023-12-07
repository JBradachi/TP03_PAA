#include "../headers/criptografia.h"

int encriptografa(FILE *arqEntrada, FILE *arqSaida, int cifra, int ehRandom, TadAnalise *lista){
    char c;
    int count = 0;
    printf("Arquivo encriptado: \n\n");

    // para o calculo da análise os caracteres alfabéticos foram unidospara se utilizar a tabela que o professor passou
    while ((c = getc(arqEntrada)) != EOF){
        if(c == '\n'){
            fprintf(arqSaida, "%c", c);
            printf("%c", c);
        }
        else if(c + cifra <= 126){
            fprintf(arqSaida, "%c", (c+cifra));
            printf("%c", (c+cifra));
            if(ehRandom == 1){
                if(isalpha(c)!= 0){
                    if(tolower(c) + cifra <= 122){
                        lista->listaDeOcorrencias[(tolower(c)+cifra-97)].ocorrencia+=1;
                    }else{
                        lista->listaDeOcorrencias[(tolower(c)+cifra-26-97)].ocorrencia+=1;
                    }
                    count++;
                }
                
                
            }
            
        }
        else{
            fprintf(arqSaida, "%c", (c+cifra-94));
            printf("%c", (c+cifra-94));
            if(ehRandom == 1){
                if(isalpha(c)!= 0){
                    if(tolower(c) + cifra <= 122){
                        lista->listaDeOcorrencias[(tolower(c)+cifra-97)].ocorrencia+=1;
                    }else{
                        lista->listaDeOcorrencias[(tolower(c)+cifra-26-97)].ocorrencia+=1;
                    }
                    count++;
                }
            }
        }
    }
    printf("\n");
    return count;
}

int desencriptografia(FILE *arqEncripto, FILE *arqDesencripto, int cifra){
    char c;
    while ((c = getc(arqEncripto)) != EOF){
        if(c == '\n'){
            fprintf(arqDesencripto, "%c", c);
            printf("%c", c);
        }
        else if(c - cifra >= 32){
            fprintf(arqDesencripto, "%c", (c-cifra));
            printf("%c", (c-cifra));
        }
        else{
            fprintf(arqDesencripto, "%c", (c-cifra+94));
            printf("%c", (c-cifra+94));
        }
    }
}

int manipulaArquivo(char *nomeEntrada, int cifra, int ehRandom, int Encripto){
    FILE *arqEntrada, *arqSaida;
    TadAnalise lista;
    int totalDeChar;
    char path[60];
    
    if(Encripto == 1){
        strcpy(path, "./entradas/arquivoEncriptografado.txt");
    }else{
        strcpy(path, "./entradas/arquivoDesencriptografado.txt");
    }
    iniciaLista(&lista);
    if((arqEntrada = fopen(nomeEntrada, "r")) != NULL){
        if((arqSaida = fopen(path, "w")) != NULL){
            if(Encripto == 1 && ehRandom == 1){
                totalDeChar = encriptografa(arqEntrada, arqSaida, cifra, ehRandom, &lista);
                calculaPercentual(&lista, totalDeChar);
                imprimePercentual(lista, cifra);
            }else if(Encripto == 1){
                encriptografa(arqEntrada, arqSaida, cifra, ehRandom, &lista);
            }else{
                desencriptografia(arqEntrada, arqSaida, cifra);
            }
            
        }else{
            printf("Falha na criação de arquivo");    
            fclose(arqEntrada);
            return 1;
        }
    }else{
        printf("Falha na abertura de arquivo");
        return 1;
    }
    fclose(arqEntrada);
    fclose(arqSaida);
}
