#include "interface_controleDeJogo.h"

void comecajogo(){

	Bloco* lista = constroibloco(lista);
	int pontuacao;
	Param para;
	para.read_c = 0;
	para.time_out = 0;	
	pthread_mutex_init(&para.read_c_mutex, NULL);


	printw("-------Comecou o jogo!-------\n\n\n");
    pontuacao = fase1(lista,&para);
    fase2(pontuacao,lista);
    free(lista);
}

int fase1(Bloco * lista, Param * para){

	int pontuacao1 = 0,pontuacao2 = 0,vaux;
	Bloco p1;
	Bloco p2;

	printw("------------Fase 1-----------\n\n");

	for(vaux = 0; vaux < 3; vaux++){
		p1 = palavra_aleatoria(lista);
		pontuacao1 += vezJogador1(p1,para);

		p2 = palavra_aleatoria(lista);
		pontuacao2 += vezJogador2(p2,para);

		if(vaux == 2){
			if(pontuacao1 == pontuacao2){
				printw("\nEmpate, rodada extra.\n" );
				vaux = 1;
			}
		}
	}
	printw("Pontuacao do Jogador 1: %d.\n",pontuacao1);
	printw("Pontuacao do Jogador 2: %d.\n",pontuacao2);

	if(pontuacao1 > pontuacao2){
		printw("Jogador 1 ganhou. Parabens, voce passou para a segunda fase.\n");
		return pontuacao1;
	}
	else{
		printw("Jogador 2 ganhou. Parabens, voce passou para a segunda fase.\n");
		return pontuacao2;
	}

}

int vezJogador1(Bloco palavra, Param * para){
	printw("-----------Jogador 1---------\n\n");

	para->palavra = palavra;

	pthread_t timer,leitor;
	
	pthread_create(&timer,NULL,timer_fn,para);
	pthread_create(&leitor,NULL,leitor_fn,para);

	pthread_join(timer,NULL);
    if (para->read_c <= 2) {
		pthread_join(leitor,NULL);
    }

	if(para->time_out == 1){
		printw("ACABOU O TEMPO\n");
		para->read_c = 0;
		return 0;
	}
	para->read_c = 0;
	return para->dica;
}

int vezJogador2(Bloco palavra, Param * para){
	printw("-----------Jogador 2---------\n\n");

	para->palavra = palavra;

	pthread_t timer,leitor;
	
	pthread_create(&timer,NULL,timer_fn,para);
	pthread_create(&leitor,NULL,leitor_fn,para);

	pthread_join(timer,NULL);
    if (para->read_c <= 2) {
		pthread_join(leitor,NULL);
    }

	if(para->time_out == 1){
		printw("ACABOU O TEMPO\n");
		para->read_c = 0;
		return 0;
	}
	para->read_c = 0;
	return para->dica;
}

void fase2(int pontuacaoAntiga, Bloco * lista){

	int pontuacao = 0, etapa, dica;
	char opcao,chute[20];

	printw("------------Fase 2-----------\n\n");
	for(etapa = 1; etapa <= 8; etapa++){
		printw("Etapa %d :\n\n",etapa );

		Bloco palavra = palavra_fase_2(lista,etapa);

		for(dica = 1; dica <= 3; dica++){

			printw("Sua dica %d eh: %s\n",dica,retornadica(palavra,dica));
			printw("Seu chute:\n>> ");
			getstr(chute);

			if(verificaPalavra(chute,retornapalavra(palavra)) == 0){
				pontuacao += contabilizaPalavra2(etapa);
				printw("Você acertou parebens!!!\n");
				break;
			}
		}

		if(dica == 4){
			printw("Você usou todas as suas dicas. Você perdeu :(\n");
			break;
		}
		if(etapa != 8){
				getchar();
				printw("Deseja parar de jogar e ficar com os pontos que tem?(s/n)\n>> ");
				getstr(&opcao);
		}
		if(opcao == 's' || opcao == 'S'){
			pontuacao = pontuacao + pontuacaoAntiga;
			printw("Voce fez %d pontos. \n", pontuacao);
			addRank(pontuacao);
			break;	
		}
	}

	if(etapa == 9){
		pontuacao = pontuacao + pontuacaoAntiga;
		printw("PARABENS VOCE GANHOU :) !!!!!!!!!!!!!!!!!!\n");
		printw("VOCE FEZ %d PONTOS. \n", pontuacao);
		addRank(pontuacao);
	}
}

void addRank(int pontuacao){
	char nome[20];
	printw("Informe seu nome: (20 chars) \n>>");
	getstr(nome);
	FILE* fp = fopen("rank.txt","a");
	fputs(nome, fp);
	fputc(' ', fp);
	fprintf(fp, "%d\n", pontuacao);

	fclose(fp);
}


void* leitor_fn(void* param) {
	Param* para = (Param *)(param);
	char chute[20];
	int dica;
	while(1) {
		for(dica = 1; dica < 4; dica++){

			printw("Sua dica %d eh: %s\n",dica,retornadica(para->palavra,dica));
			printw("Seu chute:\n>> ");
			getstr(chute);

			if(verificaPalavra(chute,retornapalavra(para->palavra)) == 0){
				printw("Você acertou parebens!!!\n");
		        para->read_c = -1;
				para->dica = contabilizaPalavra1(dica);
		    	pthread_mutex_unlock(&(para->read_c_mutex));        
		    	pthread_exit(NULL);
			}
		}
	}
}

void* timer_fn(void* param) {
	Param* para = (Param *)(param);
    while (1) {
        sleep(SLEEP_TIME);
        pthread_mutex_lock(&(para->read_c_mutex));
        if (para->read_c > 14) {
			para->time_out = 1;
            pthread_mutex_unlock(&(para->read_c_mutex));     
            return NULL;
        }
        else if(para->read_c == -1){
            pthread_mutex_unlock(&(para->read_c_mutex));     
            return NULL;
        }
        pthread_mutex_unlock(&(para->read_c_mutex));
        para->read_c += 1;
        fflush(stdout);
    }
}