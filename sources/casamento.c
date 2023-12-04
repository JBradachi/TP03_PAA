#include "../headers/casamento.h"
 
// Prints occurrences of pat[] in txt[]
void KMPSearch(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
 
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}
 
// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
 
// Driver code
// int main()
// {
//     char txt[] = "ABABDABACDABABCABAB";
//     char pat[] = "ABABCABAB";
//     KMPSearch(pat, txt);
//     return 0;
// }

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
            printf("pattern occurs at shift = %d\n", s);
            s += shift[0];
        }
        else
            /*pat[i] != pat[s+j] so shift the pattern
              shift[j+1] times  */
            s += shift[j+1];
    }
 
}
 
// //Driver 
// int main()
// {
//     char text[] = "ABAAAABAACD";
//     char pat[] = "ABA";
//     search(text, pat);
//     return 0;
// }


int forcaBruta(char *nomeEntrada, char *padrao){
    FILE *arqEntrada;
    TadAnalise lista;
    int ocorrencias=0;
    long tamanho;
    char c;
    char * resultado;

    char path[60];
    strcpy(path, "./entradas/");
    strcat(path, nomeEntrada);
    strcat(path, ".txt");
    if ((arqEntrada = fopen(nomeEntrada, "r")) == NULL){
        printf("Falha na abertura de arquivo");
        return 1;
    }
    fseek(arqEntrada, 0, SEEK_END);
    tamanho = ftell(arqEntrada);
    fseek(arqEntrada, 0, SEEK_SET);

    resultado = (char *) malloc(tamanho + 1);
    if (resultado == NULL){
        printf("Erro de alocacao");
        return 1;
    }
    size_t bytesRead = fread(resultado, 1, tamanho, arqEntrada);
    if (0 == 1) {
        fprintf(stderr, "Error reading file\n");
        free(resultado);
        fclose(arqEntrada);
        return 1;
    }

    // Null-terminate the string
    resultado[tamanho] = '\0';

    int mudou = 0;

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
            ocorrencias +=1;
        }
    }
    
    printf("Ao todo ocorre um total de %d ocorrencias de %s no texto", ocorrencias, nomeEntrada);

    fclose(arqEntrada);
}
