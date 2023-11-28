#include "../headers/analise.h"

int iniciaLista(TadAnalise *lista){
    int i;
    for(i = 0; i<94; i++){
        lista->listaDeOcorrencias[i].caractere = i+32;
        lista->listaDeOcorrencias[i].ocorrencia = 0;
    }
}

int calculaPercentual(TadAnalise *lista, int totalDeChar){
    int i;
    for(i = 0; i<94; i++){
        lista->listaDeOcorrencias[i].ocorrencia = ((lista->listaDeOcorrencias[i].ocorrencia)/(totalDeChar))*100;
    }
}

void imprimePercentual(TadAnalise lista){
    int i;
    for(i = 0; i<94; i++){
        printf("%c | %0.2f\n", lista.listaDeOcorrencias[i].caractere, lista.listaDeOcorrencias[i].ocorrencia);
    }
}