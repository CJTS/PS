#include "interface_controleDeJogo.h"

void comecajogo(){

	Bloco* lista = constroibloco(lista);
	int pontuacao;

	printf("-------Comecou o jogo!-------\n\n\n");
    pontuacao = fase1(lista);
    fase2(pontuacao,lista);
    free(lista);
}

int fase1(Bloco * lista){

	int pontuacao1 = 0,pontuacao2 = 0,vaux;
	Bloco p1;
	Bloco p2;
	
	printf("------------Fase 1-----------\n\n");

	for(vaux = 0; vaux < 3; vaux++){
		p1 = palavra_aleatoria(lista);
		pontuacao1 += vezJogador1(p1);

		p2 = palavra_aleatoria(lista);
		pontuacao2 += vezJogador2(p2);

		if(vaux == 2){
			if(pontuacao1 == pontuacao2){
				printf("\nEmpate, rodada extra.\n" );
				vaux = 1;
			}
		}
	}
	printf("Pontuacao do Jogador 1: %d.\n",pontuacao1);
	printf("Pontuacao do Jogador 2: %d.\n",pontuacao2);

	if(pontuacao1 > pontuacao2){
		printf("Jogador 1 ganhou. Parabens, voce passou para a segunda fase.\n");
		return pontuacao1;
	}
	else{
		printf("Jogador 2 ganhou. Parabens, voce passou para a segunda fase.\n");
		return pontuacao2;
	}

}

int vezJogador1(Bloco palavra){

	char chute[20];
	int dica;
	printf("-----------Jogador 1---------\n\n");

	for(dica = 1; dica < 4; dica++){

		printf("Sua dica %d eh: %s\n",dica,retornadica(palavra,dica));
		printf("Seu chute:\n>> ");
		scanf("%s",chute);
	
		if(verificaPalavra(chute,retornapalavra(palavra)) == 0){
			printf("Você acertou parebens!!!\n");
			return contabilizaPalavra1(dica);
		}
	}
	
	printf("Você nao adivinhou. Duhhhh. Era muito facil!!!\n");
	return 0;
}

int vezJogador2(Bloco palavra){

	char chute[20];
	int dica;
	printf("-----------Jogador 2---------\n\n");

	for(dica = 1; dica < 4; dica++){
	
		printf("Sua dica %d eh: %s\n",dica,retornadica(palavra,dica));
		printf("Seu chute:\n>> ");
		scanf("%s",chute);
	
		if(verificaPalavra(chute,retornapalavra(palavra)) == 0){
			printf("Você acertou parebens!!!\n");
			return contabilizaPalavra1(dica);
		}
	}
	
	printf("Você nao adivinhou. Duhhhh. Era muito facil!!!\n");
	return 0;
}

void fase2(int pontuacaoAntiga, Bloco * lista){
	
	int pontuacao = 0, etapa, dica;
	char opcao,chute[20];

	printf("------------Fase 2-----------\n\n");
	for(etapa = 1; etapa <= 8; etapa++){
		printf("Etapa %d :\n\n",etapa );

		Bloco palavra = palavra_fase_2(lista,etapa);

		for(dica = 1; dica <= 3; dica++){
	
			printf("Sua dica %d eh: %s\n",dica,retornadica(palavra,dica));
			printf("Seu chute:\n>> ");
			scanf("%s",chute);
		
			if(verificaPalavra(chute,retornapalavra(palavra)) == 0){
				pontuacao += contabilizaPalavra2(etapa);
				printf("Você acertou parebens!!!\n");
				break;
			}
		}

		if(dica == 4){
			printf("Você usou todas as suas dicas. Você perdeu :(\n");
			break;
		}
		if(etapa != 8){
				getchar();
				printf("Deseja parar de jogar e ficar com os pontos que tem?(s/n)\n>> ");
				scanf("%c",&opcao);
		}
		if(opcao == 's' || opcao == 'S'){
			pontuacao = pontuacao + pontuacaoAntiga;
			printf("Voce fez %d pontos. \n", pontuacao);
			addRank(pontuacao);
			break;	
		}
	}

	if(etapa == 9){
		pontuacao = pontuacao + pontuacaoAntiga;
		printf("PARABENS VOCE GANHOU :) !!!!!!!!!!!!!!!!!!\n");
		printf("VOCE FEZ %d PONTOS. \n", pontuacao);
		addRank(pontuacao);
	}
}

void addRank(int pontuacao){
	char nome[20];
	printf("Informe seu nome: (20 chars) \n>>");
	scanf("%s",nome);
	FILE* fp = fopen("rank.txt","a");
	fputs(nome, fp);
	fputc(' ', fp);
	fprintf(fp, "%d\n", pontuacao);

	fclose(fp);
}