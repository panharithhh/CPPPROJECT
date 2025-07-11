#include "product.h"
#include <iostream>
#include <fstream> //allowing file stream operations
#include <sstream>
#include <iomanip>

using namespace std;

Stock::Stock(){
    head = NULL;
    tail = NULL;
}

Stock::~Stock(){
    Product* current = head;
    while(current!=nullptr){
        Product* next = current -> next;
        delete current;
        current = next;
    }
}

void Stock::_addProduct(int id, string name, double price, int quantity, string category){
    Product* p = new Product;
    p->id = id;
    p->name = name;
    p->price = price;
    p->quantity = quantity;
    p->category = category;
    p->next = nullptr;
    p->prev = nullptr;

    if(head == nullptr){
        head = tail = p;
    } else {
        p->prev = tail;
        tail->next = p;
        tail = p;
    }
}

void Stock::addProduct(int id, string name, double price, int quantity, string category){
    _addProduct(id, name, price, quantity, category);
    saveStock(); // Save changes to file
    cout << "Product added successfully!\n";
}

void Stock::viewProduct(const string& stock){
    Product* current = head;
    cout << "\nID\tName\t\t\tPrice\t\tQuantity\tCategory\n";
    cout << "-----------------------------------------------------------------------------\n";
    while(current != nullptr){
        ostringstream priceStream;
        priceStream << fixed << setprecision(2) << current->price << "$";
        string priceWithDollar = priceStream.str();

        cout << left
             << setw(8) << current->id
             << setw(24) << current->name
             << setw(16) << priceWithDollar
             << setw(16) << current->quantity
             << setw(15) << current->category
             << endl;

        current = current->next;
    }
    cout << "-----------------------------------------------------------------------------\n";
}

void Stock::updateProduct(int id){
    Product* current = head;
    bool found = false;
    while(current != nullptr){
        if(current->id == id){
            found = true;
            cout << "Updating product with ID " << id << ":\n";
            cout << "Enter new name: "; cin.ignore(); getline(cin, current->name);
            cout << "Enter new price: ";
            while (!(cin >> current->price)) {
                cout << "Invalid input. Please enter a number for the Price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Enter new quantity: ";
            while (!(cin >> current->quantity)) {
                cout << "Invalid input. Please enter a number for the Quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(); // Consume the newline character
            cout << "Enter new category: "; getline(cin, current->category);
            
            saveStock(); // Save changes to file
            cout << "Product updated successfully.\n";
            break;
        }
        current = current->next;
    }

    if(!found){
        cout << "Product with ID: " << id << " not found.\n";
    }
}

void Stock::deleteProduct(int id){
    Product* current = head;
    bool found = false;
    while(current != nullptr){
        if(current->id == id){
            found = true;
            if(current == head){
                head = current->next;
                if(head) head->prev = nullptr;
            } else {
                current->prev->next = current->next;
            }

            if(current == tail){
                tail = current->prev;
                if(tail) tail->next = nullptr;
            } else {
                current->next->prev = current->prev;
            }

            delete current;
            saveStock(); // Save changes to file
            cout << "Product deleted successfully.\n";
            break;
        }
        current = current->next;
    }

    if(!found){
        cout << "Product with ID: " << id << " not found.\n";
    }
}
void Stock::loadStock(){
    ifstream file("stock.csv");
    if(!file.is_open()){
        // If the file doesn't exist, it's not an error, just means no stock yet.
        return;
    }

    string line;
    getline(file, line); //skip header line

    while(getline(file, line)){
        stringstream ss(line);
        string idStr, name, priceStr, quantityStr, category;

        getline(ss, idStr, ',');
        if(idStr.empty()) continue; // Skip empty lines
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, category, ',');

        _addProduct(stoi(idStr), name, stod(priceStr), stoi(quantityStr), category);
    }
    file.close();
}

void Stock::searchProduct(int id){
    Product* current = head;
    bool found = false;
    while(current != nullptr){
        if(current->id == id){
            found = true;
            cout << "\nID\tName\t\t\tPrice\t\tQuantity\tCategory\n";
            cout << "-----------------------------------------------------------------------------\n";
            ostringstream priceStream;
            priceStream << fixed << setprecision(2) << current->price << "$";
            string priceWithDollar = priceStream.str();

            cout << left
                 << setw(8) << current->id
                 << setw(24) << current->name
                 << setw(16) << priceWithDollar
                 << setw(16) << current->quantity
                 << setw(15) << current->category
                 << endl;
            cout << "-----------------------------------------------------------------------------\n";
            break; 
        }
        current = current->next;
    }

    if(!found){
        cout << "Product with ID: " << id << " not found.\n";
    }
}

void Stock::swapProductData(Product* a, Product* b) {
    string tempName = a->name;
    double tempPrice = a->price;
    int tempQuantity = a->quantity;
    string tempCategory = a->category;
    int tempId = a->id;

    a->name = b->name;
    a->price = b->price;
    a->quantity = b->quantity;
    a->category = b->category;
    a->id = b->id;

    b->name = tempName;
    b->price = tempPrice;
    b->quantity = tempQuantity;
    b->category = tempCategory;
    b->id = tempId;
}

void Stock::sortByName() {
    if (!head || !head->next) {
        return;
    }

    bool swapped;
    Product* current;
    Product* last = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->next != last) {
            if (current->name > current->next->name) {
                swapProductData(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);

    saveStock();
}

void Stock::saveStock(){
    ofstream outFile("stock.csv");
    if (!outFile.is_open()) {
        cout << "Failed to open stock.csv for writing data.\n";
        return;
    }

    outFile << "ID,Name,Price,Quantity,Category\n";
    Product* current = head;
    while (current != nullptr) {
        outFile << current->id << ',' << current->name << ',' << current->price << ',' << current->quantity << ',' << current->category << '\n';
        current = current->next;
    }
    outFile.close();
}