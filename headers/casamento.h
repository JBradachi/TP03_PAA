#include "criptografia.h"

void computeLPSArray(char* pat, int M, int* lps);
void KMPSearch(char* pat, char* txt);
void preprocess_case2(int *shift, int *bpos, char *pat, int m);
void preprocess_strong_suffix(int *shift, int *bpos, char *pat, int m);
int manipulaCasamentos(char *nomeEntrada, char *padrao);
int forcaBruta(char *resultado, char *padrao);