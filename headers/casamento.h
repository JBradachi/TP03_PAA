#include "criptografia.h"

int manipulaCasamentos(char *nomeEntrada, char *padrao);
int forcaBruta(char *resultado, char *padrao);
void ShiftAnd(char *texto, int tamanhoTexto, char *padrao, int tamanhoPadrao);
void BoyerMooreOcorrencia( char *texto,  char *padrao);
void criaVetorOcorrencias( char *padrao, int tamanhoPadrao, int vetorOcorrencias[MAXASCII]);
int maximo(int a, int b);
