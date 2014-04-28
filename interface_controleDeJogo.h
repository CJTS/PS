#include <stdio.h>
#include <stdlib.h>
#include "interface_logicaDeNegocios.h"
#include "interface_persistencia.h"

void comecajogo ();
int fase1 (Bloco * lista);
void fase2 (int pontuacao, Bloco * lista);
void fimjogo ();
int vezJogador1(Bloco palavra);
int vezJogador2(Bloco palavra);
void addRank(int pontuacao);