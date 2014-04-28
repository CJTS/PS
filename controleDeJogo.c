#include "controleDeJogo.h"

void comecajogo(){
	int pontuacao;
	printf("-------Comecou o jogo!-------\n\n\n");
    pontuacao = fase1();
    fase2(pontuacao);
}

int fase1(){

	Bloco palavra1,palavra2;
	int pontuacao1 = 0,pontuacao2 = 0,vaux;

	strcpy(palavra1.palavra, "DRACULA\0");
	strcpy(palavra1.dica1, "Transilvania\0");
	strcpy(palavra1.dica2, "Vampiro\0");
	strcpy(palavra1.dica3, "Mestre\0");

	strcpy(palavra2.palavra, "ASTECA\0");
	strcpy(palavra2.dica1, "Civilizacao\0");
	strcpy(palavra2.dica2, "America\0");
	strcpy(palavra2.dica3, "Mexico\0");
	
	printf("------------Fase 1-----------\n\n");

	for(vaux = 0; vaux < 3; vaux++){

		pontuacao1 += vezJogador1(palavra1);
		pontuacao2 += vezJogador2(palavra2);

		if(vaux == 2){
			if(pontuacao1 == pontuacao2){
				printf("Empate, rodada extra.\n" );
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

void fase2(int pontuacaoAntiga){
	
	Bloco palavra;
	int pontuacao = 0, etapa, dica;
	char opcao,chute[20];

	printf("------------Fase 2-----------\n\n");
	for(etapa = 1; etapa <= 8; etapa++){
		printf("Etapa %d :\n\n",etapa );
		strcpy(palavra.palavra, "DRACULA\0");
		strcpy(palavra.dica1, "Transilvania\0");
		strcpy(palavra.dica2, "Vampiro\0");
		strcpy(palavra.dica3, "Mestre\0");

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