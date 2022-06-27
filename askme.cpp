#include<bits/stdc++.h>
using namespace std;

// Defining user struct
struct User {
    int id {};
    string user_name {};
    string password {};
    string name {};
    string email {};
    bool allow_aq {};
};

// seeding users to a vector from users.txt
vector<User> users;

void seedUsrs() {
    ifstream usrsfile;
    usrsfile.open("./users.txt");

    while (!usrsfile.eof()) {
        User new_user;
        usrsfile >> new_user.id >> new_user.user_name >> new_user.password
                 >> new_user.name >> new_user.email >> new_user.allow_aq;
        users.push_back(new_user);
    }

    usrsfile.close();
}

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "Menu:" << endl;
        cout << '\t' <<"1: Login\n";
        cout << '\t' <<"2: Sign Up\n";

        cout << "Enter number in range 1 - 2: ";
        cin >> choice;

        if (!(1 <= choice && choice <= 2)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;	// loop keep working
        }
    }
    return choice;
}
int userMenu() {
    int choice = -1;
    while (choice == -1) {
        cout << "\nMenu:" << endl;
        cout << '\t' <<"1: Print questions to me\n";
        cout << '\t' <<"2: Print questions from me\n";
        cout << '\t' <<"3: Answer question\n";
        cout << '\t' <<"4: Delete question\n";
        cout << '\t' <<"5: Ask question\n";
        cout << '\t' <<"6: List System Users\n";
        cout << '\t' <<"7: Feed\n";
        cout << '\t' <<"8: Logout\n";

        cout << "Enter number in range 1 - 8: ";
        cin >> choice;

        if (!(1 <= choice && choice <= 8)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;	// loop keep working
        }
    }
    return choice;
}

void signUp() {
        string user_name, password, name, email;
        bool allow_aq;
        int id;

        cout << "Enter id: ";
        cin >> id;
        cout << "Enter user name: ";
        cin >> user_name;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter email: ";
        cin >> email;
        cout << "Allow anonymous questions?: (0 or 1): ";
        cin >> allow_aq;

        User new_user = {id, user_name, password, name, email, allow_aq};
        users.push_back(new_user);

        ofstream usrsfile;
        usrsfile.open("./users.txt", ofstream ::app);

        usrsfile << id << ' ' <<user_name <<' '<< password
                << ' ' <<name << ' '<< email
                <<' ' <<allow_aq << endl;

        usrsfile.close();

        userMenu();
}



void system() {
    while (true) {
        int choice = menu();

        if (choice == 1)
            signUp();
/*        else
            signUp();*/
    }
}

int main() {
    seedUsrs();
    system();
    cout << "Hello world!";
    return 0;
}

/*
 * each user has name , password , email , allow AQ
 */