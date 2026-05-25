#include<stdio.h>
#include"book.h"

int main(){
    struct Book library[2] = {
        {"C Programming", 29.99},
        {"Data Structures", 39.99}
    };

    printBook(library, 2);
    return 0;
}