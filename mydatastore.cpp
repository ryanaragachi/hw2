#include "mydatastore.h"
#include <iostream>

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    for (Product* p : products_) {
        delete p;
    }
    for (auto& u : users_) {
        delete u.second;
    }
}

void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
    std::set<std::string> keywords = p->keywords();
    for (const std::string& keyword : keywords) {
        keywordMap_[keyword].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users_[u->getName()] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> results;

    if (terms.empty()) return results;

    std::set<Product*> resultSet;
    if (keywordMap_.find(terms[0]) != keywordMap_.end()) {
        resultSet = keywordMap_[terms[0]];
    }

    for (size_t i = 1; i < terms.size(); ++i) {
        if (keywordMap_.find(terms[i]) != keywordMap_.end()) {
            if (type == 0) { // AND search
                resultSet = setIntersection(resultSet, keywordMap_[terms[i]]);
            } else { // OR search
                resultSet = setUnion(resultSet, keywordMap_[terms[i]]);
            }
        }
    }

    results.assign(resultSet.begin(), resultSet.end());
    return results;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>\n";

    ofile << "<users>\n";
    for (const auto& u : users_) {
        u.second->dump(ofile);
    }
    ofile << "</users>\n";
}

// --- Cart Management Methods ---

void MyDataStore::addToCart(std::string username, int hitIndex) {
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username\n";
        return;
    }
    if (hitIndex < 0 || hitIndex >= (int)products_.size()) {
        std::cout << "Invalid request\n";
        return;
    }
    carts_[username].push_back(products_[hitIndex]);
}

void MyDataStore::viewCart(std::string username) {
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username\n";
        return;
    }
    int index = 1;
    for (Product* p : carts_[username]) {
        std::cout << "Item " << index++ << ": " << p->displayString() << "\n";
    }
}

void MyDataStore::buyCart(std::string username) {
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username\n";
        return;
    }
    std::vector<Product*>& cart = carts_[username];
    User* user = users_[username];

    auto it = cart.begin();
    while (it != cart.end()) {
        Product* p = *it;
        if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            user->deductAmount(p->getPrice());
            it = cart.erase(it); // Remove item after purchase
        } else {
            ++it; // Skip items that can't be purchased
        }
    }
}