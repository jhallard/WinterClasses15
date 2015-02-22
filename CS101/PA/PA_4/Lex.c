// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #2                            ||                 
// ||  File    - Lex.c                                                || 
// ||  Info    - Implementation of the Lex string sorting program     ||                                             
// |===================================================================|

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <string.h>

// function pre-declarations
int readFile(char * fn, char ***);
int writeFile(char * fn, char **, List);
int getNumLines(char * fn);
int compareTo(char *, char *);
List insertionSort(char ** lines, int num_words);


// @func - main
// @args - command line arguments
// @ret  - error/success code
int main(int argc, char *argv[]) {

    /* argc should be 3 for correct execution */  
    if(argc != 3)  {
        fprintf(stderr, "Error, Proper Usage: Lex <in_fn> <out_fn>");
        exit(1);
    }

    // array of strings to be loaded from the file
    char ** word_list = NULL;

    // populate the array of strings
    int num_words = readFile(argv[1], &word_list);

    // sort the strings using a list of indices
    List sorted_list = insertionSort(word_list, num_words);

    writeFile(argv[2], word_list, sorted_list);

    int i = 0;
    for(i = 0; i <= getNumLines(argv[1]); i++) {
        free(word_list[i]);
        word_list[i] = NULL;
    }
    free(word_list);
    word_list = NULL;

    freeList(&sorted_list);

    return 0;

}

// @func - insertionSort
// @args - #1 array of strings to be sorted, #2 number of strings in this array
// @ret  - A list containing the indices of the strings in sorted order
// @info - function assumed that each word is terminated by a null terminator.
List insertionSort(char ** lines, int num_lines) {

    List ret_list = newList();
    int i = 0;

    // populate the list with line numbers
    for(i = 0; i < num_lines; i++) {
        append(ret_list, i);
    }

    // insertion sort outer loop
    for(i = 1; i < length(ret_list); i++) {

        moveTo(ret_list, i);

        char * i_string = lines[getElement(ret_list)]; // get the string to be compared from the index in the list

        // Go backwards along the list to find the correct insertion spot for the ith element
        for(moveTo(ret_list, i-1); getIndex(ret_list) >= 0 && compareTo(i_string, lines[getElement(ret_list)]) < 0; movePrev(ret_list)) {
        }

        // if we ran off the end of the list
        if(getIndex(ret_list) == -1) {
            if(compareTo(i_string, lines[front(ret_list)]) <= 0) {
                // put it at the front of the list
                prepend(ret_list, i);
                moveTo(ret_list, i+1);
                delete(ret_list);
            }
        }
        else if(getIndex(ret_list) < i-1) {
            insertAfter(ret_list, i);
            moveTo(ret_list, i+1);
            delete(ret_list);
        }
    }

    return ret_list;

}

// @func - compareTo
// @args - #1 first string, #2 second string
// @ret  - < 0 if one comes first, = 0 if they are the same, > 0 if two comes first
// @ifno - basically a wrapper to emulate the compareTo function on strings in Java
int compareTo(char * one, char * two) {
    if(one == NULL || two == NULL) {
        fprintf(stderr, "Error : Null Strings in compareTo\n");
        exit(1);
    }

    return strcmp(one, two);
}


// @func - readFile
// @args - #1 string containing the file name, #2 pointer to an array of strings to populate
// @ret  - the number of lines in the file/words in the array
int readFile(char * fn, char *** words) {
     int current_line = 0;
     const int BUFSIZE = 100;
     int num_lines = getNumLines(fn);
     *words = malloc((num_lines+1)*sizeof(char*));

     FILE *fp = fopen(fn, "r");
     if (fp == 0) {
            fprintf(stderr, "Error while opening %s", fn);
            exit(1);
     }

     (*words)[current_line] = malloc(BUFSIZE*sizeof(char));

     if((*words)[current_line] == NULL) {
        printf("malloc fail\n");
        exit(1);
     }
      while (fgets((*words)[current_line], BUFSIZE, fp)) {
            current_line++;
            (*words)[current_line] = malloc(BUFSIZE);
            if((*words)[current_line] == NULL) {
                fprintf(stderr, "malloc fail\n");
                exit(1);
            }
     } 
     fclose(fp);

     return current_line;
}


int writeFile(char * fn, char ** words, List list) {
    FILE *f = fopen(fn, "w");
    if (f == NULL) {
        printf("Error opening output file %s!\n", fn);
        exit(1);
    }

    for(moveTo(list, 0); getIndex(list) >= 0; moveNext(list)) {
        fprintf(f, "%s", words[getElement(list)]);
    }

    fclose(f);
    return 1;
}


// @func - getNumLines
// @arg  - strings containing the file name
// @ret  - the number of lines in the file
int getNumLines(char * fn) {
    int num_lines=0;
    char ch[100];
    FILE * fp = fopen(fn,"r");
      while (fgets(ch, 100, fp)) {
        num_lines++;
    } 
    fclose(fp);

    return num_lines;
}
