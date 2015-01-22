#include "List.h"

typedef struct Node  {

    Node * prev;
    Node * next;
    int data;
};

typedef struct ListObj {

    Node * front_node;
    Node * back_node;
    Node * cursor_node;

    int cursor_index;
    int num_nodes;

}, ListObj;


// Constructors-Destructors ---------------------------------------------------

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
}

// @func - freeList
// @args - Pointer to a list to be freed
// @ret  - nothing
// @info - Cleans up all of the malloc'd data inside of the list
void freeList(List* pL) {

}


// -----------------------------------------------------------------------
// Access functions -----------------------------------------------------------
// -----------------------------------------------------------------------


// @func -
// args  -
// @ret  -
int length(List L) {
    if(L == NULL) {
        return;
    }
    return L->num_nodes;
}

// @func -
// args  -
// @ret  -
int getIndex(List L) {
    if(L == NULL) {
        return;
    }
    return L->cursor_index;
}

// @func -
// args  -
// @ret  -
int front(List L) {
    if(L == NULL || L->front_node == NULL) {
        return;
    }
    return L->front_node->data;
}

// @func -
// args  -
// @ret  -
int back(List L) {
    if(L == NULL || L->back_node == NULL) {
        return;
    }
    return L->back_node->data;
}

// @func -
// args  -
// @ret  -
int getElement(List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
int equals(List A, List B) {
    if(L == NULL) {
return;
    }
}


// -----------------------------------------------------------------------
// Manipulation procedures ----------------------------------------------------
// -----------------------------------------------------------------------

// @func -
// args  -
// @ret  -
void clear(List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void moveTo(List L, int i) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void movePrev(List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void moveNext(List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void prepend(List L, int data) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void append(List L, int data) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void insertBefore(List L, int data) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void insertAfter(List L, int data) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void deleteFront(List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void deleteBack(List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
void delete(List L) {
    if(L == NULL) {
return;
    }
}

// -----------------------------------------------------------------------
// ------------------------ Other operations -----------------------------------
// -----------------------------------------------------------------------

// @func -
// args  -
// @ret  -
void printList(FILE* out, List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  -
// @ret  -
List copyList(List L) {
    if(L == NULL) {
return;
    }
}