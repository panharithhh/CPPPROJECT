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

void Stock::addProduct(int id, string name, double price, int quantity, string category){
    Product* p = new Product;
    p -> id = id;
    p -> name = name;
    p -> price = price;
    p -> quantity = quantity;
    p -> category = category;
    p -> next = nullptr;
    p -> prev = nullptr;

    if(head == nullptr){
        head = tail = p;
    }else{
        p -> prev = tail;
        tail -> next = p;
        tail = p;
    }

    // Check if file exists and is empty before writing header
    bool writeHeader = false;
    ifstream read("stock.csv");
    if (!read.good()) {
        writeHeader = true; // File content does not exist (not have header yet)
    } else {
        read.seekg(0, ios::end);
        if (read.tellg() == 0) {
            writeHeader = true; // File is empty
        }
    }
    read.close();

    ofstream write("stock.csv", ios::app);
    if(write.is_open()){
        if(writeHeader){
            write<<"ID, Name, Price, Quantity, Category\n";
        }
        write<<id<<","<<name<<","<<price<<","<<quantity<<","<<category<<endl;
        write.close();
    }else{
        cout<<"Unable to open file\n";
    }
        cout<<"Product added successfully!\n";
    
}

void Stock::viewProduct(const string& stock){
    // Product* current = head;
    cout << "\nID\tName\t\t\tPrice\t\tQuantity\tCategory\n";
    cout<<"-----------------------------------------------------------------------------\n";
    // while(current!=nullptr){
    //     cout<<current->id<<"\t"
    //         <<current->name<<"\t\t"
    //         <<current->price<<"$\t\t"
    //         <<current->quantity<<"\t\t"
    //         <<current->category<<"\n";

    //     current = current -> next;
    ifstream file(stock);
        if(!file.is_open()){
            cout<<"Failed to open "<<stock <<"\n";
            return;
        }
        string line;
        getline(file,line); //skip header line

        while(getline(file, line)){
            stringstream ss(line);
            string idStr, name, priceStr, quantityStr, category;

            getline(ss, idStr, ','); 
            getline(ss, name, ','); 
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, category, ',');

            // Convert strings to appropriate types
            int id = stoi(idStr);
            double price = stod(priceStr);
            int quantity = stoi(quantityStr);

            ostringstream priceStream;
            priceStream << fixed << setprecision(2) << price << "$";
            string priceWithDollar = priceStream.str();

            cout<<left
                <<setw(8) << id
                <<setw(24) << name
                <<setw(16) << priceWithDollar
                <<setw(16) << quantity
                <<setw(15) << category
                <<endl;
    
        }
        file.close();
        cout<<"-----------------------------------------------------------------------------\n";
}

void Stock::updateProduct(int id){
    ifstream read("stock.csv");
    if(!read.is_open()){
        cout<<"Unable to open file.\n";
        return;
    }

    ofstream temp("temp.csv");
    if(!temp.is_open()){
        cout<<"Unable to open temporary file.\n";
        return;
    }

    string line;
    bool update = false;
    getline(read, line);
    temp<<line<<"\n"; //copy header

    while(getline(read, line)){
        stringstream ss(line);
        string idStr, name, priceStr, quantityStr, category;

        getline(ss, idStr, ','); 
        getline(ss, name, ','); 
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, category, ',');

        if(stoi(idStr)==id){
            cout << "Updating product with ID " << id << ":\n";
            cout << "Enter new name: "; cin.ignore(); getline(cin, name);
            cout << "Enter new price: "; cin >> priceStr;
            cout << "Enter new quantity: "; cin >> quantityStr;
            cout << "Enter new category: "; cin.ignore(); getline(cin, category);
            update = true;
        }
        temp << idStr << "," << name << "," << priceStr << "," << quantityStr << "," << category << "\n";
    }
    read.close();
    temp.close();

    if(update){
        remove("stock.csv");
        rename("temp.csv", "stock.csv");
        cout<<"Product updated successfully.\n";
    }else{
        remove("temp.csv");
        cout<<"Product with ID: "<<id<<" not found.\n";
    }
}

void Stock::deleteProduct(int id){
    ifstream read("stock.csv");
    if(!read.is_open()){
        cout<<"Unable to open file.\n";
        return;
    }
    ofstream temp("temp.csv");
    if(!temp.is_open()){
        cout<<"Unable to open temporary file.\n";
        return;
    }

    bool found = false;
    string line;
    getline(read, line);
    temp<<line<<"\n";

    while(getline(read,line)){
        stringstream ss(line);
        string idStr, name, priceStr, quantityStr, category;

        getline(ss, idStr, ','); 
        getline(ss, name, ','); 
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, category, ',');

        if(stoi(idStr)!=id){
            temp << idStr << "," << name << "," << priceStr << "," << quantityStr << "," << category << "\n";
        }else{
            found = true;
        }
    }
    read.close();
    temp.close();

    if(found){
        remove("stock.csv");
        rename("temp.csv", "stock.csv");
        cout<<"Product deleted successfully.\n";
    }else{
        remove("temp.csv");
        cout<<"Product with ID: "<<id<<" not found.\n";
    }
}
void Stock::searchProduct(int id){
    ifstream read("stock.csv");
    if(!read.is_open()){
        cout<<"Unable to open file.\n";
        return;
    }

    string line;
    getline(read, line);

    while(getline(read, line)){
        stringstream ss(line);
        string idStr, name, priceStr, quantityStr, category;

        getline(ss, idStr, ','); 
        getline(ss, name, ','); 
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, category, ',');

        if(stoi(idStr)==id){
                cout << "\nID\tName\t\t\tPrice\t\tQuantity\tCategory\n";
                cout<<"-----------------------------------------------------------------------------\n";
                cout<<left
                <<setw(8) << id
                <<setw(24) << name
                <<setw(16) << priceStr
                <<setw(16) << quantityStr
                <<setw(15) << category
                <<endl;
                cout<<"-----------------------------------------------------------------------------\n";
        }
    }
}