#include "../headers/analise.h"

int iniciaLista(TadAnalise *lista){
    int i;
    for(i = 0; i<26; i++){
        lista->listaDeOcorrencias[i].caractere = i+97;
        lista->listaDeOcorrencias[i].ocorrencia = 0;
    }
}

int calculaPercentual(TadAnalise *lista, int totalDeChar){
    int i;
    for(i = 0; i<26; i++){
        lista->listaDeOcorrencias[i].ocorrencia = ((lista->listaDeOcorrencias[i].ocorrencia)/(totalDeChar))*100;
    }
}

void imprimePercentual(TadAnalise lista){
    int i;
    quicksort(&lista, 0, 26);
    for(i = 0; i<26; i++){
        printf("%c | %0.2f\n", lista.listaDeOcorrencias[i].caractere, lista.listaDeOcorrencias[i].ocorrencia);
    }
}

void quicksort(TadAnalise *lista,float first,float last){
    int pivot, j, i;
    TadCelulaAnalise temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;


        while(i<j){
            while(lista->listaDeOcorrencias[i].ocorrencia>=lista->listaDeOcorrencias[pivot].ocorrencia&&i<last)
                i++;
            while(lista->listaDeOcorrencias[j].ocorrencia < lista->listaDeOcorrencias[pivot].ocorrencia)
                j--;
            if(i<j){
                temp=lista->listaDeOcorrencias[i];
                lista->listaDeOcorrencias[i] = lista->listaDeOcorrencias[j];
                lista->listaDeOcorrencias[j] = temp;
            }
        }

        temp=lista->listaDeOcorrencias[pivot];
        lista->listaDeOcorrencias[pivot] = lista->listaDeOcorrencias[j];
        lista->listaDeOcorrencias[j] = temp;
        quicksort(lista,first,j-1);
        quicksort(lista,j+1,last);
        }
}

int cifraChute(TadAnalise *lista){
    
}