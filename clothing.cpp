#include "clothing.h"
#include "util.h"
#include <sstream>

Clothing::Clothing(const std::string name, double price, int qty, 
                   const std::string size, const std::string brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> brandKeys = parseStringToWords(brand_);
    keys = setUnion(keys, brandKeys); // Brand is a searchable keyword
    return keys;
}

std::string Clothing::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\nSize: " << size_ 
        << " Brand: " << brand_ 
        << "\nPrice: $" << price_ 
        << " Quantity: " << qty_;
    return oss.str();
}

void Clothing::dump(std::ostream& os) const {
    os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_ 
       << "\n" << size_ << "\n" << brand_ << std::endl;
}