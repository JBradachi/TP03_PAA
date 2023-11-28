#include "analise.h"

int encriptografa(FILE *arqEntrada, FILE *arqSaida, int cifra,  int ehRandom, TadAnalise *lista);
int manipulaArquivo(char *nomeEntrada, int cifra, int ehRandom, int Encripto);
int desencriptografia(FILE *arqEncripto, FILE *arqDesencripto, int cifra);