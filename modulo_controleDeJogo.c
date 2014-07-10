#include "interface_controleDeJogo.h"

void comecajogo(){

	Bloco* lista = constroibloco(lista);
	int pontuacao;
	Param para;
	para.read_c = 0;
	para.time_out = 0;
	pthread_mutex_init(&para.read_c_mutex, NULL);


	printw("-------Comecou o jogo!-------\n\n");
	printw("Aperte para continuar\n");
	getch();
	clear();

    pontuacao = fase1(lista,&para);
    fase2(pontuacao,lista,&para);
    free(lista);
}

int fase1(Bloco * lista, Param * para){

	int pontuacao1 = 0,pontuacao2 = 0,vaux;
	Bloco p1;
	Bloco p2;

	printw("------------Fase 1-----------\n\n");
	printw("Aperte para continuar\n");
	getch();
	clear();
	for(vaux = 0; vaux < 3; vaux++){
		printw("------------Etapa%d-----------\n\n",vaux);
		printw("Aperte para continuar\n");
		getch();
		p1 = palavra_aleatoria(lista);
		pontuacao1 += vezJogador1(p1,para);

		p2 = palavra_aleatoria(lista);
		pontuacao2 += vezJogador2(p2,para);

		if(vaux == 2){
			if(pontuacao1 == pontuacao2){
				printw("\nEmpate, rodada extra.\n" );
				getch();
				vaux = 1;
			}
		}
	}
	printw("Pontuacao do Jogador 1: %d.\n",pontuacao1);
	printw("Pontuacao do Jogador 2: %d.\n",pontuacao2);
	getch();

	if(pontuacao1 > pontuacao2){
		printw("Jogador 1 ganhou. Parabens, voce passou para a segunda fase.\n");
		getch();
		return pontuacao1;
	}
	else{
		printw("Jogador 2 ganhou. Parabens, voce passou para a segunda fase.\n");
		getch();
		return pontuacao2;
	}
}

int vezJogador1(Bloco palavra, Param * para){
	clear();
	printw("-----------Jogador 1---------\n\n");
	printw("Aperte uma tecla para comecar\n");
	getch();
	clear();

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
	clear();
	printw("-----------Jogador 2---------\n\n");
	printw("Aperte uma tecla para comecar\n");
	getch();
	clear();


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

void fase2(int pontuacaoAntiga, Bloco * lista, Param * para){
	char opcao;
	clear();
	printw("------------Fase 2-----------\n\n");
	printw("Aperte uma tecla para comecar\n");
	getch();
	clear();

	pthread_t timer,leitor;
	para->pontuacao = pontuacaoAntiga;

	for(para->etapa = 1; para->etapa <= 8; para->etapa++){
		printw("Etapa %d :\n\n",para->etapa );
		printw("Aperte uma tecla para comecar\n");
		getch();
		clear();

		Bloco palavra = palavra_fase_2(lista,para->etapa);

		para->palavra = palavra;

		pthread_create(&timer,NULL,timer_fn,para);
		pthread_create(&leitor,NULL,leitor2_fn,para);
		pthread_join(timer,NULL);
    	if (para->read_c <= 2) {
			pthread_join(leitor,NULL);
    	}

		if(para->time_out == 1){
			printw("ACABOU O TEMPO, VOCE PERDEU\n");
			getch();
			return;
		}

		if(para->etapa != 8){
				clear();
				printw("Deseja parar de jogar e ficar com os pontos que tem?(s/n)\n>> ");
				opcao = getch();
		}

		if(opcao == 's' || opcao == 'S'){
			printw("Voce fez %d pontos. \n", para->pontuacao);
			addRank(para->pontuacao);
			return;	
		}

		if(para->etapa == 9){
			printw("PARABENS VOCE GANHOU :) !!!!!!!!!!!!!!!!!!\n");
			printw("VOCE FEZ %d PONTOS. \n", para->pontuacao);
			addRank(para->pontuacao);
			return;
		}
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
	para->off_set = 0;
	char chute[20];
	int dica;
	while(1) {
		for(dica = 1; dica < 4; dica++){
			clear();
			printw("Sua dica %d eh: %s\n",dica,retornadica(para->palavra,dica));
			printw("Seu chute:\n>> ");
			chute[para->off_set] = getch();
			while(chute[para->off_set] != '\n' && chute[para->off_set] != '\0'){
				para->off_set++;
				chute[para->off_set] = getch();
				if(chute[para->off_set] == '\n'){
					chute[para->off_set] = '\0';	
				}
			}
			para->off_set = 0;
			if(verificaPalavra(chute,retornapalavra(para->palavra)) == 0){
				printw("Você acertou parebens!!!\n");
		        para->read_c = -1;
				para->dica = contabilizaPalavra1(dica);
				printw("Você fez %d pontos\n", para->dica);
				getch();
		    	pthread_mutex_unlock(&(para->read_c_mutex));        
		    	pthread_exit(NULL);
			}	
		}
		para->dica = 0;
        para->read_c = -1;
    	pthread_mutex_unlock(&(para->read_c_mutex));        
    	pthread_exit(NULL);
	}
}

void* leitor2_fn(void* param) {
	int pontuacao = 0, etapa;
	char opcao;
	Param* para = (Param *)(param);
	para->off_set = 0;
	char chute[20];
	int dica;

	while(1) {
		for(dica = 1; dica <= 3; dica++){
			printw("Sua dica %d eh: %s\n",dica,retornadica(para->palavra,dica));
			printw("Seu chute:\n>> ");
			chute[para->off_set] = getch();
			while(chute[para->off_set] != '\n' && chute[para->off_set] != '\0'){
				para->off_set++;
				chute[para->off_set] = getch();
				if(chute[para->off_set] == '\n'){
					chute[para->off_set] = '\0';	
				}
			}
			para->off_set = 0;
			clear();
			if(verificaPalavra(chute,retornapalavra(para->palavra)) == 0){
				para->pontuacao += contabilizaPalavra2(para->etapa);
				printw("Você acertou parebens!!!\n");
				getch();
			    para->read_c = -1;
				pthread_mutex_unlock(&(para->read_c_mutex));        
				pthread_exit(NULL);
				break;
			}
		}

		if(dica == 4){
			printw("Você usou todas as suas dicas. Você perdeu :(\n");
			getch();
		    para->read_c = -1;
			pthread_mutex_unlock(&(para->read_c_mutex));        
			pthread_exit(NULL);
			break;
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
	    refresh();
	    mvprintw(0,30,"%d",para->read_c);
	    refresh();
	    move(2,3+(para->off_set));
	    refresh();
        para->read_c += 1;
        fflush(stdout);
    }
}