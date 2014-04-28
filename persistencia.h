#include <stdio.h>

typedef struct bloco{
    char palavra[20], dificuldade;
    char dica1[20], dica2[20], dica3[20];
}Bloco;

Bloco* constroibloco();
Bloco* palavra_aleatoria(Bloco *lista);
Bloco* palavra_fase_2(Bloco *lista, char dificuldade);