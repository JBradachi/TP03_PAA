#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int encriptografa(FILE *arqEntrada, FILE *arqSaida, int cifra,  int ehRandom);
int manipulaArquivo(char *nomeEntrada, int cifra, int ehRandom, int Encripto);
int desencriptografia(FILE *arqEncripto, FILE *arqDesencripto, int cifra);