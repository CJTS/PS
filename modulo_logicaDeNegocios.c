#include "interface_logicaDeNegocios.h"

/*retorna 0 caso a palavra que o usuario digitou seja a resposta e 1 caso contrário*/
/*recebe a palavra que o usuario digitou e a palavra que ele tem que acertar*/
int verificaPalavra (char* palavra, char* atual){

    if(strcmp(strupr(palavra), strupr(atual))==0)
        return 0;
    else
        return 1;
}

/*retorna a pontuação da pessoa para a fase 1*/
/*recebe o número de dicas usadas pelo usuario para acertar a palavra*/
int contabilizaPalavra1 (int dicas){
    return 3-dicas;
}

/*retorna a pontuação da pessoa para a fase 2*/
/*recebe o número da etapa o qual ele saiu do jogo. Caso ele ganhe o jogo,
recebe-se outro número qualquer (aconselha-se usar o 9)*/
int contabilizaPalavra2 (int etapa){
    if(etapa == 1)
        return 10;
    else if(etapa == 2)
        return 100;
    else if(etapa == 3)
        return 500;
    else if(etapa == 4)
        return 1000;
    else if(etapa == 5)
        return 5000;
    else if(etapa == 6)
        return 10000;
    else if(etapa == 7)
        return 500000;
    else if(etapa == 8)
        return 1000000;
}

char* retornapalavra (Bloco p){

    char* q = p.palavra;

    return q;
}

char* retornadica (Bloco p, int dica){

    char* q1 = p.dica1;
    char* q2 = p.dica2;
    char* q3 = p.dica3;

    if (dica == 1)
        return q1;
    else if (dica == 2)
        return q2;
    else
        return q3;
}