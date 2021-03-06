#include "interface_persistencia.h"

Bloco* constroibloco(Bloco *lista){
	FILE *fp;
	int n,i;

	fp = fopen("Palavras.txt", "r");
	fscanf (fp, "%d", &n);


	lista = (Bloco *) malloc(n*sizeof(Bloco));
	fseek(fp,1,1);

	for(i = 0; i < n; i++){
		fscanf(fp,"%s",(lista+i)->palavra);
	 	fseek(fp,1,1);

	 	fscanf(fp,"%c",&((lista+i)->dificuldade));
	 	fseek(fp,1,1);

	 	fscanf(fp,"%s", (lista+i)->dica1);
	 	fseek(fp,1,1);

	 	fscanf(fp,"%s", (lista+i)->dica2);
	 	fseek(fp,1,1);

	 	fscanf(fp,"%s", (lista+i)->dica3);
	 	fseek(fp,1,1);
	}
	fclose(fp);

	return lista;
}

Bloco palavra_aleatoria(Bloco *lista){
	FILE *fp;
	int n;
	time_t tempo;

	fp = fopen("Palavras.txt", "r");
	fscanf (fp, "%d", &n);

	time(&tempo);

	fclose(fp);

	return *(lista+(tempo%n));
}

Bloco palavra_fase_2(Bloco *lista, int etapa){

	Bloco lista1;
	char dificuldade;
	int i = 1;

	if(etapa==1 || etapa==2 || etapa==3){
		dificuldade = 'F';
	}else if(etapa==4 || etapa ==5 || etapa==6){
		dificuldade = 'M';
	}else{
		dificuldade = 'D';
	}

	lista1 = palavra_aleatoria(lista);

	while(dificuldade != lista1.dificuldade){
		lista1 = palavra_aleatoria(lista+i);
		i++;
	}

	return lista1;
}

void adiciona_palavra(Bloco *lista, Bloco palavra){
	FILE *fp;
	int n;

	fp = fopen("Palavras.txt", "r+"); //Abre o arquivo de palavras

	fseek(fp,0,2); //posiciona o ponteiro do arquivo no final deste
	//A partir daqui se escrevem os dados da palavra no arquivo
	fprintf(fp, "%s ", palavra.palavra);
	fprintf(fp, "%c ", palavra.dificuldade);
	fprintf(fp, "%s ", palavra.dica1);
	fprintf(fp, "%s ", palavra.dica2);
	fprintf(fp, "%s\n", palavra.dica3);

	rewind(fp); //reposiciona o ponteiro do arquivo no início deste
	fscanf(fp,"%d",&n); //Lê a quantidade de palavras do arquivo
	n++; //incrementa a quantidade de palavras
	rewind(fp); //reposiciona o ponteiro do arquivo no início deste
	fprintf(fp, "%d", n); //grava nova quantidade de palavras no arquivo

	fclose(fp); //fechar o arquivo de palavras

	return;
}

int exclui_palavra(Bloco *lista, char *palavra){
	FILE *fp;
	int i, n, f = 0,j;
	int result;

	fp = fopen("Palavras.txt", "r"); //Abre o arquivo de palavras
	fscanf(fp,"%d",&n); //Lê a quantidade de palavras do arquivo/lista

	//O for abaixo compara 'palavra' as palavras da lista e encerra o for caso encontre uma igual, mantendo assim o índice i
	for(i=0;i<n;i++){
		result = verificaPalavra((lista+i)->palavra,palavra);

		if(result == 0){
			lista[i] = lista[n-2]; // Substitui o bloco removido pelo último bloco da lista
			n--; //Diminui em 1 o valor de n, que representa quantidade de palavras
			fclose(fp); //Fecha o arquivo no modo leitura 
			fp = fopen("Palavras.txt","w+"); //Elimina o conteúdo do arquivo e começa a reescritura
			fprintf(fp, "%d\n", n);//Insere quantidade de palavras do arquivo
			//Loop de escritura da: palavra/dificuldade/dica1/dica2/dica3 
			for(j = 0; j < n; j++){
				printw("\n%d\n",j);
				fprintf(fp, "%s %c %s %s %s\n", (lista+j)->palavra, (lista+j)->dificuldade, (lista+j)->dica1, (lista+j)->dica2, (lista+j)->dica3);
				printw("%s %c %s %s %s\n", (lista+j)->palavra, (lista+j)->dificuldade, (lista+j)->dica1, (lista+j)->dica2, (lista+j)->dica3 );
				getch();
			}
			return 1;
		}
		
	}

	//Fecha o arquivo fp
	fclose(fp);
	return 0;
}