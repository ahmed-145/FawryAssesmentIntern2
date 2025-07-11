#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>



class Book {
private:
    std::string ISBN;
    std::string title;
    std::string author;
    int year;
    double price;

public:
    Book(const std::string& isbn, const std::string& title, const std::string& author, int year, double price)
        : ISBN(isbn), title(title), author(author), year(year), price(price) {}

    virtual ~Book() = default;

    std::string getISBN() const { return ISBN; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }
    double getPrice() const { return price; }

    virtual bool isForSale() const = 0;
    virtual bool isShippable() const = 0;
    virtual void buy(int quantity, const std::string& email, const std::string& address) = 0;

    virtual void display() const {
        std::cout << "Quantum book store: ISBN: " << ISBN << ", Title: " << title
                  << ", Author: " << author << ", Year: " << year
                  << ", Price: $" << price << std::endl;
    }
};

class PaperBook : public Book {
private:
int stock;

public:
PaperBook(const std::string& isbn, const std::string& title, const std::string& author, int year, double price, int stock)
    : Book(isbn, title, author, year, price), stock(stock) {}

    bool isForSale() const override {
        return stock > 0;
    }

    bool isShippable() const override {
        return stock > 0;
    }

    void buy(int quantity, const std::string& email, const std::string& address) override {
        if (quantity <= stock) {
            stock -= quantity;
            std::cout << "Purchased " << quantity << " copies of " << getTitle() << " by " << getAuthor() << std::endl;
        } else {
            std::cout << "Not enough stock for " << getTitle() << std::endl;
        }
    }

};

class EBook : public Book {
private:
std::string filetype;

public:

EBook(const std::string& isbn, const std::string& title, const std::string& author, int year, double price, const std::string& filetype)
    : Book(isbn, title, author, year, price), filetype(filetype) {}

bool isForSale() const override {
    return true; 
}

bool isShippable() const override {
    return false;
}
void buy(int quantity, const std::string& email, const std::string& address) {
    std::cout << "Purchased " << quantity << " copies of " << getTitle()
              << " by " << getAuthor() << " (EBook)" << std::endl
              << "Download link sent to: " << email << std::endl;
}
};

class ShowcaseBook : public Book {
public:
    ShowcaseBook(const std::string& isbn, const std::string& title, const std::string& author,
                 int year, double price)
        : Book(isbn, title, author, year, price) {}

    bool isForSale() const override {
        return false;
    }

    bool isShippable() const override {
        return false;
    }

    void buy(int quantity, const std::string& email, const std::string& address) override {
        std::cout << "Quantum book store: This book is a showcase item and not available for sale.\n";
    }

    void display() const override {
        Book::display();
        std::cout << "Quantum book store: [Display Only (AKA) Not for Sale]" << std::endl;
    }
};

int main() {
    std::vector<Book*> books;

    // Add books
    books.push_back(new PaperBook("ISBN001", "Clean Code", "Robert C. Martin", 2008, 40.0, 5));
    books.push_back(new EBook("ISBN002", "Pragmatic Programmer", "Andy Hunt", 1999, 25.0, "PDF"));
    books.push_back(new ShowcaseBook("ISBN003", "Display Only", "Unknown", 1980, 999.0));

    // Display all books
    std::cout << "\nQuantum book store: All books in inventory:\n";
    for (Book* b : books) b->display();

    // Buy a PaperBook
    std::cout << "\nQuantum book store: Buying PaperBook (ISBN001)...\n";
    for (Book* b : books)
        if (b->getISBN() == "ISBN001") b->buy(2, "ahmed@example.com", "123 Book Street");

    // Buy an EBook
    std::cout << "\nQuantum book store: Buying EBook (ISBN002)...\n";
    for (Book* b : books)
        if (b->getISBN() == "ISBN002") b->buy(1, "ahmed@example.com", "ignored");

    // Try to buy a ShowcaseBook
    std::cout << "\nQuantum book store: Attempting to buy ShowcaseBook (ISBN003)...\n";
    for (Book* b : books)
        if (b->getISBN() == "ISBN003") b->buy(1, "ahmed@example.com", "ignored");

    // Remove outdated books older than 20 years (from 2025)
    std::cout << "\nQuantum book store: Removing books older than 20 years (from 2025)...\n";
    for (auto it = books.begin(); it != books.end(); ) {
        if (2025 - (*it)->getYear() > 20) {
            std::cout << "Quantum book store: Removed outdated book with ISBN " << (*it)->getISBN() << std::endl;
            delete *it;  // Free memory
            it = books.erase(it);  // Remove from vector
        } else {
            ++it;
        }
    }

    // Final state
    std::cout << "\nQuantum book store: Final inventory state:\n";
    for (Book* b : books) b->display();

    return 0;
}
