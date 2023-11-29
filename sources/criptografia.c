#include "../headers/criptografia.h"

int encriptografa(FILE *arqEntrada, FILE *arqSaida, int cifra, int ehRandom, TadAnalise *lista){
    char c;
    int count = 0;
    printf("Arquivo encriptado: \n");
    printf("cifra usada = %d ", cifra);

    // para o calculo da análise os caracteres alfabéticos foram unidospara se utilizar a tabela que o professor passou
    while ((c = getc(arqEntrada)) != EOF){
        if(c == '\n'){
            fprintf(arqSaida, "%c", c);
            printf("%c", c);
        }
        else if(c + cifra <= 126){
            fprintf(arqSaida, "%c", (c+cifra));
            printf("%c", (c+cifra));
            if(ehRandom){
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
            if(ehRandom){
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
            fprintf(arqDesencripto, "%c", (c-cifra+95));
            printf("%c", (c-cifra+95));
        }
    }
}

int manipulaArquivo(char *nomeEntrada, int cifra, int ehRandom, int Encripto){
    FILE *arqEntrada, *arqSaida;
    TadAnalise lista;
    int totalDeChar;
    iniciaLista(&lista);
    if((arqEntrada = fopen(nomeEntrada, "r")) != NULL){
        if((arqSaida = fopen("./entradas/arquivoEncriptografado.txt", "w")) != NULL){
            if(Encripto){
                totalDeChar = encriptografa(arqEntrada, arqSaida, cifra, ehRandom, &lista);
                calculaPercentual(&lista, totalDeChar);
                imprimePercentual(lista);
            }else{
                desencriptografia(arqEntrada, arqSaida, cifra);
            }
            
        }else{
            printf("Falha na criação de arquivo");    
        }
    }else{
        printf("Falha na abertura de arquivo");
    }
}
