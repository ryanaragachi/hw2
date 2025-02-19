#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std::string name, double price, int qty, 
             const std::string genre, const std::string rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    keys.insert(genre_); // Genre is a searchable keyword
    return keys;
}

std::string Movie::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\nGenre: " << genre_ 
        << " Rating: " << rating_ 
        << "\nPrice: $" << price_ 
        << " Quantity: " << qty_;
    return oss.str();
}

void Movie::dump(std::ostream& os) const {
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ 
       << "\n" << genre_ << "\n" << rating_ << std::endl;
}