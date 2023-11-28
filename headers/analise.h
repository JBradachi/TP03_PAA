#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct celulaAnalise{
    char caractere;
    float ocorrencia;
}TadCelulaAnalise;

typedef struct analise{
    TadCelulaAnalise listaDeOcorrencias[94];
}TadAnalise;

int iniciaLista(TadAnalise *lista);
int calculaPercentual(TadAnalise *lista, int totalDeChar);
void imprimePercentual(TadAnalise lista);