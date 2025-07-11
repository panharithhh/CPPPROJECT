#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

using namespace std;

struct Product{
    int id;
    string name;
    double price;
    int quantity;
    string category;
    Product* prev;
    Product* next;
};

class Stock{
    private:
        Product* head;
        Product* tail;
        void swapProductData(Product* a, Product* b);
    void _addProduct(int id, string name, double price, int quantity, string category);

    public:
        Stock(); //Constructor 
        ~Stock(); //Destructor
        
        void addProduct(int id, string name, double price, int quantity, string category);
        void viewProduct(const string& stock);
        void updateProduct(int id);
        void deleteProduct(int id);
        void searchProduct(int id);
        void sortByName();
        void loadStock();
        void saveStock();

};

#endif