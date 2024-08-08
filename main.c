#include <stdio.h>
#include "objects.h"
#include "Library.h"

int main() {
    Library* library = createLibrary();
    if (!library) {
        printf("Failed to create library.\n");
        return 1;
    }

    Book book1 = {"1234567890123", "C Programming", "Author A", 1, NULL};
    Book book2 = {"1234567890124", "Embedded Systems", "Author B", 1, NULL};

    insertBook(library, &book1);
    insertBook(library, &book2);

    printf("Library after inserting books:\n");
    displayBooks(library);

    User user = {"John", "Doe", {0}};
    if (borrowBook(library, &user, "1234567890123")) {
        printf("Book borrowed successfully.\n");
    } else {
        printf("Failed to borrow book.\n");
    }

    printf("Library after borrowing a book:\n");
    displayBooks(library);

    if (returnBook(library, &user, "1234567890123")) {
        printf("Book returned successfully.\n");
    } else {
        printf("Failed to return book.\n");
    }

    printf("Library after returning a book:\n");
    displayBooks(library);

    return 0;
}
