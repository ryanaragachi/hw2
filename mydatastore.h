#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <vector>
#include <map>
#include <set>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    // Additional methods for managing carts
    void addToCart(std::string username, int hitIndex);
    void viewCart(std::string username);
    void buyCart(std::string username);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*>> keywordMap_; // Keyword → Products
    std::map<std::string, std::vector<Product*>> carts_;   // Username → Cart
};

#endif