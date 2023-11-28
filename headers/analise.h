#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct celulaAnalise{
    char caractere;
    int ocorrencia;
}TadCelulaAnalise;

typedef struct analise{
    celulaAnalise listaDeOcorrencias[94];
}TadAnalise;

int iniciaLista(TadAnalise lista);
