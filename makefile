all:  megasenha test limpa

test: logicaDeNegocios.c teste.c
	gcc -I./CUnit -L./CUnit teste.c -lcunit -o teste
	./teste

megasenha: main.o interface.o controleDeJogo.o logicaDeNegocios.o
	gcc main.o interface.o controleDeJogo.o logicaDeNegocios.o -o megasenha
	./megasenha.exe

main.o: main.c interface.c interface.h
	gcc -c main.c

interface.o: interface.c interface.h
	gcc -c interface.c

controleDeJogo.o: controleDeJogo.c controleDeJogo.h
	gcc -c controleDeJogo.c

logicaDeNegocios.o: logicaDeNegocios.c logicaDeNegocios.h
	gcc -c logicaDeNegocios.c

limpa: 
	rm *.o
