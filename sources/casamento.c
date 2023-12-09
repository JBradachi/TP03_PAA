#include "../headers/casamento.h"

void ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao){
    int ocorrencias = 0;
    printf("PESQUISA COM SHIFT AND:\n");

  if (tamanhoPadrao > tamanhoTexto) return; // Se o padrão for maior que o texto, não é possivel haver casamentos

  int MascaraDeBits[MAXASCII], R = 0; //As mascaras são utilizadas para comparar as letras no algoritmo
  for (int i = 0; i < MAXASCII; i++)       // pré - processamento
    MascaraDeBits[i] = 0; // A table ascii vai de 0 a 127. Assim, cria-se um vetor com todos esses valores

  for (int i = 1; i <= tamanhoPadrao; i++)
    /** preenche a mascara da forma estudada em sala:
     * 1 << (tamanhoPadrao - i) ===> vetor que possue um 1 coincidente com a posicao da letra atual
     * É adicionado 127 a todos os asciis (não entendi direito o porque)
     * "|=" significa que a mascara de bista recebera o resultado dela "or"  (tamanhoPadrao - i) 
     */
    MascaraDeBits[padrao[i-1]] |= 1 << (tamanhoPadrao - i);  


  for (int i = 0; i < tamanhoTexto; i++) {   
    /**
     * (1 << (tamanhoPadrao - 1)) =  10^(m-1) do algoritmo visto em sala
     */
    R = ((R >> 1) | (1 << (tamanhoPadrao - 1))) & MascaraDeBits[texto[i]];  // Essa linha representa o R' estudado em sala
    if ((R & 1) != 0){  // Se a ultima posição for 1, significa que encontrou o padrão
      if (i - tamanhoPadrao + 2 > 0){ // Marca se o padrão não é maior do que o texto restante
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

 
// pega maior valor (usado pra melhor visualização)
int maximo(int a, int b) { 
    return (a > b)? a: b; 
}
 
// preparando vetor de ocorrencias
void criaVetorOcorrencias( char *padrao, int tamanhoPadrao, int vetorOcorrencias[MAXASCII]){
    int i;
 
    // Inicia tudo com -1
    for (i = 0; i < MAXASCII; i++) vetorOcorrencias[i] = -1; 
 
    for (i = 0; i < tamanhoPadrao; i++)  vetorOcorrencias[(int) padrao[i]] = i;  
    // Para a posicao do caracter na tabela ascii, guarda onde ele ocorre pela ultima vez no padrão (ou seja, se ele não ocorre, fica -1. Dessa forma, temos todos os caracteres da tabela ascii mapeados com suas respectivas ocorrencias no padrao). 
    // Outros algoritmos usam uma estratégia muito parecida de criar um vetor do tamanho da tabela ascii. Dessa forma, é possivel acessar diretamente o valor correspondente usando seu valor ascii
}
 
// BOYER MOORE COM HEURISTICA OCRRENCIA
void BoyerMooreOcorrencia( char *texto,  char *padrao){
    printf("PESQUISA COM BOYER-MOORE, HEURISTICA OCORRENCIA\n");
    int tamanhoPadrao = strlen(padrao);
    int tamanhoTexto = strlen(texto);
    int ocorrencias = 0;
 
    int vetorOcorrencias[MAXASCII];  // Cria um vetor do tamanho da tabela ascii
 
    /* Preenche o vetor com as ocorrencias dos caracteres, para ser possivel saber quanto é necessário pular */
    criaVetorOcorrencias(padrao, tamanhoPadrao, vetorOcorrencias);
 
    int s = 0;  // s marca a posição de inicio da "janela" no texto
    while(s <= (tamanhoTexto - tamanhoPadrao))
    {
        int j = tamanhoPadrao -1 ;

        /**
         * Para cada posição no padrão e no texto, da direita para a esquerda, compara os padrões
         * nesse caso, 
         */
        while(j >= 0 && padrao[j] == texto[s+j])
            j--;
 

        // Se todo o loop for executado por completo, todos os caracteres deram match, e portanto há uma ocorrencia do padrão naquela posição 
        if (j < 0)
        {
            printf("Padrao encontrado na posicao %d\n", s);
               /**
                * se a posicao da janela mais o tamanho do texto ultrapassar o tamanho do texto, deve-se andar apenas uma posição
                * caso contrário, anda-se até que o ultimo caracter da parte que deu match no texto se alinhe com um caracter que dê match no padrão.
                * EX.:
                * "ABCACBCABCBA"
                *  ABC              => Posicao que deu match
                *     ABC           => Proxima posicao da janela
                *  
                * 
                */
            s += (s+ tamanhoPadrao < tamanhoTexto)? tamanhoPadrao-vetorOcorrencias[texto[s+tamanhoPadrao]] : 1;
            ocorrencias ++;
 
        }
 
        else // caso não dê match

               // vetorOcorrencias[texto[s + j]] pega a ultima ocorrencia do caracter que deu mismatch no texto, ou seja, na posição s + j
               // j - vetorOcorrencias[texto[s + j]] dá o número de espaços que devem ser movidos para que o caracter do texto que deu mismatch dê match com um caracter do padrao (é o tamanho menos a posição que o caracter ocorre, ou seja, quantas posições devem ser andadas para que o match ocorra)
               // caso o valor seja -1 (não há esse caracter no texto), é retornado 1, ou seja, a "janela" anda um caracter
               // RESUMO: faz o alinhamento dos caracteres, como estudado em sala
                /**
                 * EX.:
                 * "ABACCBCABCBA"
                 *  ABC
                 *    ABC
                 * 
                 */
          
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

