#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"
#include "Library.h"

Library* createLibrary() {
    Library* library = (Library*)malloc(sizeof(Library));
    if (!library) {
        perror("Failed to create library");
        return NULL;
    }
    library->bookTable = (BookTable*)malloc(sizeof(BookTable));
    library->bookList =  (BookList*)malloc(sizeof(BookList));
    if (!library->bookTable || !library->bookList) {
        perror("Faild to create table or list");
        free(library->bookTable);
        free(library->bookList);
        free(library);
        return NULL;
    }
    for (int i=0; i<TABLE_SIZE; i++) {
        library->bookTable->table[i] = NULL;
    }
    library->bookList->head = NULL;
    return library;
}
unsigned int hash (char* isbn){
    unsigned int hash = 0;
    while(*isbn) {
        hash = (hash << 5) + *isbn++;
    }

    return hash % TABLE_SIZE;
}

void insertBook(Library* library, Book* book) {
    unsigned int bookIndex = hash(book->ISBN);
    Node* tableNode = (Node*)malloc(sizeof(Node));
    Node* listNode = (Node*)malloc(sizeof(Node));
    if (!tableNode || !listNode) {
        perror("Failed to insert book");
        return;
    }
    tableNode->book = book;
    tableNode->next = library->bookTable->table[bookIndex];
    library->bookTable->table[bookIndex] = tableNode;

    listNode->book = book;
    listNode->next = library->bookList->head;
    library->bookList->head = listNode; 
}


Book* searchBookByIsbn(Library* library, char* ISBN){
    unsigned int bookIndex = hash(ISBN);
    Node* node = library->bookTable->table[bookIndex];
    while (node) {
        if (strcmp(node->book->ISBN, ISBN) == 0) {
            return node->book;
        }
        node = node->next;
    }
    return NULL;
}

// int isBookAvailable(Library library, char* ISBN){

// }

int borrowBook(Library* library, User* user, char* ISBN){
    Book* book = searchBookByIsbn(library, ISBN);
    if (!book || !book->isAvailable) {
        return 0;
    }
    
    for (int i = 0; i<MAX_BORROWED_BOOKS; i++){
        if (user->borrowedBooksISBN[i][0] == '\0') {
            strncpy(user->borrowedBooksISBN[i], ISBN, ISBN_LENGTH);
            book->isAvailable = 0;
            book->user = user;
            return 1;
        }
    }
    return 0; //brrowed the maximum nunber of books;
}

int returnBook(Library* library, User* user, char* ISBN) {
    for (int i = 0; i<MAX_BORROWED_BOOKS; i++){
        if (strcmp(user->borrowedBooksISBN[i], ISBN) == 0) {
            Book* book = searchBookByIsbn(library, ISBN);
            user->borrowedBooksISBN[i] = '\0';
            book->isAvailable = 1;
            book->user = NULL;
            return 1;
        }
    }
    return 0;
}

void displayBooks(Library* library){
    Node* node = library->bookList->head;
    while (node) {
        printf("Book: %s, ISBN: %s, Author: %s, Available: %d\n",
                node->book->name, node->book->ISBN, node->book->author, node->book->isAvailable);
        node = node->next;
    }
}



