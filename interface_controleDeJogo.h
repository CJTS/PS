#ifndef MOD_CONTROLE

#define MOD_CONTROLE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "interface_logicaDeNegocios.h"
#include "interface_persistencia.h"

#define SLEEP_TIME 1

typedef struct param{
	int read_c;
	int time_out;
	int dica;
	int off_set;
	int etapa;
	int pontuacao;
	pthread_mutex_t read_c_mutex;
	Bloco palavra;
} Param;

void comecajogo();
int fase1 (Bloco * lista, Param * para);
void fase2 (int pontuacao, Bloco * lista, Param * para);
void fimjogo ();
int vezJogador1(Bloco palavra, Param * para);
int vezJogador2(Bloco palavra, Param * para);
void addRank(int pontuacao);
void* timer_fn(void* arg);
void* leitor_fn(void* arg);
void* leitor2_fn(void* arg);
#endif