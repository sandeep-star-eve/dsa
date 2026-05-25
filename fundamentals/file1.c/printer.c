#include <stdio.h>
#include "book.h"

void printBook(const struct Book *ptr, int size) { 
    for(int i = 0; i < size; i++) {
        printf("book %d: %s - $%.2f\n", i + 1, (ptr + i)->title, (ptr + i)->price);
    }
}

