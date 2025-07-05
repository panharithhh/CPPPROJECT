#include "product.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main(){
    int choice;
    int id, quantity;
    double price;
    string name, category;

    Stock stock;
    cout<<"*** WELCOME TO STOCK MANAGEMENT SYSTEM ***\n";    
    // cout<<R"(╦ ╦┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ╔═╗┌┬┐┌─┐┌─┐┬┌─  ╔╦╗┌─┐┌┐┌┌─┐┌─┐┌─┐┌┬┐┌─┐┌┐┌┌┬┐  ╔═╗┬ ┬┌─┐┌┬┐┌─┐┌┬┐\n;
    //          ║║║├┤ │  │  │ ││││├┤    │ │ │  ╚═╗ │ │ ││  ├┴┐  ║║║├─┤│││├─┤│ ┬├┤ │││├┤ │││ │   ╚═╗└┬┘└─┐ │ ├┤ │││\n;
    //          ╚╩╝└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ╚═╝ ┴ └─┘└─┘┴ ┴  ╩ ╩┴ ┴┘└┘┴ ┴└─┘└─┘┴ ┴└─┘┘└┘ ┴   ╚═╝ ┴ └─┘ ┴ └─┘┴ ┴\n)";

    do{
        cout<<"\n== Menu ==\n";
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
                cout<<"Enter name: "; getline(cin, name);
                cout<<"Enter Quantity: "; cin>> quantity;
                cout<<"Enter Price: "; cin>>price;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Enter categroy: "; getline(cin, category);
                stock.addProduct(id, name, price, quantity, category);
                break;
            case 2:
                stock.viewProduct("stock.csv");
                break;
            case 3:
                cout<<"Search Product\n";
                cout<<"Enter product ID: ";
                cin>>id;
                stock.searchProduct(id);
                break;
            case 4:
                cout<<"*** Update Product ***\n";
                cout<<"Enter the product ID: ";
                cin>>id;
                stock.updateProduct(id);
                break;
            case 5:
                cout<<"*** Delete Product ***\n";
                cout<<"Enter the product ID: ";
                cin>>id;
                stock.deleteProduct(id);
                break;
            case 6:
                break;
            default:
                cout<<"Invalid choice. Please try again.\n";
                continue;
        }
    }while(choice!=6);
}