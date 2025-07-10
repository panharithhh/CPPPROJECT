#include "product.h"
#include <iostream>

using namespace std;

int main(){
    int choice;
    int id, quantity;
    double price;
    string name, category;

    Stock stock;

    do{
        cout<<"*** WELCOME TO STOCK MANAGEMENT SYSTEM ***\n";
        cout<<"1. Add Product\n";
        cout<<"2. View Product\n";
        cout<<"3. Search Products\n";
        cout<<"4. Update Product\n";
        cout<<"5. Delete Product\n";
        cout<<"6. Exit\n";
        cout<<"Please select an option: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"*** Add Product ***\n";
                cout<<"Enter ID: "; cin>>id;
                cout<<"Enter name: "; cin>> name;
                cout<<"Enter Quantity: "; cin>> quantity;
                cout<<"Enter Price: "; cin>>price;
                cout<<"Enter categroy: "; cin>>category;
                stock.addProduct(id, name, price, quantity, category);
                break;
            case 2:
                stock.viewProduct();
                break;
            // case 3:
            //     searchProduct();
            //     break;
            // case 4:
            //     updateProduct();
            //     break;
            // case 5:
            //     deleteProduct();
            //     break;
            case 6:
                break;
            default:
                cout<<"Invalid choice. Please try again.\n";
                continue;
        }
    }while(choice!=6);
}