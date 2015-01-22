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


// @func - length
// args  - List to be queried
// @ret  - the length of the list (if non-NULL)
int length(List L) {
    if(L == NULL) {
        return;
    }
    return L->num_nodes;
}

// @func - getIndex
// args  - List to be queried
// @ret  - the index that the cursor points to in this list
int getIndex(List L) {
    if(L == NULL) {
        return;
    }
    return L->cursor_index;
}

// @func - front
// args  - '''
// @ret  - The value of the data inside of the front node
int front(List L) {
    if(L == NULL || L->front_node == NULL) {
        return;
    }
    return L->front_node->data;
}

// @func - back
// args  - '''
// @ret  - The value of the data inside of the back node
int back(List L) {
    if(L == NULL || L->back_node == NULL) {
        return;
    }
    return L->back_node->data;
}

// @func - getElement
// args  - The list to eb queried
// @ret  - The data that the cursor points to
int getElement(List L) {
    if(L == NULL || L->cursor_node == NULL || L->cursor_index == -1) {
        return;
    }

    return L->cursor_node->data;
}

// @func - equals
// args  - #1 First list to be compared, #2 Second list to be compared for equality
// @ret  - 1 if true, 0 if false
int equals(List A, List B) {
    if(A == NULL || B == NULL) {
        return;
    }
}


// -----------------------------------------------------------------------
// Manipulation procedures ----------------------------------------------------
// -----------------------------------------------------------------------

// @func - clear
// args  - The list to be queried
// @ret  - nothing
void clear(List L) {
    if(L == NULL) {
        return;
    }
}

// @func - moveTo
// args  - #1 The list to be queried, #2 the index to move the cursor to
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
// args  - The list to be queried
// @ret  -
void movePrev(List L) {
    if(L == NULL) {
        return;
    }

    // assert that the cursor is in a valid place
    if(L->cursor_index < 1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        return;
    }

    L->cursor_node = L->cursor_node->prev;
}

// @func -
// args  - The list to be queried
// @ret  -
void moveNext(List L) {
    if(L == NULL) {
        return;
    }
}

// @func -
// args  - The list to be queried
// @ret  -
void prepend(List L, int data) {
    if(L == NULL) {
        return;
    }
}

// @func -
// args  - The list to be queried
// @ret  -
void append(List L, int data) {
    if(L == NULL) {
        return;
    }
}

// @func -
// args  - The list to be queried
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
// args  - The list to be queried
// @ret  -
void deleteFront(List L) {
    if(L == NULL) {
        return;
    }
}

// @func -
// args  - The list to be queried
// @ret  -
void deleteBack(List L) {
    if(L == NULL) {
        return;
    }
}

// @func -
// args  - The list to be queried
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
// args  - The list to be queried
// @ret  -
void printList(FILE* out, List L) {
    if(L == NULL) {
return;
    }
}

// @func -
// args  - The list to be queried
// @ret  -
List copyList(List L) {
    if(L == NULL) {
return;
    }
}