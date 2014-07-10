#ifndef MOD_LOGICA

#define MOD_LOGICA

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct bloco{
    char palavra[20], dificuldade;
    char dica1[20], dica2[20], dica3[20];
} Bloco;

int verificaPalavra(char*, char*);

void strupr(char *p);
int contabilizaPalavra1 (int);
int contabilizaPalavra2 (int);
char* retornapalavra (Bloco);
char* retornadica (Bloco, int);

#endif