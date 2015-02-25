// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #2                            ||                 
// ||  File    - List.c                                               || 
// ||  Info    - Implementation of the List and Node data structures  ||                                             
// |===================================================================|

#include "List.h"
#include "stdio.h"
#include "stdlib.h"

// @type - NodeObj
// @info - This private struct represents a simple doubly-linked node for our doubly-linked
//         List data type. It contains pointers to the next and previous nodes in the list
//         and an integer representing the data in the node.
typedef struct NodeObj {

    struct NodeObj * prev;
    struct NodeObj * next;
    int data;
} NodeObj;

// Simplify the syntax for myself.
typedef struct NodeObj Node;

// @type - ListObj
// @info - The main doubly-linked list for the Lex program and future programs.
//         Consists of pointers to the front and back nodes, as well as a pointer
//         that acts as a cursor, letting the user iterate over the nodes in the list.
typedef struct ListObj {

    Node * front_node;
    Node * back_node;
    Node * cursor_node;

    int cursor_index;
    int num_nodes;

} ListObj;

// -----------------------------------------------------------------------
// ------------------ Constructors-Destructors ---------------------------
// -----------------------------------------------------------------------

// @func - newList
// @args - ?? Why does this take a void arg ??
// @ret  - Returns a newly allocated list struct.
List newList(void) {
    List new_list = malloc(sizeof(ListObj));
    new_list->front_node = NULL;
    new_list->back_node = NULL;
    new_list->cursor_node = NULL;
    new_list->num_nodes = 0;
    new_list->cursor_index = -1;
    return new_list;
}

// @func - freeList
// @args - Pointer to a list to be freed
// @ret  - nothing
// @info - Cleans up all of the malloc'd data inside of the list
void freeList(List* pL) {
    if(pL == NULL || *pL == NULL) {
        fprintf(stderr, "Error : Null List in freeList() \n");
        exit(1);
    }
    clear(*pL);
    free(*pL);
    *pL = NULL;
}


// -----------------------------------------------------------------------
// -------------------------- Access functions ---------------------------
// -----------------------------------------------------------------------


// @func - length
// @args - List to be queried
// @ret  - the length of the list (if non-NULL)
int length(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List in length() \n");
        exit(1);
    }
    return L->num_nodes;
}

// @func - getIndex
// @args - List to be queried
// @ret  - the index that the cursor points to in this list
int getIndex(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List in getIndex() \n");
        exit(1);
    }
    return L->cursor_index;
}

// @func - front
// @args - '''
// @ret  - The value of the data inside of the front node
// @info - Pre : List must not be empty
int front(List L) {
    if(L == NULL || L->front_node == NULL) {
        fprintf(stderr, "Error : Null List in front() \n");
        exit(1);
    }
    if(L->front_node == NULL) {
        fprintf(stderr, "Error : Empty List in front() \n");
        exit(1);
    }
    return L->front_node->data;
}

// @func - back
// @args - '''
// @ret  - The value of the data inside of the back node
// @info - Pre : List must not be empty
int back(List L) {
    if(L == NULL || L->back_node == NULL) {
        fprintf(stderr, "Error : Null List in back() \n");
        exit(1);
    }
    if(L->back_node == NULL) {
        fprintf(stderr, "Error : Empty List in back() \n");
        exit(1);
    }
    return L->back_node->data;
}

// @func - getElement
// @args - The list to eb queried
// @ret  - The data that the cursor points to
// @info - Pre : Cursor must be defined, length > 0
int getElement(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List \n");
        exit(1);
    }
    // precondition assertion
    if(L->cursor_node == NULL || L->cursor_index == -1) {
        fprintf(stderr, "Error : Invalid Cursor Index getElement() \n");
        exit(1);
    }

    return L->cursor_node->data;
}

// @func - equals
// @args - #1 First list to be compared, #2 Second list to be compared for equality
// @ret  - 1 if true, 0 if false
int equals(List A, List B) {
    if(A == NULL || B == NULL) {
        fprintf(stderr, "Error : Null List/Invalid cursor \n");
        exit(1);
    }

    int saved_index1 = A->cursor_index;
    int saved_index2 = B->cursor_index;

    // two lists must be the same length to be the same
    if(A->num_nodes != B->num_nodes)
        return 0;

    for(int i = 0; i < A->num_nodes; i++) {
        moveTo(A, i);
        moveTo(B, i);

        if(A->cursor_node == NULL || A->cursor_node->data != B->cursor_node->data)
            return 0;
    }

    moveTo(A, saved_index1);
    moveTo(B, saved_index2);
    return 1;
}


