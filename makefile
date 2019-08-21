########## Makefile ############

all: main.o lista.o vendas.o
	gcc lista.o vendas.o main.o -o vendas -lm

main.o: main.c vendas.h lista.h
	gcc -g -c main.c
vendas.o: vendas.h vendas.c
	gcc -g -c vendas.c
lista.o: lista.h lista.c
	gcc -g -c lista.c
