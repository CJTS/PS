#include "interface_interface.h"

void iniciar(){

	initscr();
	
	char opcao = escolhe();
	printw("\n%c\n",opcao);
	switch(opcao){
			case '1':
				telaDeJogo();
				break;
			case '2':
				telaDeRank();
				break;
			case '3':
				telaDeInstrucoes();
				break;
			case '4':
				telaDeBD();
				break;
			case '5':
				return;
				break;
	}		
	endwin();
}

char escolhe(){

	char opcao;
	
	clear();
	printw("----------Megasenha----------\n");
	printw("Escolha uma opção:\n");
	printw("-----------------------------\n");
	printw("1 - Jogar\n");
	printw("2 - Ranking\n");
	printw("3 - Como Jogar\n");
	printw("4 - Organizar BD\n");
	printw("5 - Sair\n>> ");
	opcao = getch();

	while(opcao != '1' && opcao != '2' && opcao != '3' && opcao != '4' && opcao != '5'){
		printw("\nOpcao inválida tentar de novo.\n>> ");
		opcao = getch();
	}

	printw("\n%c\n",opcao);
	return opcao;
}

void telaDeJogo(){
	clear();
	comecajogo();
	iniciar();
}

void telaDeRank(){
	char c;
	char opcao;
	clear();
	printw("Nome Pontuacao\n");
	FILE* fp = fopen("rank.txt","r");
	 while((c = fgetc(fp)) != EOF){
	 	printw("%c", c);
	}
	fclose(fp);

	refresh();
	printw("\n\nEscolha uma opção:\n");
	printw("--------------------\n");
	printw("1 - Voltar\n");
	printw("2 - Sair\n>> ");
	opcao = getch();

	while(opcao != '1' && opcao != '2'){
		printw("\nOpcao inválida tentar de novo.\n>> ");
		opcao = getch();
	}

	switch(opcao){
			case '1':
				iniciar();
			break;

			case '2':
				return;
			break;
	}
}
void telaDeInstrucoes(){

	char opcao;

	clear();
	printw("A cada rodada, cada participante devera adivinhar uma palavra, que sera selecionada aleatoriamente para ele.\n");
	printw("Ao fim de tres rodadas, o participante que tiver mais pontos, passara para a fase final.\n");
	printw("Caso haja um empate, deve ser feita uma nova rodada e assim por diante, ata que haja um desempate.\n");
	printw("Cada palavra devera tera um nível de dificuldade (facil, medio e dificil).\n");
	printw("O numero de pontos que o participante ganha em cada palavra se da pelo numero de dicas que ele nao usou, logo, P1 = 3 – D (onde D e o numero de dicas usadas).\n");
	printw("Na fase final, o participante com mais pontos tera que adivinhar 8 palavras, dada uma valendo uma pontuacao e nivel de dificuldade sendo incrementados.\n");
	printw("Assim, se o participante acerta, ele ganha os pontos relativos aquela palavra.\n");
	refresh();
	printw("Caso ele use todas as dicas e erre, ele perde todos os pontos e o jogo acaba.\n");
	printw("Importante lembrar também, que ao final de cada uma das etapas desta fase, o participante pode desistir e ficar com os pontos que ja ganhou ate ali.\n");
	printw("Se o participante acertar todas as fases, o jogo acaba e sua pontuacao e computada.\n");
	printw("A pontuação final do jogo e definida pelo numero de pontos na fase inicial vezes o numero de pontos adquiridos na fase final.\n");
	printw("Logo: Pf = P1 x P2. Ao fim do jogo, a pontuacao	e o nome do usuario vao para um ranking que sera acessivel a todos.\n\n\n");
	
	printw("Escolha uma opção:\n");
	printw("--------------------\n");
	printw("1 - Voltar\n");
	printw("2 - Sair\n>> ");
	opcao = getch();

	while(opcao != '1' && opcao != '2'){
		printw("Opcao inválida tentar de novo.\n>> ");
		opcao = getch();
	}

	switch(opcao){
			case '1':
				iniciar();
			break;

			case '2':
				return;
			break;
	}
}

void telaDeBD(){
	Bloco* lista = constroibloco(lista);
	int opcao, result;
	Bloco p;

	clear();
	printw("Escolha uma opção:\n");
	printw("--------------------\n");
	printw("1 - Inserir palavra\n");
	printw("2 - Retirar palavra\n");
	printw("3 - Voltar\n");
	printw("4 - Sair\n>> ");
	opcao = getch();

	while(opcao != '1' && opcao != '2' && opcao != '3' && opcao != '4'){
		printw("Opcao inválida tentar de novo.\n>> ");
		opcao = getch();
	}

	switch(opcao){
			case '1':
				printw("\nPalavra\n>>");
				getstr(p.palavra);
				printw("\nDificuldade\n>>");
				p.dificuldade = getch(); 
				printw("\nDica1\n>>");
				getstr(p.dica1);
				printw("\nDica2\n>>");
				getstr(p.dica2);
				printw("\nDica3\n>>");
				getstr(p.dica3);
				adiciona_palavra(lista, p);
			break;

			case '2':
				printw("\nPalavra\n>>");
				getstr(p.palavra);
				result = exclui_palavra(lista, p.palavra);
				if(result == 1 )
					printw("\nPalavra removida com sucesso!\n");
				else
					printw("\nPalavra nao encontrada. Exclusao invalida.\n");
			break;

			case '3':
				iniciar();
			break;

			case '4':
				return;
			break;
	}

	iniciar();

}