all: megasenha limpa

megasenha: main.o interface.o
	gcc main.o interface.o -o megasenha.exe
	./megasenha.exe

main.o: main.c interface.c interface.h
	gcc -c main.c

interface.o: interface.c interface.h
	gcc -c interface.c

limpa: 
	rm *.o
