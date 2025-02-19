#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"  // Include MyDataStore

using namespace std;

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};

void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    // Instantiate MyDataStore (instead of generic DataStore)
    MyDataStore ds;

    // Instantiate product and user parsers
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the database parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Parse the database file to populate MyDataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    // Display menu
    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "=====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        if ((ss >> cmd)) {
            if (cmd == "AND") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0); // 0 = AND search
                displayProducts(hits);
            }
            else if (cmd == "OR") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1); // 1 = OR search
                displayProducts(hits);
            }
            else if (cmd == "ADD") {
                string username;
                int hitIndex;
                if (ss >> username >> hitIndex) {
                    ds.addToCart(username, hitIndex - 1); // Convert to 0-based index
                } else {
                    cout << "Invalid request" << endl;
                }
            }
            else if (cmd == "VIEWCART") {
                string username;
                if (ss >> username) {
                    ds.viewCart(username);
                } else {
                    cout << "Invalid username" << endl;
                }
            }
            else if (cmd == "BUYCART") {
                string username;
                if (ss >> username) {
                    ds.buyCart(username);
                } else {
                    cout << "Invalid username" << endl;
                }
            }
            else if (cmd == "QUIT") {
                string filename;
                if (ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.empty()) {
        cout << "No results found!" << endl;
        return;
    }
    sort(hits.begin(), hits.end(), ProdNameSorter());
    
    for (size_t i = 0; i < hits.size(); ++i) {  // Keeps original logic
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << hits[i]->displayString() << endl;  
        cout << endl;
        resultNo++;
    }
}