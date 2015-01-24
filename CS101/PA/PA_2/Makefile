#------------------------------------------------------------------------------
# Makefile for Stack ADT
#
#      make             makes StackTest
#      make clean       removes object files
#
#------------------------------------------------------------------------------

ListClient : ListClient.o List.o
	gcc -o ListClient ListClient.o List.o 

ListClient.o : List.h ListClient.c
	gcc -c -std=c99 -Wall ListClient.c

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o


List.o : List.h List.c
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f ListClient ListClient.o List.o