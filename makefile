all:  megasenha limpa

teste_logicaDeNegocios: logicaDeNegocios.c teste_logicaDeNegocios.c
	gcc -I./CUnit -L./CUnit teste_logicaDeNegocios.c -lcunit -o teste
	./teste

teste_persistencia: persistencia.c teste_persistencia.c
	gcc -I./CUnit -L./CUnit teste_persistencia.c -lcunit -o teste_perci
	./teste_perci

megasenha: main.o modulo_interface.o modulo_controleDeJogo.o modulo_logicaDeNegocios.o modulo_persistencia.o
	gcc main.o modulo_interface.o modulo_controleDeJogo.o modulo_logicaDeNegocios.o modulo_persistencia.o -o megasenha

main.o: main.c
	gcc -c main.c

modulo_interface.o: modulo_interface.c interface_interface.h
	gcc -c modulo_interface.c

modulo_controleDeJogo.o: modulo_controleDeJogo.c interface_controleDeJogo.h
	gcc -c modulo_controleDeJogo.c

modulo_persistencia.o: modulo_persistencia.c interface_persistencia.h
	gcc -c modulo_persistencia.c

modulo_logicaDeNegocios.o: modulo_logicaDeNegocios.c interface_logicaDeNegocios.h
	gcc -c modulo_logicaDeNegocios.c
	
limpa: 
	rm *.o
