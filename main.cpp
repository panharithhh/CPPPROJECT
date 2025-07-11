#include "product.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

class generatenum {
public:
    string computerGeneratedPassword() {
        int password[6];
        string returnPassword = "";
        for (int i = 0; i < 6; i++) {
            password[i] = rand() % 10;
            returnPassword += to_string(password[i]);
        }
        cout << "Registration Code: ";
        for (int i = 0; i < 6; i++) {
            cout << password[i];
        }
        cout << endl;
        return returnPassword;
    }
};

int main() {
    srand(time(0));
    Stock stock;
    stock.loadStock(); 
    bool running = true;
    int choice;
    string email, password, re_entered_password, username, code;
    generatenum g;
    string generatedCode = g.computerGeneratedPassword();

    while (running) {
        cout<<"*** WELCOME TO STOCK MANAGEMENT SYSTEM ***\n";    
        cout<<R"(╦ ╦┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐  ╔═╗┌┬┐┌─┐┌─┐┬┌─  ╔╦╗┌─┐┌┐┌┌─┐┌─┐┌─┐┌┬┐┌─┐┌┐┌┌┬┐  ╔═╗┬ ┬┌─┐┌┬┐┌─┐┌┬┐\n;
                 ║║║├┤ │  │  │ ││││├┤    │ │ │  ╚═╗ │ │ ││  ├┴┐  ║║║├─┤│││├─┤│ ┬├┤ │││├┤ │││ │   ╚═╗└┬┘└─┐ │ ├┤ │││\n;
                 ╚╩╝└─┘┴─┘└─┘└─┘┴ ┴└─┘   ┴ └─┘  ╚═╝ ┴ └─┘└─┘┴ ┴  ╩ ╩┴ ┴┘└┘┴ ┴└─┘└─┘┴ ┴└─┘┘└┘ ┴   ╚═╝ ┴ └─┘ ┴ └─┘┴ ┴\n)";
        cout <<"\n\n\n\n";
        cout << "1. Login\n";
        cout << "2. Sign up\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 1) {
            cout << "Login\n";
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            cin >> password;

            ifstream file("data.csv");
            string line;
            bool loggedIn = false;

            while (getline(file, line)) {
                stringstream ss(line);
                string file_email, file_password, file_username;
                getline(ss, file_email, ',');
                getline(ss, file_password, ',');
                getline(ss, file_username, ',');
                if (file_email == email && file_password == password) {
                    loggedIn = true;
                    cout << "Welcome myfriend  " << file_username << "\n";
                    break;
                }
            }
            file.close();

            if (!loggedIn) {
                cout << "wrong password gang.\n";
            }

            if (loggedIn) {
                int menuChoice;
                do {
                    cout << "\n*** WELCOME TO STOCK MANAGEMENT SYSTEM ***\n";
                    cout << "== Menu ==\n";
                    cout << "1. Add Product\n";
                    cout << "2. View Product\n";
                    cout << "3. Search Products\n";
                    cout << "4. Update Product\n";
                    cout << "5. Delete Product\n";
                    cout << "6. Logout\n";
                    cout << "Please select an option: ";
                    while (!(cin >> menuChoice)) {
                        cout << "Invalid input. Please enter a number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    int id, quantity;
                    double price;
                    string name, category;
                    switch (menuChoice) {
                        case 1:
                            cout << "*** Add Product ***\n";
                            cout << "Enter ID: "; 
                            while (!(cin >> id)) {
                                cout << "Invalid input. Please enter a number for the ID: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Enter name: "; getline(cin, name);
                            cout << "Enter Quantity: ";
                            while (!(cin >> quantity)) {
                                cout << "Invalid input. Please enter a number for the Quantity: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cout << "Enter Price: ";
                            while (!(cin >> price)) {
                                cout << "Invalid input. Please enter a number for the Price: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Enter category: "; getline(cin, category);
                            stock.addProduct(id, name, price, quantity, category);
                            break;
                        case 2: {
                            int sortChoice;
                            cout << "\n== View Products ==\n";
                            cout << "1. View as is\n";
                            cout << "2. Sort by Name (A-Z)\n";
                            cout << "Please select an option: ";
                            while (!(cin >> sortChoice)) {
                                cout << "Invalid input. Please enter a number: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }

                            if (sortChoice == 1) {
                                stock.viewProduct("stock.csv");
                            } else if (sortChoice == 2) {
                                stock.sortByName();
                                cout << "Products have been sorted by name.\n";
                                stock.viewProduct("stock.csv");
                            } else {
                                cout << "Invalid choice. Returning to main menu.\n";
                            }
                            break;
                        }
                        case 3:
                            cout << "Search Product\n";
                            cout << "Enter product ID: ";
                            while (!(cin >> id)) {
                                cout << "Invalid input. Please enter a number for the ID: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            stock.searchProduct(id);
                            break;
                        case 4:
                            cout << "*** Update Product ***\n";
                            cout << "Enter the product ID: ";
                            cin >> id;
                            stock.updateProduct(id);
                            break;
                        case 5:
                            cout << "*** Delete Product ***\n";
                            cout << "Enter the product ID: ";
                            cin >> id;
                            stock.deleteProduct(id);
                            break;
                        case 6:
                            cout << "Logging out...\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            continue;
                    }
                } while (menuChoice != 6);
            }

        } else if (choice == 2) {
            cout << "sign up\n";
            cout << "enter your email: ";
            cin >> email;
            cout << "enter your password: ";
            cin >> password;
            cout << "enter your password again: ";
            cin >> re_entered_password;
            cout << "enter a username: ";
            cin >> username;
            cout << "enter the registration code: ";
            cin >> code;

            if (password != re_entered_password) {
                cout << "passwords do not match.\n";
            } else if (code == generatedCode) {
                ofstream file("data.csv", ios::app);
                file << email << "," << password << "," << username << "\n";
                file.close();
                cout << "sign up successful.\n";
                generatedCode = g.computerGeneratedPassword();
            } else {
                cout << "wrong information.\n";
            }
        } else if (choice == 3) {
            running = false;
            cout << "exiting program.\n";
        } else {
            cout << "invalid choice. Please try again.\n";
            break;
        }
        cout << "\n";
    }

    return 0;
}