#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool available;

public:
    Book() = default;
    Book(const string &t, const string &a, const string &i)
        : title(t), author(a), isbn(i), available(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    bool isAvailable() const { return available; }

    bool borrowBook() {
        if (!available) return false;
        available = false;
        return true;
    }

    bool returnBook() {
        if (available) return false;
        available = true;
        return true;
    }

    void print() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn
             << ", " << (available ? "Available" : "Checked out") << '\n';
    }
};

class User {
private:
    string name;
    int id;
    vector<string> borrowedIsbns;

public:
    User() = default;
    User(const string &name_, int id_) : name(name_), id(id_) {}

    int getId() const { return id; }
    string getName() const { return name; }

    void borrow(const string &isbn) { borrowedIsbns.push_back(isbn); }
    bool hasBorrowed(const string &isbn) const {
        return find(borrowedIsbns.begin(), borrowedIsbns.end(), isbn) != borrowedIsbns.end();
    }
    void returned(const string &isbn) {
        auto it = find(borrowedIsbns.begin(), borrowedIsbns.end(), isbn);
        if (it != borrowedIsbns.end()) borrowedIsbns.erase(it);
    }
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

    Book* findBookByISBN(const string &isbn) {
        for (auto &b : books) if (b.getISBN() == isbn) return &b;
        return nullptr;
    }

    User* findUserById(int id) {
        for (auto &u : users) if (u.getId() == id) return &u;
        return nullptr;
    }

public:
    void addBook(const Book &b) { books.push_back(b); }
    void registerUser(const User &u) { users.push_back(u); }

    bool borrowBook(int userId, const string &isbn) {
        Book* b = findBookByISBN(isbn);
        User* u = findUserById(userId);
        if (!b || !u) return false;
        if (!b->borrowBook()) return false;
        u->borrow(isbn);
        return true;
    }

    bool returnBook(int userId, const string &isbn) {
        Book* b = findBookByISBN(isbn);
        User* u = findUserById(userId);
        if (!b || !u) return false;
        if (!u->hasBorrowed(isbn)) return false;
        if (!b->returnBook()) return false;
        u->returned(isbn);
        return true;
    }

    vector<Book> searchByTitle(const string &q) const {
        vector<Book> out;
        for (const auto &b : books) if (b.getTitle().find(q) != string::npos) out.push_back(b);
        return out;
    }

    void listAllBooks() const {
        for (const auto &b : books) b.print();
    }
};

// Simple interactive menu for Code Runner
int main() {
    Library lib;

    // seed data
    lib.addBook(Book("Twisted love", "Ana huang", "ISBN001"));
    lib.addBook(Book("The watchman ", "Scott Meyers", "ISBN002"));
    lib.addBook(Book("Clean Code", "benson boone", "ISBN003"));

    lib.registerUser(User("Eileen", 1));
    lib.registerUser(User("Rita", 2));

    while (true) {
        cout << "--- Library Menu ---\n";
        cout << "1) List books\n";
        cout << "2) Search by title\n";
        cout << "3) Borrow book\n";
        cout << "4) Return book\n";
        cout << "5) Exit\n";
        cout << "Choose: ";
        int choice;
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            lib.listAllBooks();
        } else if (choice == 2) {
            cout << "Enter search query: ";
            string q; getline(cin, q);
            auto res = lib.searchByTitle(q);
            cout << res.size() << " result(s)\n";
            for (const auto &b : res) b.print();
        } else if (choice == 3) {
            cout << "Enter user id: ";
            int uid; cin >> uid; cin.ignore();
            cout << "Enter ISBN to borrow: ";
            string isbn; getline(cin, isbn);
            bool ok = lib.borrowBook(uid, isbn);
            cout << (ok ? "Borrowed successfully" : "Borrow failed") << "\n";
        } else if (choice == 4) {
            cout << "Enter user id: ";
            int uid; cin >> uid; cin.ignore();
            cout << "Enter ISBN to return: ";
            string isbn; getline(cin, isbn);
            bool ok = lib.returnBook(uid, isbn);
            cout << (ok ? "Returned successfully" : "Return failed") << "\n";
        } else {
            break;
        }

        cout << 'All tests executed.\n';
    }

    return 0;
}

