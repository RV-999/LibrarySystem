#include "objects.h"

#define TABLE_SIZE 503

typedef struct Node {
    Book* book;
    Node* next;
} Node;

typedef struct {
    Node* table[TABLE_SIZE];
} BookTable;

typedef struct {
    Node* head;
} BookList;

typedef struct {
    BookTable* bookTable;
    Node* bookList;
} Library;

Library* createLibrary();
void insertBook(Library* library, Book* book);
Book* searchBookByIsbn(Library* library, char* ISBN);
// int isBookAvailable(Library library, char* ISBN);
int borrowBook(Library* library, User* user, char* ISBN);
int returnBook(Library* library, User* user, char* ISBN);
void displayBooks(Library* library);
