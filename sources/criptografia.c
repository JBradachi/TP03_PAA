#include "../headers/criptografia.h"

int encriptografa(FILE *arqEntrada, FILE *arqSaida, int cifra, int ehRandom){
    char c;
    int count = 0;
    printf("Arquivo encriptado: \n");
    while ((c = getc(arqEntrada)) != EOF){
        if(c == '\n'){
            fprintf(arqSaida, "%c", c);
            printf("%c", c);
        }
        else if(c + cifra <= 126){
            fprintf(arqSaida, "%c", (c+cifra));
            printf("%c", (c+cifra));
            if(ehRandom){
                count++;
            }
            
        }
        else{
            fprintf(arqSaida, "%c", (c+cifra-95));
            printf("%c", (c+cifra-95));
            if(ehRandom){
                count++;
            }
        }
    }
    printf("\n");
    
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
    if((arqEntrada = fopen(nomeEntrada, "r")) != NULL){
        if((arqSaida = fopen("./entradas/arquivoEncriptografado.txt", "w")) != NULL){
            if(Encripto){
                encriptografa(arqEntrada, arqSaida, cifra, ehRandom);
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