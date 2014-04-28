#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h" 
#include "modulo_persistencia.c"
/*
 * Função que adiciona ao registro do CUnit os testes paras as funções 
 * presentes no arquivo testes.c
 */
void adicionar_testes_smo_datas(void);

/*Abaixo estão as funções que efetuam os testes para a função ConstroiMalha*/
void teste_DT_palavra_fase_2_Facil(void);
void teste_DT_palavra_fase_2_Medio(void);
void teste_DT_palavra_fase_2_Dificl(void);

/* Teste com o arquivo nulo nula */
void teste_DT_palavra_fase_2_Facil(void){
	Bloco* lista = constroibloco(lista);
	Bloco *p = palavra_fase_2(lista,1);
	Bloco *p1 = palavra_fase_2(lista,2);
	Bloco *p2 = palavra_fase_2(lista,3);

	CU_ASSERT(p->dificuldade == 'F' && p1->dificuldade == 'F' && p2->dificuldade == 'F');
}

void teste_DT_palavra_fase_2_Medio(void){
	Bloco* lista = constroibloco(lista);
	Bloco *p = palavra_fase_2(lista,4);
	Bloco *p1 = palavra_fase_2(lista,5);
	Bloco *p2 = palavra_fase_2(lista,6);

	CU_ASSERT(p->dificuldade == 'M' && p1->dificuldade == 'M' && p2->dificuldade == 'M');
}

void teste_DT_palavra_fase_2_Dificl(void){
	Bloco* lista = constroibloco(lista);
	Bloco *p = palavra_fase_2(lista,7);
	Bloco *p1 = palavra_fase_2(lista,8);

	CU_ASSERT(p->dificuldade == 'D' && p1->dificuldade == 'D');
}



void  adicionar_testes_smo_datas(void){
	CU_pSuite suite;
	
	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes da smo_datas",NULL,NULL);
	
	
	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, teste_DT_palavra_fase_2_Facil);
	CU_ADD_TEST(suite, teste_DT_palavra_fase_2_Medio);
	CU_ADD_TEST(suite, teste_DT_palavra_fase_2_Dificl);

}

int main(void){
	/*Inicializa o registro de suítes e testes do CUnit*/	
	if (CUE_SUCCESS != CU_initialize_registry())
    	return CU_get_error();
    
    /*Adiciona os testes ao registro*/ 	
   	adicionar_testes_smo_datas();
	/*Muda o modo do CUnit para o modo VERBOSE
	 O modo VERBOSE mostra algumas informacoes a
	 mais na hora da execucao*/
	CU_basic_set_mode(CU_BRM_VERBOSE);
	/*Roda os testes e mostra na tela os resultados*/
	CU_basic_run_tests();
	/*Limpa o registro*/
	CU_cleanup_registry();
	return CU_get_error();
}