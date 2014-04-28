#include <stdio.h>
#include <string.h>

#ifndef modulo_logica_de_negocios
#define modulo_logica_de_negocios

typedef struct bloco{
    char palavra[20], dificuldade;
    char dica1[20], dica2[20], dica3[20];
} Bloco;


int verificaPalavra(char*, char*);
int contabilizaPalavra1 (int);
int contabilizaPalavra2 (int);
char* retornapalavra (Bloco);
char* retornadica (Bloco, int);
void preenchebloco_caminho (Bloco*);


#endif