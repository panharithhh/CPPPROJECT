#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
        }
        cout << "\n";
    }

    return 0;
}