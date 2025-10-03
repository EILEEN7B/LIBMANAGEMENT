Book class: Holds book details (title, author, ISBN) and availability status.
            Provides methods for borrowing and returning books (borrowBook(), returnBook()).
 User class: Represents a library user with a name, ID, and list of borrowed books.
             Provides methods for borrowing (borrow()), checking if already borrowed (hasBorrowed()), and returning (returned()).  
library class:Aggregates Book and User objects.
              Handles core logic: searching, borrowing, and returning.
              Uses helper functions (findBookByISBN(), findUserById()) to avoid code duplication.