// --------------------------------------------------------------------------
// --------------------- Manipulation procedures ----------------------------
// --------------------------------------------------------------------------

// @func - clear
// @args - The list to be queried
// @ret  - nothing
void clear(List L) {
    if(L == NULL) {
        return;
    }
    Node * walker = L->front_node;
    while(L->front_node != NULL) {
        walker = L->front_node;
        L->front_node = L->front_node->next;
        free(walker);
        walker = NULL;
        L->num_nodes--;
    }

}

// @func - moveTo
// @args - #1 The list to be queried, #2 the index to move the cursor to
// @ret  - nothing
// @info - 0 <= i < L.length() else index gets set to -1
void moveTo(List L, int i) {
    if(L == NULL) {
        fprintf(stderr, "List null in moveTo");
        exit(1);
    }
    if(i < 0 || i > L->num_nodes-1)  {// pre-condition assertion
        L->cursor_index = -1;
        L->cursor_node = NULL;
        return;
    }

    if(i == L->num_nodes-1) {
        L->cursor_node = L->back_node;
        L->cursor_index = L->num_nodes-1;
        return;
    }

    if(L->cursor_index == -1) {
        if(i < L->num_nodes/2) {
            L->cursor_index = 0;
            L->cursor_node = L->front_node;
        }
        else {
            L->cursor_index = L->num_nodes-1;
            L->cursor_node = L->back_node;
        }
    }

    int diff = i - L->cursor_index;

    if(diff == 0) {
        return;
    }
    else if(diff > 0) { // we need to move forward
        while(L->cursor_index != i && L->cursor_node != NULL) {
            L->cursor_node = L->cursor_node->next;
            L->cursor_index++;
        }
        return;
    }
    else {
        while(L->cursor_index != i && L->cursor_node != NULL) {
            L->cursor_node = L->cursor_node->prev;
            L->cursor_index--;
        }
        return;
    }
}


// @func - movePrev
// @args - The list to be queried
// @ret  - nothing
// @info - cursor_index >= 1, cursor_index < L.length for move to work, otherwise we leave
//         the cursor undefined.
void movePrev(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List in movePRev \n");
        exit(1);
    }

    // assert that the cursor is in a valid place
    if(L->cursor_index < 1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;

        // if it's invalid
        return;
    }
    L->cursor_index--;
    L->cursor_node = L->cursor_node->prev;
}

// @func - moveNext
// @args - The list to be queried
// @ret  - nothing
// @info - cursor_index >= 0, cursor_index < L.length - 1 for this to work, other we leave/make
//         the cursor undefined.
void moveNext(List L) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index >= L->num_nodes-1 || L->cursor_index == -1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        return;
    }

    L->cursor_node = L->cursor_node->next;
    L->cursor_index++;
}

// @func - prepend
// @args - #1 The list to be queried, #2 the data to prepend to the list
// @ret  - nothing
void prepend(List L, int data) {
    if(L == NULL) {
        return;
    }

    // allocate a new node
    Node * new_node = malloc(sizeof(Node));
    new_node->data = data;

    // special case, if the list is empty we have to set the back node to also point to this new node
    if(L->num_nodes == 0 || L->front_node == NULL) {
        L->front_node = new_node;
        L->back_node = new_node;
        L->num_nodes++;
        return;
    }
    L->front_node->prev = new_node;
    L->front_node->prev->next = L->front_node;
    L->front_node = new_node;
    if(L->cursor_index != -1) {
        L->cursor_index++;
    }
    L->num_nodes++;
}

// @func - append
// @args - #1 The list to be queried, #2 the data to append to the list
// @ret  - nothing
void append(List L, int data) {
    if(L == NULL) {
        return;
    }

    // allocate a new node
    Node * new_node = malloc(sizeof(Node));
    new_node->data = data;

    if(L->num_nodes == 0) {
        L->front_node = new_node;
        L->back_node = new_node;
        L->num_nodes++;
        return;
    }
    new_node->prev = L->back_node;
    L->back_node->next = new_node;
    L->back_node = new_node;
    L->num_nodes++;
}

