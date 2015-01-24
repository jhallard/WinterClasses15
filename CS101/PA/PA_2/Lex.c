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

int readFile(const char * fn, const char ***);

int getNumLines(const char * fn);

int compareTo(const char *, const char *);

List insertionSort(const char ** lines, int num_words);

int main(int argc, const char *argv[]) {

    /* argc should be 3 for correct execution */  
    if(argc != 3)  {
        fprintf(stderr, "Error, Proper Usage: Lex <in_fn> <out_fn>");
        exit(1);
    }

    const char ** word_list;
    printf("%s", argv[1]);
    int num_words = readFile(argv[1], &word_list);

    List new_list = insertionSort(word_list, num_words);


    for(moveTo(new_list, 0); getIndex(new_list) >= 0; moveNext(new_list)) {
        printf("%s \n", word_list[getElement(new_list)]);
    }
    return 0;

}


List insertionSort(const char ** lines, int num_lines) {

    List ret_list = newList();
    int i = 0;
    for(i = 0; i < num_lines; i++) {
        append(ret_list, i);
    }

    for(i = 1; i < length(ret_list); i++) {

        moveTo(ret_list, i);
        char * i_string = lines[getElement(ret_list)];

        // Go backwards along the list to find the correct insertion spot for the ith element
        for(moveTo(ret_list, i-1); getIndex(ret_list) >= 0 && compareTo(i_string, lines[getElement(ret_list)]) < 0; movePrev(ret_list)) {
        }

        if(getIndex(ret_list) == -1) {
            if(compareTo(i_string, lines[front(ret_list)]) <= 0) {
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

int compareTo(const char * one, const char * two) {
    return strcmp(one, two);
}



int readFile(const char * fn, const char *** words) {
     int current_line = 0;
     int BUFSIZE = 1000;
     int num_lines = getNumLines(fn);
     *words = malloc((num_lines+1)*sizeof(char*));

     FILE *fp = fopen(fn, "r");
     if (fp == 0){
            fprintf(stderr, "Error while opening %s", fn);
            exit(1);
     }

     (*words)[current_line] = malloc(BUFSIZE);

     if((*words)[current_line] == NULL) {
        printf("malloc fail\n");
        exit(1);
     }
      while (fgets((*words)[current_line], BUFSIZE, fp)) {
            current_line++;
            (*words)[current_line] = malloc(BUFSIZE);
            if((*words)[current_line] == NULL) {
                printf("malloc fail\n");
                exit(1);
            }
     } 

     return current_line;
}

int getNumLines(const char * fn) {
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
