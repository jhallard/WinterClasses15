// ==========================================
// Author  - John Allard
// ID      - 1437547
// CruzID  - jhallard
// Project - Programming Assignment #2
// File    - List.h
// Info    - Declaration of the List data structure interface.
// ==========================================

#ifndef LIST_H_CS101
#define LIST_H_CS101

#include <stdio.h>
#include <stdlib.h>

// typedef a ListObj ptr to be a list for convenience
typedef struct ListObj* List;


// ---------------------------------------------------------------------------
// ------------------ Constructors-Destructors -------------------------------
// ---------------------------------------------------------------------------

List newList(void);

void freeList(List* pL);


// ---------------------------------------------------------------------------
// -------------------------- Access functions -------------------------------
// ---------------------------------------------------------------------------


int length(List L);

int getIndex(List L);

int front(List L);

int back(List L);

int getElement(List L);

int equals(List A, List B);

// ------------------------------------------------------------------------------
// --------------------- Manipulation procedures --------------------------------
// ------------------------------------------------------------------------------

void clear(List L);

void moveTo(List L, int i);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int data);

void append(List L, int data);

void insertBefore(List L, int data);

void insertAfter(List L, int data);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

// --------------------------------------------------------------------------
// ------------------------ Other operations --------------------------------
// --------------------------------------------------------------------------

void printList(FILE* out, List L);

List copyList(List L);



#endif