#include "controleDeJogo.h"

void comecajogo(){
	printf("-------Comecou o jogo!-------\n\n\n");
    fase1();
}

void fase1(){

	Bloco palavra1,palavra2;
	int pontuacao1 = 0,pontuacao2 = 0,vaux;

	strcpy(palavra1.palavra, "Dracula\0");
	strcpy(palavra1.dica1, "Transilvania\0");
	strcpy(palavra1.dica2, "Vampiro\0");
	strcpy(palavra1.dica3, "Mestre\0");

	strcpy(palavra2.palavra, "Asteca\0");
	strcpy(palavra2.dica1, "Civilizacao\0");
	strcpy(palavra2.dica2, "America\0");
	strcpy(palavra2.dica3, "Mexico\0");
	
	printf("------------Fase 1-----------\n\n");

	for(vaux = 0; vaux < 3; vaux++){

		pontuacao1 += vezJogador1(palavra1);
		pontuacao2 += vezJogador2(palavra2);

		if(vaux == 2){
			if(pontuacao1 == pontuacao2){
				vaux = 1;
			}
		}
	}
	printf("Pontuacao do Jogador 1: %d.\n",pontuacao1);
	printf("Pontuacao do Jogador 2: %d.\n",pontuacao2);

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