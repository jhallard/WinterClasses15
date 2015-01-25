#include "List.h"

int main() {

    List l = newList();
    prepend(l,1);
    prepend(l,2);
    printf("%d", length(l));
    prepend(l,3);
    printf("%d", length(l));

    int i = 0;
    for(i = 0; i < 10000; i++) {
        prepend(l, i);
    }

    for(i = 5; getIndex(l) >= 0; i+=6 ) {
        moveTo(l, i);
        delete(l);
    }

    freeList(&l);

    return 0;
}