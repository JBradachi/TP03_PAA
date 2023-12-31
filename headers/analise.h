#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
    #define clear() system("cls"); 
#else
    #include <unistd.h>
    #define clear() system("clear");
    #define SLEEP_MS(ms) usleep(ms * 1000)
#endif

#define MAXASCII 256

typedef struct celulaAnalise{
    char caractere;
    float ocorrencia;
}TadCelulaAnalise;

typedef struct analise{
    TadCelulaAnalise listaDeOcorrencias[26];
}TadAnalise;

int iniciaLista(TadAnalise *lista);
int calculaPercentual(TadAnalise *lista, int totalDeChar);
void imprimePercentual(TadAnalise lista, int cifra_usada);
void quicksort(TadAnalise *lista,float first,float last);
int cifraChute(TadAnalise *lista);
int indexMax(int *vector);