// @func - insertBefore
// @args - #1 The list to be queried, #2 the data to be inserted before the cursor
// @ret  - nothing
// @info - Precondition - Cursor must be at a valid index (x >= 1 && x < L.length)
void insertBefore(List L, int data) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index < 0 || L->num_nodes < 1 ) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Error : Cursor index is NULL\n");
        exit(1);
    }

    // allocate a new node
    Node * new_node = malloc(sizeof(Node));
    new_node->data = data;

    if(L->cursor_node->prev != NULL) {
        L->cursor_node->prev->next = new_node;
    }
    new_node->prev = L->cursor_node->prev;
    L->cursor_node->prev = new_node;
    new_node->next = L->cursor_node;
    if(L->cursor_index != -1) {
        L->cursor_index++;
    }

    if(L->front_node == L->cursor_node) {
        L->front_node = L->cursor_node->prev;
    }
    L->num_nodes++;
}

// @func - insertAfter
// @args - #1 The list to be queried, #2 the data to be inserted after the cursor
// @ret  - nothing
// @info - Precondition - Cursor must be at a valid index (x >= 0 && x < L.length-1
void insertAfter(List L, int data) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index < 0 || L->num_nodes < 1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Error : Invalid index to insert after\n");
        exit(1);
    }

    // allocate a new node
    Node * new_node = malloc(sizeof(Node));
    new_node->data = data;

    if(L->cursor_node->next != NULL) {
        L->cursor_node->next->prev = new_node;
    }
    new_node->next = L->cursor_node->next;
    L->cursor_node->next = new_node;
    new_node->prev = L->cursor_node;

    if(L->back_node == L->cursor_node) {
        L->back_node = L->cursor_node->next;
    }

    L->num_nodes++;
}

// @func - deleteFront
// @args - The list to be queried
// @ret  - nothing
// @info - Pre : length > 0 and list not null
void deleteFront(List L) {
    if(L == NULL) {
        return;
    }
    if(L->num_nodes < 1 || L->front_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Front node is NULL/ length = 0");
    }

    Node * to_delete = L->front_node;
    if(L->front_node != NULL) {
      L->front_node = L->front_node->next;
    }
    L->front_node->prev = NULL;
    L->num_nodes--;
    free(to_delete);
    to_delete = NULL;
}

// @func - deleteBack
// @args - The list to be queried
// @ret  - nothing
// @info - Pre : Length > 0 and list not null
void deleteBack(List L) {
    if(L == NULL) {
        return;
    }
    if(L->num_nodes < 1 || L->back_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Back node is NULL/ length = 0");
    }

    Node * to_delete = L->back_node;
    L->back_node = L->back_node->prev;
    L->back_node->next = NULL;
    L->num_nodes--;
    free(to_delete);
    to_delete = NULL;
}

// @func - delete
// @args - The list to be queried
// @ret  - nothing
void delete(List L) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index < 0 || L->cursor_node == NULL || L->num_nodes == 0) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Error : Cannot delete NULL cursor\n");
        exit(1);
    }

    if(L->cursor_node->next != NULL)
        L->cursor_node->next->prev = L->cursor_node->prev;
    if(L->cursor_node->prev != NULL) 
        L->cursor_node->prev->next = L->cursor_node->next;

    // reset the cursor position
    Node * to_delete = L->cursor_node;
    free(to_delete);
    to_delete = NULL;
    L->cursor_node = NULL;
    L->cursor_index = -1;
    L->num_nodes--;
}

// -------------------------------------------------------------------------
// ------------------------ Other operations -------------------------------
// -------------------------------------------------------------------------

// @func - printList
// @args - #1 output stream, #2 The list to be queried
// @ret  - nothing
void printList(FILE* out, List L) {
    if(L == NULL || out == NULL) {
        return;
    }
    Node * walker = L->front_node;

    while(walker != NULL) {
        int x = walker->data;
        fprintf(out, "%d ", x);
        walker = walker->next;
    }
}

// @func - copyList
// @args - The list to be copied
// @ret  - copy of the list
List copyList(List L) {
    if(L == NULL) {
        printf("List null in copyList\n");
        exit(1);
    }
    Node * walker = L->front_node;
    List ret_list = newList();
    while(walker != NULL) {
        append(ret_list, walker->data);
        walker = walker->next;
    }
    return ret_list;
}



// @func - sortList
// @args - the list to be sorted
// @ret  - nothing
// @info - sorts the list in ascending order
void insertSorted(List L, int val) {

  for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)) {
    if(getElement(L) > val) {
      insertBefore(L, val);
      return;
    }
  }

  append(L, val);

}
