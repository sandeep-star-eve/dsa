#ifndef BOOK_H
#define BOOK_H

struct Book{
    char title[50];
    double price;
};

void printBook(const struct Book *b, int size);

#endif
