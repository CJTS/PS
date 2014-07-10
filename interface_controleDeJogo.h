/*!	
*	Descrição do arquivo.
*	\author CJTS.
*	\since 09/07/14.
*	\version 1.0.
*
*/

#ifndef MOD_CONTROLE

#define MOD_CONTROLE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "interface_logicaDeNegocios.h"
#include "interface_persistencia.h"

#define SLEEP_TIME 1


/**
* Nome: Param
* Descrição: strcut responsavel pelo controle das variaveis necessarias para o uso de threads
*/
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

/*!
	Nome: comecaJogo
	Descrição: Função responsável pelo inico do jogo
*/
void comecajogo();

//! Função que contem a lógica da primeira fase do jogo
/*!
*	\param lista: lista de palavras
*	\param para: struct de controle
*	\return pontuação feita pelo jogador vencedor
*/
int fase1 (Bloco * lista, Param * para);
/**
* Nome: fase2
* Descrição: Função que contem alógica da segunda fase do jogo
*/
void fase2 (int pontuacao, Bloco * lista, Param * para);
/**
* Nome: fimJogo
* Descrição: Função responsável pelo termino do jogo
*/
void fimjogo ();
/**
* Nome: vezJogador1
* Descrição: Função responsável por controlar a vez do primeiro jogador
*/
int vezJogador1(Bloco palavra, Param * para);
/**
* Nome: vezJogador2
* Descrição: Função responsável por controlar a vez do segundo jogador
*/
int vezJogador2(Bloco palavra, Param * para);
/**
* Nome: addRank
* Descrição: Função responsável por adicionar uma jogador na tabela de rank
*/
void addRank(int pontuacao);
/**
* Nome: timer_fn
* Descrição: Função responsável pelo timer de 15s.
*/
void* timer_fn(void* arg);
/**
* Nome: leitor_fn
* Descrição: Função responsável pelo buffer de entrada da primeira fase
*/
void* leitor_fn(void* arg);
/**
* Nome: leitor2_fn
* Descrição: Função responsável pelo buffer de entrada da segunda fase
*/
void* leitor2_fn(void* arg);
#endif