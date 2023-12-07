#include "criptografia.h"

void calculaVetorMaiorPrefixoSufixo(char* padrao, int M, int* maiorPrefixoSufixo);
void KMP(char* pat, char* txt);
void preprocess_case2(int *shift, int *bpos, char *pat, int m);
void preprocess_strong_suffix(int *shift, int *bpos, char *pat, int m);
int manipulaCasamentos(char *nomeEntrada, char *padrao);
int forcaBruta(char *resultado, char *padrao);
void ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao);