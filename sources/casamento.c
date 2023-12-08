#include "../headers/casamento.h"

void ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao){
    int ocorrencias = 0;
    printf("PESQUISA COM SHIFT AND:\n");

  if (tamanhoPadrao > tamanhoTexto) return; 

  int MascaraDeBits[MAXASCII], R = 0;
  for (int i = 0; i < MAXASCII; i++)       
    MascaraDeBits[i] = 0; 

  for (int i = 1; i <= tamanhoPadrao; i++)
    MascaraDeBits[padrao[i-1]] |= 1 << (tamanhoPadrao - i);  


  for (int i = 0; i < tamanhoTexto; i++) {   
    R = ((R >> 1) | (1 << (tamanhoPadrao - 1))) & MascaraDeBits[texto[i]];  
    if ((R & 1) != 0){  
      if (i - tamanhoPadrao + 2 > 0){ 
        printf( "Padrao encontrado na posicao %d\n", i - tamanhoPadrao + 1);
        ocorrencias ++;
      }
    }
  }
    printf("===============================\nAo todo ocorre um total de %d ocorrencias de '%s' no texto\n===============================\n\n", ocorrencias, padrao);
}

int forcaBruta(char *resultado, char *padrao){
    int mudou = 0, ocorrencias = 0;
    printf("PESQUISA COM FORCA BRUTA\n");

    for (long i = 0; i < strlen(resultado) - strlen(padrao) + 1; i++)
    {   
        mudou = 0;
        for (int j = 0; j < strlen(padrao); j++){
            if (padrao[j] != resultado[i + j]){
                mudou = 1;
                break;
            }
        }
        if (mudou == 0){
            printf("Padrao encontrado na posicao %d\n", i);
            ocorrencias +=1;
        }
    }
    
    printf("===============================\nAo todo ocorre um total de %d ocorrencias de '%s' no texto\n===============================\n\n", ocorrencias, padrao);
    return 0;
}

 
int maximo(int a, int b) { 
    return (a > b)? a: b; 
}
 
void criaVetorOcorrencias( char *padrao, int tamanhoPadrao, int vetorOcorrencias[MAXASCII]){
    int i;
 
    for (i = 0; i < MAXASCII; i++) vetorOcorrencias[i] = -1; 
 
    for (i = 0; i < tamanhoPadrao; i++)  vetorOcorrencias[(int) padrao[i]] = i;  
}
 
void BoyerMooreOcorrencia( char *texto,  char *padrao){
    printf("PESQUISA COM BOYER-MOORE, HEURISTICA OCORRENCIA\n");
    int tamanhoPadrao = strlen(padrao);
    int tamanhoTexto = strlen(texto);
    int ocorrencias = 0;
 
    int vetorOcorrencias[MAXASCII];  
 
    criaVetorOcorrencias(padrao, tamanhoPadrao, vetorOcorrencias);
 
    int s = 0; 
    while(s <= (tamanhoTexto - tamanhoPadrao))
    {
        int j = tamanhoPadrao -1 ;

        while(j >= 0 && padrao[j] == texto[s+j])
            j--;
 
        if (j < 0)
        {
            printf("Padrao encontrado na posicao %d\n", s);

            s += (s+ tamanhoPadrao < tamanhoTexto)? tamanhoPadrao-vetorOcorrencias[texto[s+tamanhoPadrao]] : 1;
            ocorrencias ++;
 
        }
 
        else 
          
            s += maximo(1, j - vetorOcorrencias[texto[s+j]]);
    }
        printf("===============================\nAo todo ocorre um total de %d ocorrencias de '%s' no texto\n===============================\n\n", ocorrencias, padrao);
}

int manipulaCasamentos(char *nomeEntrada, char *padrao){
    FILE *arqEntrada;
    TadAnalise lista;
    int ocorrencias=0, algoritmo;
    size_t tamanho;
    char c;
    clock_t t;


    char path[60];
    strcpy(path, "./entradas/");
    strcat(path, nomeEntrada);
    strcat(path, ".txt");
    if ((arqEntrada = fopen(path, "r")) == NULL){
        printf("Falha na abertura de arquivo");
        return 1;
    }
    fseek(arqEntrada, 0, SEEK_END);
    tamanho = ftell(arqEntrada);
    fseek(arqEntrada, 0, SEEK_SET);
    char *resultado = (char *)malloc(sizeof(char) * (tamanho + 10));
    if (resultado == NULL){
        printf("Erro de alocacao");
        return 1;
    }

    int i = 0;
    while ((c = fgetc(arqEntrada)) != EOF)
    {
        resultado[i] = c;
        i++;
    }
    resultado[i] = '\0';

    printf("Qual algoritmo deseja usar:\n1 - Forca bruta\n2 - Boyer Moore, heuristica ocorrencia\n3 - ShiftAnd\n>>> ");
    scanf("%d", &algoritmo);

    switch (algoritmo)
    {
    case 1:
        t = clock(); //tempo inicial
        forcaBruta(resultado, padrao);
        t = clock() - t; //tempo final - tempo inicial
        printf("Tempo de execucao: %lfms\n\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        break;
    
    case 2:
        t = clock(); //tempo inicial
        BoyerMooreOcorrencia(resultado, padrao);
        t = clock() - t; //tempo final - tempo inicial
        printf("Tempo de execucao: %lfms\n\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        break;
    case 3:
        t = clock(); //tempo inicial
        ShiftAnd(resultado, strlen(resultado), padrao, strlen(padrao));
        t = clock() - t; //tempo final - tempo inicial
        printf("Tempo de execucao: %lfms\n\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        break;
    default:
        break;
    }
    free(resultado);
    fclose(arqEntrada);
}

