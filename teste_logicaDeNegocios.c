#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h" 
#include "modulo_logicaDeNegocios.c"
/*
 * Função que adiciona ao registro do CUnit os testes paras as funções 
 * presentes no arquivo testes.c
 */
void adicionar_testes_smo_datas(void);

/*Abaixo estão as funções que efetuam os testes para a função ConstroiMalha*/
void teste_DT_VerificaPalavra_Igual(void);
void teste_DT_VerificaPalavra_Diferente(void);
void teste_DT_VerificaPalavra_CaseSensitive(void);
void teste_DT_contabilizaPalavra1_1(void);
void teste_DT_contabilizaPalavra1_2(void);
void teste_DT_contabilizaPalavra1_3(void);

/* Teste com o arquivo nulo nula */
void teste_DT_VerificaPalavra_Igual(void){
	char p[] = "Torta";
	char p1[] = "Torta";
	int resultado = verificaPalavra(p,p1);
	CU_ASSERT_TRUE(!resultado);
}

void teste_DT_VerificaPalavra_Diferente(void){
	char p[] = "Torta";
	char p1[] = "Tort";
	int resultado = verificaPalavra(p,p1);
	CU_ASSERT_TRUE(resultado);
}

void teste_DT_VerificaPalavra_CaseSensitive(void){
	char p[] = "torta";
	char p1[] = "TORTA";
	int resultado = verificaPalavra(p,p1);
	CU_ASSERT_TRUE(!resultado);
}

void teste_DT_contabilizaPalavra1_1(void){
	int valor = 1;
	int pont = contabilizaPalavra1(valor);

	CU_ASSERT(pont == 2);
}

void teste_DT_contabilizaPalavra1_2(void){
	int valor = 2;
	int pont = contabilizaPalavra1(valor);

	CU_ASSERT(pont == 1);
}

void teste_DT_contabilizaPalavra1_3(void){
	int valor = 3;
	int pont = contabilizaPalavra1(valor);

	CU_ASSERT(pont == 0);
}



void  adicionar_testes_smo_datas(void){
	CU_pSuite suite;
	
	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes da smo_datas",NULL,NULL);
	
	
	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, teste_DT_VerificaPalavra_Igual);
	CU_ADD_TEST(suite, teste_DT_VerificaPalavra_Diferente);
	CU_ADD_TEST(suite, teste_DT_VerificaPalavra_CaseSensitive);
	CU_ADD_TEST(suite, teste_DT_contabilizaPalavra1_1);
	CU_ADD_TEST(suite, teste_DT_contabilizaPalavra1_2);
	CU_ADD_TEST(suite, teste_DT_contabilizaPalavra1_3);

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