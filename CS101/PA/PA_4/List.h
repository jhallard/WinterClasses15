// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #2                            ||                 
// ||  File    - List.h                                               || 
// ||  Info    - Declaration of the List and Node data structures     ||                                             
// |===================================================================|

#ifndef LIST_H_CS101_JOHN_A
#define LIST_H_CS101_JOHN_A

#include <stdio.h>
#include <stdlib.h>

// typedef a ListObj ptr to be a list for convenience
typedef struct ListObj* List;


// ---------------------------------------------------------------------------
// ------------------ Constructors/Destructors -------------------------------
// ---------------------------------------------------------------------------

// @func - newList
// @args - ?? Why does this take a void arg ??
// @ret  - Returns a newly allocated list struct.
List newList(void);

// @func - freeList
// @args - Pointer to a list to be freed
// @ret  - nothing
// @info - Cleans up all of the malloc'd data inside of the list
void freeList(List* pL);


// ---------------------------------------------------------------------------
// -------------------------- Access functions -------------------------------
// ---------------------------------------------------------------------------

// @func - length
// @args - List to be queried
// @ret  - the length of the list (if non-NULL)
int length(List L);

// @func - getIndex
// @args - List to be queried
// @ret  - the index that the cursor points to in this list
int getIndex(List L);

// @func - front
// @args - '''
// @ret  - The value of the data inside of the front node
// @info - Pre : List must not be empty
int front(List L);

// @func - back
// @args - '''
// @ret  - The value of the data inside of the back node
// @info - Pre : List must not be empty
int back(List L);

// @func - getElement
// @args - The list to eb queried
// @ret  - The data that the cursor points to
// @info - Pre : Cursor must be defined
int getElement(List L);

// @func - equals
// @args - #1 First list to be compared, #2 Second list to be compared for equality
// @ret  - 1 if true, 0 if false
int equals(List A, List B);

// ------------------------------------------------------------------------------
// --------------------- Manipulation procedures --------------------------------
// ------------------------------------------------------------------------------

// @func - clear
// @args - The list to be queried
// @ret  - nothing
void clear(List L);

// @func - moveTo
// @args - #1 The list to be queried, #2 the index to move the cursor to
// @ret  - nothing
// @info - 0 <= i < L.length() else index gets set to -1
void moveTo(List L, int i);

// @func - movePrev
// @args - The list to be queried
// @ret  - nothing
// @info - Pre : cursor_index >= 1, cursor_index < L.length
void movePrev(List L);

// @func - moveNext
// @args - The list to be queried
// @ret  - nothing
// @info - Pre : cursor_index >= 0, cursor_index < L.length - 1
void moveNext(List L);

// @func - prepend
// @args - #1 The list to be queried, #2 the data to prepend to the list
// @ret  - nothing
void prepend(List L, int data);

// @func - append
// @args - #1 The list to be queried, #2 the data to append to the list
// @ret  - nothing
void append(List L, int data);

// @func - insertBefore
// @args - #1 The list to be queried, #2 the data to be inserted before the cursor
// @ret  - nothing
// @info - Precondition - Cursor must be at a valid index (x >= 1 && x < L.length)
void insertBefore(List L, int data);

// @func - insertAfter
// @args - #1 The list to be queried, #2 the data to be inserted after the cursor
// @ret  - nothing
// @info - Precondition - Cursor must be at a valid index (x >= 0 && x < L.length-1
void insertAfter(List L, int data);

// @func - deleteFront
// @args - The list to be queried
// @ret  - nothing
// @info - Pre : length > 0 and list not nul
void deleteFront(List L);

// @func - deleteBack
// @args - The list to be queried
// @ret  - nothing
// @info - Pre : Length > 0 and list not null
void deleteBack(List L);

// @func - delete
// @args - The list to be queried
// @ret  - nothing
void delete(List L);

// --------------------------------------------------------------------------
// ------------------------ Other operations --------------------------------
// --------------------------------------------------------------------------

// @func - printList
// @args - #1 output stream, #2 The list to be queried
// @ret  - nothing
void printList(FILE* out, List L);

// @func - copyList
// @args - The list to be copied
// @ret  - copy of the list
List copyList(List L);



#endif
