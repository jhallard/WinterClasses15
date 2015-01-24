// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #2                            ||                 
// ||  File    - Lex.c                                                || 
// ||  Info    - Implementation of the Lex string sorting program     ||                                             
// |===================================================================|

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

int readFile(char * fn, char **);

int getNumLines(char * fn);

int main(int argc, char *argv[]) {

    /* argc should be 3 for correct execution */  
    if(argc != 3)  {
        fprintf(stderr, "Error, Proper Usage: Lex <in_fn> <out_fn>");
        exit(1);
    }

    char ** word_list = NULL;
    int num_words = readFile(argv[1], word_list);
    num_words++;

    return 0;

}

int readFile(char * fn, char ** words) {
     int current_line = 0;
     int BUFSIZE = 1000;
     int num_lines = getNumLines(fn);
     words = malloc(num_lines*sizeof(char*));

     FILE *fp = fopen("input.txt", "r");
     if (fp == 0){
            fprintf(stderr, "Error while opening");
            exit(1);
     }

     words[current_line] = malloc(BUFSIZE);
      while (fgets(words[current_line], BUFSIZE, fp)) {
            current_line++;
            words[current_line] = malloc(BUFSIZE);
     } 

     return num_lines;
}

int getNumLines(char * fn) {
    int lines=0;
    char ch;
    FILE * fp=fopen(fn,"r");
    while((ch=fgetc(fp))!=EOF)
    {
        if (ch=='\n') { lines++; }
    }
    fclose(fp);

    return lines;
}
