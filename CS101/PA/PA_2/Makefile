#------------------------------------------------------------------------------
# Makefile for Stack ADT
#
#      make             makes StackTest
#      make clean       removes object files
#
#------------------------------------------------------------------------------

StackTest : ListTest.o List.o
	gcc -o ListTest ListTest.o List.o 

StackTest.o : List.h ListTest.c
	gcc -c -std=c99 -Wall ListTest.c

Stack.o : List.h List.c
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f ListTest ListTest.o List.o