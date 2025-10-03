Book class: Holds book details (title, author, ISBN) and availability status.
            Provides methods for borrowing and returning books (borrowBook(), returnBook()).
 User class: Represents a library user with a name, ID, and list of borrowed books.
             Provides methods for borrowing (borrow()), checking if already borrowed (hasBorrowed()), and returning (returned()).  
library class:Aggregates Book and User objects.
              Handles core logic: searching, borrowing, and returning.
              Uses helper functions (findBookByISBN(), findUserById()) to avoid code duplication.
Variables inside a class (like title, author, isbn, available in the Book class) are declared as private, preventing direct access from outside the class while Book(const string&, const string&, const string&) are public that can interact with the book.
some Running Tests include:
 List Books- displays all the books available in the library
 Search by Title- its queries if the book is available to be borrowed
 Borrow Book- it allows a user to borrow an available book if the book is not available or has already been borrowed then the output is " borrow failed"
 Return Book- enables a user to return a book borrowed, the book was not borrowed the " return failed" because the book was already available

