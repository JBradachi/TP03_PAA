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

void imprimePercentual(TadAnalise lista, int cifra_usada){
    int i;
    quicksort(&lista, 0, 26);
    for(i = 0; i<26; i++){
        printf("%c | %0.2f\n", lista.listaDeOcorrencias[i].caractere, lista.listaDeOcorrencias[i].ocorrencia);
    }

    printf("Chute de cifra: %d\n", cifraChute(&lista));
    printf("Cifra usada: %d\n", cifra_usada);
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
    int diferenca[5], i,j , ocorrenciaDiferenca[5];
    char tabela[5] = "aeosr";
    for(i=0; i<5; i++){
        diferenca[i] = 0;
        ocorrenciaDiferenca[i] = 0;
    }
    for(i=0; i<5; i++){
        if ((diferenca[i] = lista->listaDeOcorrencias[i].caractere - tabela[i]) < 0){
            diferenca[i]+=26;
        }
    }

    for(i=0; i<5; i++){
        for(j = 0; j<5; j++){
            if(diferenca[i] == diferenca[j]){
                ocorrenciaDiferenca[i]++;
            }
        }
    }

    return diferenca[indexMax(ocorrenciaDiferenca)];

}

int indexMax(int *vector){
    int i, index=0;
    for(i=0; i<5;i++){
        if(vector[index]<vector[i]){
            index = i;
        }
    }
    return index;
}