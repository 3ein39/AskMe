#include<bits/stdc++.h>
using namespace std;

struct User {
    string user_name {};
    string password {};
    string name {};
    string email {};
    bool allow_aq {};
};
vector<User> users;

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "Menu:" << endl;
        cout << '\t' <<"1: Login\n";
        cout << '\t' <<"2: Sign Up\n";

        cin >> choice;

        if (!(1 <= choice && choice <= 2)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;	// loop keep working
        }
    }
    return choice;
}



void system() {
    while (true) {
        int choice = menu();

        /*if (choice == 1)
            signIn();
        else
            signUp();*/
    }
}

int main() {
    system();
    cout << "Hello world!";
    return 0;
}

/*
 * each user has name , password , email , allow AQ
 */