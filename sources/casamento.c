#include "../headers/casamento.h"
 

 #define MAXCHAR 256

void ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao){
    int ocorrencias = 0;
    printf("PESQUISA COM SHIFT AND:\n");

  if (tamanhoPadrao > tamanhoTexto) return; // Se o padrão for maior que o texto, não é possivel haver casamentos

  int MascaraDeBits[MAXCHAR], R = 0; //As mascaras são utilizadas para comparar as letras no algoritmo
  for (int i = 0; i < MAXCHAR; i++)       // pré - processamento
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


// Prints occurrences of pat[] in txt[]
void KMP(char* padrao, char* texto)
{
    printf("PESQUISA COM KMP:\n");
    int M = strlen(padrao);
    int N = strlen(texto);
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int maiorPrefixoSufixo[M];
 
    // Preprocess the pattern (calculate lps[] array)
    calculaVetorMaiorPrefixoSufixo(padrao, M, maiorPrefixoSufixo);
    int contar = 0;
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (padrao[j] == texto[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            printf("Padrao encontrado na posicao %d\n", i - j);
            contar +=1;
            j = maiorPrefixoSufixo[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && padrao[j] != texto[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = maiorPrefixoSufixo[j - 1];
            else
                i = i + 1;
        }
    }
    printf("===============================\nAo todo ocorre um total de %d ocorrencias de '%s' no texto\n===============================\n\n", contar, padrao);
}
 
// Fills lps[] for given pattern pat[0..M-1]
void calculaVetorMaiorPrefixoSufixo(char* padrao, int M, int* maiorPrefixoSufixo)
{
    // length of the previous longest prefix suffix
    int len = 0;
 
    maiorPrefixoSufixo[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (padrao[i] == padrao[len]) {
            len++;
            maiorPrefixoSufixo[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = maiorPrefixoSufixo[len - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                maiorPrefixoSufixo[i] = 0;
                i++;
            }
        }
    }
}

/* C program for Boyer Moore Algorithm with 
   Good Suffix heuristic to find pattern in
   given text string */

// FIXME: daqui pra baixo é o BM com a heuristica do good suffix ()
 
// preprocessing for strong good suffix rule
void preprocess_strong_suffix(int *shift, int *bpos, char *pat, int m)
{
    // m is the length of pattern 
    int i=m, j=m+1;
    bpos[i]=j;
 
    while(i>0)
    {
        /*if character at position i-1 is not equivalent to
          character at j-1, then continue searching to right
          of the pattern for border */
        while(j<=m && pat[i-1] != pat[j-1])
        {
            /* the character preceding the occurrence of t in 
               pattern P is different than the mismatching character in P, 
               we stop skipping the occurrences and shift the pattern
               from i to j */
            if (shift[j]==0)
                shift[j] = j-i;
 
            //Update the position of next border 
            j = bpos[j];
        }
        /* p[i-1] matched with p[j-1], border is found.
           store the  beginning position of border */
        i--;j--;
        bpos[i] = j; 
    }
}
 
//Preprocessing for case 2
void preprocess_case2(int *shift, int *bpos, char *pat, int m)
{
    int i, j;
    j = bpos[0];
    for(i=0; i<=m; i++)
    {
        /* set the border position of the first character of the pattern
           to all indices in array shift having shift[i] = 0 */
        if(shift[i]==0)
            shift[i] = j;
 
        /* suffix becomes shorter than bpos[0], use the position of 
           next widest border as value of j */
        if (i==j)
            j = bpos[j];
    }
}
 
/*Search for a pattern in given text using
  Boyer Moore algorithm with Good suffix rule */
void search(char *text, char *pat)
{
    printf("RESOLUCAO POR BM\n");
    // s is shift of the pattern with respect to text
    int s=0, j;
    int m = strlen(pat);
    int n = strlen(text);
 
    int bpos[m+1], shift[m+1];
 
    //initialize all occurrence of shift to 0
    for(int i=0;i<m+1;i++) shift[i]=0;
 
    //do preprocessing
    preprocess_strong_suffix(shift, bpos, pat, m);
    preprocess_case2(shift, bpos, pat, m);
    int contar = 0;
 
    while(s <= n-m)
    {
 
        j = m-1;
 
        /* Keep reducing index j of pattern while characters of
             pattern and text are matching at this shift s*/
        while(j >= 0 && pat[j] == text[s+j])
            j--;
 
        /* If the pattern is present at the current shift, then index j
             will become -1 after the above loop */
        if (j<0)
        {
            printf("Padrao encontrado na posicao %d\n", s);
            contar +=1;
            s += shift[0];
        }
        else
            /*pat[i] != pat[s+j] so shift the pattern
              shift[j+1] times  */
            s += shift[j+1];
    }
    printf("===============================\nAo todo ocorre um total de %d ocorrencias de '%s' no texto\n===============================\n\n", contar, pat);
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
        searchBad(resultado, padrao);
        t = clock() - t; //tempo final - tempo inicial
        printf("Tempo de execucao: %lfms\n\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        break;
    case 3:
        t = clock(); //tempo inicial
        ShiftAnd(resultado, strlen(resultado), padrao, strlen(padrao));
        t = clock() - t; //tempo final - tempo inicial
        printf("Tempo de execucao: %lfms\n\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        break;
       
    case 4:
        t = clock(); //tempo inicial
        KMP(padrao, resultado);
        t = clock() - t; //tempo final - tempo inicial
        printf("Tempo de execucao: %lfms\n\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        break;
    default:
        break;
    }
    free(resultado);
    fclose(arqEntrada);
}

 
// A utility function to get maximum of two integers
int maximo (int a, int b) { 
    return (a > b)? a: b; 
}
 
// The preprocessing function for Boyer Moore's
// bad character heuristic
void badCharHeuristic( char *str, int size, 
                        int badchar[MAXCHAR])
{
    int i;
 
    // Inicia tudo com -1
    for (i = 0; i < MAXCHAR; i++) badchar[i] = -1; 
 
    // Fill the actual value of last occurrence 
    // of a character
    for (i = 0; i < size; i++)  badchar[(int) str[i]] = i;  
    // Para a posicao do caracter na tabela ascii, guarda onde ele ocorre pela ultima vez no padrão (ou seja, se ele não ocorre, fica -1. Dessa forma, temos todos os caracteres da tabela ascii mapeados com suas respectivas ocorrencias no padrao). 
    // Outros algoritmos usam uma estratégia muito parecida de criar um vetor do tamanho da tabela ascii. Dessa forma, é possivel acessar diretamente o valor correspondente usando seu valor ascii
}
 
/* A pattern searching function that uses Bad
   Character Heuristic of Boyer Moore Algorithm */
void searchBad( char *texto,  char *padrao){
    printf("PESQUISA COM BOYER-MOORE, HEURISTICA OCORRENCIA\n");
    int tamanhoPadrao = strlen(padrao);
    int tamanhoTexto = strlen(texto);
    int ocorrencias = 0;
 
    int vetorOcorrencias[MAXCHAR];  // Cria um vetor do tamanho da tabela ascii
 
    /* Preenche o vetor com as ocorrencias dos caracteres, para ser possivel saber quanto é necessário pular */
    badCharHeuristic(padrao, tamanhoPadrao, vetorOcorrencias);
 
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
 
            /* Shift the pattern so that the next 
               character in text aligns with the last 
               occurrence of it in pattern.
               The condition s+m < n is necessary for 
               the case when pattern occurs at the end 
               of text */
            s += (s+ tamanhoPadrao < tamanhoTexto)? tamanhoPadrao-vetorOcorrencias[texto[s+tamanhoPadrao]] : 1;
            ocorrencias ++;
 
        }
 
        else // caso não de match, 
            /* Shift the pattern so that the bad character
               in text aligns with the last occurrence of
               it in pattern. The max function is used to
               make sure that we get a positive shift. 
               We may get a negative shift if the last 
               occurrence  of bad character in pattern
               is on the right side of the current 
               character. */

               // vetorOcorrencias[texto[s + j]] pega a ultima ocorrencia do caracter que deu mismatch no texto, ou seja, na posição s + j
               // 
            s += maximo(1, j - vetorOcorrencias[texto[s+j]]);
    }
        printf("===============================\nAo todo ocorre um total de %d ocorrencias de '%s' no texto\n===============================\n\n", ocorrencias, padrao);
}
 
/* Driver program to test above function */
// int main()
// {
//     char txt[] = "ABAAABCD";
//     char pat[] = "ABC";
//     search(txt, pat);
//     return 0;
// }