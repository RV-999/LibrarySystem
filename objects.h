#define USER_NAME_LENGTH 10
#define MAX_BORROWED_BOOKS 5
#define ISBN_LENGTH 14
#define BOOK_NAME_LENGTH 20
#define AUTHOR_LENGTH 20


typedef struct {
    char firstName[USER_NAME_LENGTH];
    char lastName[USER_NAME_LENGTH];
    char borrowedBooksISBN[MAX_BORROWED_BOOKS][ISBN_LENGTH];
} User;

typedef struct {
    char ISBN[ISBN_LENGTH];
    char name[BOOK_NAME_LENGTH];
    char author[AUTHOR_LENGTH];
    int isAvailable; //1 if available, 0 if not
    User* user;
} Book;
