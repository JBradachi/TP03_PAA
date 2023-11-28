#include "../headers/criptografia.h"

int encriptografa(FILE *arqEntrada, FILE *arqSaida, int cifra){
    char c;
    while ((c = getc(arqEntrada)) != EOF){
        if(c == '\n'){
            fprintf(arqSaida, "%c", c);
        }
        else if(c + cifra <= 126){
            fprintf(arqSaida, "%c", (c+cifra));
        }
        else{
            fprintf(arqSaida, "%c", (c+cifra-95));
        }
    }
    
}

int manipulaArquivo(char *nomeEntrada, int cifra){
    FILE *arqEntrada, *arqSaida;
    if((arqEntrada = fopen(nomeEntrada, "r")) != NULL){
        if((arqSaida = fopen("./entradas/arquivoEncriptografado.txt", "w")) != NULL){
            encriptografa(arqEntrada, arqSaida, cifra);
        }else{
            printf("Falha na criação de arquivo");    
        }
    }else{
        printf("Falha na abertura de arquivo");
    }
}