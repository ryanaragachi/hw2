#include "book.h"
#include "util.h"
#include <sstream>

Book::Book(const std::string name, double price, int qty, 
           const std::string isbn, const std::string author)
    : Product("book", name, price, qty), isbn_(isbn), author_(author) {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> authorKeys = parseStringToWords(author_);
    keys.insert(isbn_); // ISBN is a searchable keyword
    keys = setUnion(keys, authorKeys); // Merge with author's keywords
    return keys;
}

std::string Book::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\nAuthor: " << author_ 
        << " ISBN: " << isbn_ 
        << "\nPrice: $" << price_ 
        << " Quantity: " << qty_;
    return oss.str();
}

void Book::dump(std::ostream& os) const {
    os << "book\n" << name_ << "\n" << price_ << "\n" << qty_ 
       << "\n" << isbn_ << "\n" << author_ << std::endl;
}