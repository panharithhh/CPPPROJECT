#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

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

        for (int i = 0; i < 6; i++) {
            cout << password[i] << " ";
        }
        cout << endl;

        return returnPassword;
    }
};

int main() {
    srand(time(0));

    bool running = true;
    int choice;
    string email, password, re_entered_password, username, code;

    generatenum g;

    string generatedCode = g.computerGeneratedPassword();
    while (running) {
        cout << "1. Login\n";
        cout << "2. Sign up\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "--- Login ---\n";
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            cin >> password;
            cout << "Attempting to log in...\n";
        } else if (choice == 2) {
            cout << "--- Sign Up ---\n";
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            cin >> password;
            cout << "Re-enter your password: ";
            cin >> re_entered_password;
            cout << "Enter a username: ";
            cin >> username;
            cout << "Enter the registration code: ";
            cin >> code;
            cout << "Attempting to sign up...\n";

            if (code == generatedCode ) {

            } else {
                cout << " Wrong information";
            }
        } else if (choice == 3) {
            running = false;
            cout << "Exiting program.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
        cout << "\n";
    }

    return 0;
}