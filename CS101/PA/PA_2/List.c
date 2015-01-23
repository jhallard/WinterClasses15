// |===================================================================|
// ||  Author  - John Allard                                          ||     
// ||  ID      - 1437547                                              || 
// ||  CruzID  - jhallard                                             || 
// ||  Project - Programming Assignment #2                            ||                 
// ||  File    - List.c                                               || 
// ||  Info    - Implementation of the List and Node data structures  ||                                             
// |===================================================================|

#include "List.h"

typedef struct NodeObj {

    struct NodeObj * prev;
    struct NodeObj * next;
    int data;
} NodeObj;

typedef struct NodeObj Node;

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

}


// -----------------------------------------------------------------------
// -------------------------- Access functions ---------------------------
// -----------------------------------------------------------------------


// @func - length
// @args - List to be queried
// @ret  - the length of the list (if non-NULL)
int length(List L) {
    if(L == NULL) {
        //TODO printf stderr
        exit(1);
    }
    return L->num_nodes;
}

// @func - getIndex
// @args - List to be queried
// @ret  - the index that the cursor points to in this list
int getIndex(List L) {
    if(L == NULL) {
        //TODO printf stderr
        printf("Fail in getIndex\n");
        exit(1);
    }
    return L->cursor_index;
}

// @func - front
// @args - '''
// @ret  - The value of the data inside of the front node
int front(List L) {
    if(L == NULL || L->front_node == NULL) {
        //TODO printf stderr
        exit(1);
    }
    return L->front_node->data;
}

// @func - back
// @args - '''
// @ret  - The value of the data inside of the back node
int back(List L) {
    if(L == NULL || L->back_node == NULL) {
        //TODO printf stderr
        exit(1);
    }
    return L->back_node->data;
}

// @func - getElement
// @args - The list to eb queried
// @ret  - The data that the cursor points to
int getElement(List L) {
    if(L == NULL || L->cursor_node == NULL || L->cursor_index == -1) {
        //TODO printf stderr
        exit(1);
    }

    return L->cursor_node->data;
}

// @func - equals
// @args - #1 First list to be compared, #2 Second list to be compared for equality
// @ret  - 1 if true, 0 if false
int equals(List A, List B) {
    if(A == NULL || B == NULL) {
        //TODO printf stderr
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
        L->num_nodes--;
    }

}

// @func - moveTo
// @args - #1 The list to be queried, #2 the index to move the cursor to
// @ret  - nothing
// @info - 0 <= i < L.length() else index gets set to -1
void moveTo(List L, int i) {
    if(L == NULL) {
        return;
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
// @ret  -
void movePrev(List L) {
    if(L == NULL) {
        exit(1);
    }

    // assert that the cursor is in a valid place
    if(L->cursor_index < 1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        return;
    }
    L->cursor_index--;
    L->cursor_node = L->cursor_node->prev;
}

// @func - moveNext
// @args - The list to be queried
// @ret  -
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

// @func -
// @args - The list to be queried
// @ret  -
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
    L->front_node = L->front_node->next;
    L->front_node->prev = NULL;
    L->num_nodes--;
    free(to_delete);
    to_delete = NULL;
}

// @func -
// @args - The list to be queried
// @ret  -
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

    L->cursor_node = NULL;
    L->cursor_index = -1;
    L->num_nodes--;
}

// -------------------------------------------------------------------------
// ------------------------ Other operations -------------------------------
// -------------------------------------------------------------------------

// @func -
// @args - The list to be queried
// @ret  -
void printList(FILE* out, List L) {
    if(L == NULL) {
        return;
    }
    Node * walker = L->front_node;

    while(walker != NULL) {
        int x = walker->data;
        fprintf(out, "%d ", x);
        walker = walker->next;
    }
}

// @func -
// @args - The list to be queried
// @ret  -
List copyList(List L) {
    if(L == NULL) {
        printf("Fail in copyList\n");
        exit(1);
    }
    Node * walker = L->front_node;
    List ret_list = newList();
    while(walker != NULL) {
        printf("Walker Data %d \n", walker->data);
        append(ret_list, walker->data);
        walker = walker->next;
    }
    return ret_list;
}