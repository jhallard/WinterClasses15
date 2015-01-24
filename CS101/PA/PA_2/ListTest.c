#include "List.h"

int main() {

    List l = newList();
    prepend(l,1);
    prepend(l,2);
    printf("%d", length(l));
    prepend(l,3);
    printf("%d", length(l));

    return 0;
}