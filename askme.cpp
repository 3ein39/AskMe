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
    vector<int> questions_by_me; // storing ids of sent questions
    vector<int> questions_to_me; // storing ids of received questions
};

// Defining question struct
struct Question {
    int question_id;
    int sender_id;
    int receiver_id;
    bool is_anonymous_questions;
    string question;
    string answer;
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
        if (new_user.id == 0) break;
        users.push_back(new_user);
    }
    usrsfile.close();
}
// seeding questions from questions.txt
vector<Question> questions;

User& findUserById(int id) {
    for (auto & u: users) {
        if (id == u.id) {
            return u;
        }
    }
}

void seedQs() {
    ifstream qsfile;
    qsfile.open("./questions.txt");

    while (!qsfile.eof()) {
        Question new_question;

        qsfile >> new_question.question_id >> new_question.sender_id
            >> new_question.receiver_id >> new_question.is_anonymous_questions;

        getline(qsfile, new_question.question, ',');
        getline(qsfile, new_question.answer,',');

        if (new_question.question.empty()) break; // handling the eof

        User& sender = findUserById(new_question.sender_id);
        sender.questions_by_me.push_back(new_question.question_id);

        User& receiver = findUserById(new_question.receiver_id);
        receiver.questions_to_me.push_back(new_question.question_id);

        questions.push_back(new_question);
    }

    qsfile.close();
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
int userMenu(int id) {
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

int logIn() {
   while (true) {
        cout << "Enter user name & password: ";
        string user_name, password;
        cin >> user_name >> password;
        int id{};
        for (const auto &user: users) {
            if (user.user_name == user_name && user.password == password) {
                id = user.id;
                break;
            }
        }
        if (id == 0) {
            cout << "Invalid username or password...\n"
                 << "please try again.\n";
            continue;
        } else
            return id;
    }
}

int signUp() {
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

        return id;
}

void listUsers() {
    for (const auto user: users) {
        cout << "ID: " << user.id
            << "\tNamw: " << user.name
            << endl;
    }
}

void listQuestionsToMe(int id) {
    const User& user = findUserById(id);
    cout << user.questions_to_me[0] << endl;
}

void askSystem(int id) {
    while (true) {
        int choice = userMenu(id);

        if (choice == 1)
            listQuestionsToMe(id);
        else if (choice == 6)
            listUsers();
        else if (choice == 8)
            break;
    }
}

void system() {
    while (true) {
        int choice = menu();
        int id = 0;
        if (choice == 1)
            id = logIn();
        else if (choice == 2)
            id = signUp();
        else
            break;
        if (id) askSystem(id);
    }
}

int main() {
    seedUsrs();
    seedQs();
    system();
    return 0;
}
