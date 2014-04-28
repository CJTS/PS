#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interface_logicaDeNegocios.h"

Bloco* constroibloco(Bloco *lista);
Bloco palavra_aleatoria(Bloco *lista);
Bloco palavra_fase_2(Bloco *lista, int etapa);
void adiciona_palavra(Bloco *lista, Bloco palavra);
void exclui_palavra(Bloco *lista, char *palavra);