#include "interface.h"

void iniciar(){

	int opcao = escolhe();

	switch(opcao){
			case 1:
				telaDeJogo();
			break;

			case 2:
				telaDeRank();
			break;

			case 3:
				telaDeInstrucoes();
			break;

			case 4:
				return;
			break;
	}
	
}

int escolhe(){

	int opcao;

	printf("----------Megasenha----------\n");
	printf("Escolha uma opção:\n");
	printf("-----------------------------\n");
	printf("1 - Jogar\n");
	printf("2 - Ranking\n");
	printf("3 - Como Jogar\n");
	printf("4 - Sair\n>> ");
	scanf("%d",&opcao);

	while(opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4){
		printf("Opcao inválida tentar de novo.\n>> ");
		scanf("%d",&opcao);
	}

	return opcao;
}

void telaDeJogo(){
	comecajogo();
}

void telaDeRank(){

}
void telaDeInstrucoes(){

	int opcao;

	printf("A cada rodada, cada participante devera adivinhar uma palavra, que sera selecionada aleatoriamente para ele.\n");
	printf("Ao fim de tres rodadas, o participante que tiver mais pontos, passara para a fase final.\n");
	printf("Caso haja um empate, deve ser feita uma nova rodada e assim por diante, ata que haja um desempate.\n");
	printf("Cada palavra devera tera um nível de dificuldade (facil, medio e dificil).\n");
	printf("O numero de pontos que o participante ganha em cada palavra se da pelo numero de dicas que ele nao usou, logo, P1 = 3 – D (onde D e o numero de dicas usadas).\n");
	printf("Na fase final, o participante com mais pontos tera que adivinhar 8 palavras, dada uma valendo uma pontuacao e nivel de dificuldade sendo incrementados.\n");
	printf("Assim, se o participante acerta, ele ganha os pontos relativos aquela palavra.\n");
	printf("Caso ele use todas as dicas e erre, ele perde todos os pontos e o jogo acaba.\n");
	printf("Importante lembrar também, que ao final de cada uma das etapas desta fase, o participante pode desistir e ficar com os pontos que ja ganhou ate ali.\n");
	printf("Se o participante acertar todas as fases, o jogo acaba e sua pontuacao e computada.\n");
	printf("A pontuação final do jogo e definida pelo numero de pontos na fase inicial vezes o numero de pontos adquiridos na fase final.\n");
	printf("Logo: Pf = P1 x P2. Ao fim do jogo, a pontuacao	e o nome do usuario vao para um ranking que sera acessivel a todos.\n\n\n");
	
	printf("Escolha uma opção:\n");
	printf("--------------------\n");
	printf("1 - Voltar\n");
	printf("2 - Sair\n>> ");
	scanf("%d",&opcao);

	while(opcao != 1 && opcao != 2){
		printf("Opcao inválida tentar de novo.\n>> ");
		scanf("%d",&opcao);
	}

	switch(opcao){
			case 1:
				iniciar();
			break;

			case 2:
				return;
			break;
	}
}