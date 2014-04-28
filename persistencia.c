#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "persistencia.h"

Bloco* constroibloco(){
	Bloco *lista, *aux;
	FILE *fp;
	int n,i;

	fp = fopen("Palavras.txt", "r");

	fscanf (fp, "%d", &n);

	lista = (Bloco *) malloc(sizeof(num*sizeof(Bloco)));
	aux = lista;
	fseek(fp,2,1);

	for(i=0;i<n;i++){
		fscanf(fp,"%s",(aux+i)->palavra);
		fseek(fp,1,1);
		fscanf(fp,"%c",&((aux+i)->dificuldade));
		fseek(fp,1,1);
		fscanf(fp,"%s", (aux+i)->dica1);
		fscanf(fp,"%s", (aux+i)->dica2);
		fscanf(fp,"%s", (aux+i)->dica3);
		fseek(fp,1,1);
		aux++;
	}
	fclose(fp);

	return lista;
}

Bloco* palavra_aleatoria(Bloco *lista){
	FILE *fp;
	int n;
	time_t tempo;

	fp = fopen("Palavras.txt", "r");
	fscanf (fp, "%d", &n);

	time(&tempo);

	fclose(fp);

	return(lista+(tempo%n));
}

Bloco* palavra_fase_2(Bloco *lista, char dificuldade){

	Bloco *lista1;

	lista1 = palavra_aleatoria(lista);

	while(dificuldade != lista1->dificuldade){
		lista1 = palavra_aleatoria(lista);
	}

	return lista1;
}