#include <stdio.h>
#include "utils/ArrayList.h"

int main(int argc, char *argv[]) {
    ArrayList(int) ARRAYLIST(A, int) = newArrayList(sizeof(int));
    int i;
    int a = 100;
    int b[] = {1, 2, 3, 4, 5};

    printf("ArrayList A\n");
    printf("/----------------------------------/\n");
    printf("A size = %d\n", ARRAYLIST_SIZE(A));
    
    printf("/----------------------------------/\n");
    printf("A add %d\n", a);
    ARRAYLIST_ADD(A, &a);
    printf("A add array[%d, %d, %d, %d, %d]\n", b[0], b[1], b[2], b[3], b[4]);
    ARRAYLIST_ADD_ARRAY(A, b, sizeof(b)/sizeof(int), int);

    printf("A size = %d\n", ARRAYLIST_SIZE(A));
    for (i = 0; i < ARRAYLIST_SIZE(A); i++) {
        printf("A get(%d) = %d\n", i, ARRAYLIST_GET(A, i, int));
    }

    printf("/----------------------------------/\n");
    printf("A remove index %d\n", 2);
    ARRAYLIST_REMOVE(A, 2);
    printf("A size = %d\n", ARRAYLIST_SIZE(A));
    for (i = 0; i < ARRAYLIST_SIZE(A); i++) {
        printf("A get(%d) = %d\n", i, ARRAYLIST_GET(A, i, int));
    }

    printf("/----------------------------------/\n");
    printf("A remove range index [1, 2]\n");
    ARRAYLIST_REMOVE_RANGE(A, 1, 2);
    printf("A size = %d\n", ARRAYLIST_SIZE(A));
    for (i = 0; i< ARRAYLIST_SIZE(A); i++) {
        printf("A get(%d) = %d\n", i, ARRAYLIST_GET(A, i, int));
    }

    printf("/----------------------------------/\n");
    printf("A remove from index 1 to last\n");
    ARRAYLIST_REMOVE_BY_LAST(A, 1);
    printf("A size = %d\n", ARRAYLIST_SIZE(A));
    for (i = 0; i < ARRAYLIST_SIZE(A); i++) {
        printf("A get(%d) = %d\n", i, ARRAYLIST_GET(A, i, int));
    }

    printf("/----------------------------------/\n");
    printf("A insert 100 to index 0\n");
    ARRAYLIST_INSERT(A, 0, &a);
    printf("A size = %d\n", ARRAYLIST_SIZE(A));
    for (i = 0; i < ARRAYLIST_SIZE(A); i++) {
        printf("A get(%d) = %d\n", i, ARRAYLIST_GET(A, i, int));

    }

    printf("/----------------------------------/\n");
    printf("A pop\n");
    ARRAYLIST_POP(A);
    for (i = 0; i < ARRAYLIST_SIZE(A); i++) {
        printf("A get(%d) = %d\n", i, ARRAYLIST_GET(A, i, int));
    }
    
    printf("/----------------------------------/\n");
    printf("A start release\n");
    ARRAYLIST_RELEASE(A);    
    if (NULL == A) {
        printf("A release success\n");
    }

    return 0;
}
