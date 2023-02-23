all: main.o arvore.o
	@gcc main.o arvore.o -o main

main.o: main.c
	@gcc main.c -c

arvore.o: arvore.c
	@gcc arvore.c -c

run:
	@./main	