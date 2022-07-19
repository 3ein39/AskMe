#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

// some helper methods
void writeFileLines(const string &path, const vector<string> &lines, bool append = true) {
    auto status = ios::in | ios::out | ios::app;

    if (!append)
        status = ios::in | ios::out | ios::trunc;	// overwrite

    fstream file_handler(path.c_str(), status);

    if (file_handler.fail()) {
        cout << "\n\nERROR: Can't open the file\n\n";
        return;
    }
    for (const auto &line : lines)
        file_handler << line << "\n";

    file_handler.close();
}

// Defining user class
class User {
private:
    int user_id;             // internal system id
    string user_name;
    string password;
    string name;
    string email;
    int allow_aq;           // 0 or 1
    vector<int> questions_ids_by_me; // storing ids of sent questions
    // From question id to list of questions IDS on this question (thread questions) - For this user
    map<int, vector<int>> questionid_questionidsThead_to_map;

public:
    // Default constructor using initializer list
    User() : user_id(-1), allow_aq(-1) {}

    void resetToQuestions(const vector<int>& to_questions) {
        // clear the last question_by_me vector
        questions_ids_by_me.clear();

        // add the new questions to the vector
        for (const auto &quesion_id: to_questions)
            questions_ids_by_me.push_back(quesion_id);
    }

    void resetFromQuestions(const vector<pair<int, int>> &from_questions) {
        // clear the last map
        questionid_questionidsThead_to_map.clear();

        // add the new questions to the vector
        for (const auto &id_pair: from_questions)
            questionid_questionidsThead_to_map[id_pair.first].push_back(id_pair.second);
    }

    void readUser(const string &user_name, int id) {
        setUserName(user_name);
        setUserId(id);

        string str;

        cout << "Enter passwrod: ";
        cin >> str;
        setPassword(str);

        cout << "Enter name: ";
        cin >> str;
        setName(str);

        cout << "Enter email: ";
        cin >> str;
        setEmail(str);

        cout << "Allow anonymous questions (0 or 1): ";
        int st; cin >> st;
        setAllowAQ(st);
    }

    int isAllowAQ() const {
        return allow_aq;
    }

    string ToString() const {
        ostringstream oss;
        oss << user_id << " " << user_name << " " << password << " " << name << " " << email << " " << allow_aq;

        return oss.str();
    }

    void print() const {
        cout << "User " << user_id << ", " << user_name << " " << password << ", " << name << ", " << email << "\n";
    }

    // setters and getters
    void setUserId(int user_id) {
        this->user_id = user_id;
    }
    int getUserId() const {
        return user_id;
    }
    void setUserName(const string& user_name) {
        this->user_name = user_name;
    }
    const string& getUserName() const {
        return user_name;
    }
    void setPassword(const string& password) {
        this->password = password;
    }
    const string& getPassword() {
        return password;
    }
    void setName(const string &name) {
        this->name = name;
    }
    const string & getName() const {
        return name;
    }
    void setEmail(string& email) {
        this->email = email;
    }
    const string& getEmail() {
        return email;
    }
    void setAllowAQ(int allow_aq) {
        this->allow_aq = allow_aq;
    }
    int getAllowAQ() {
        return allow_aq;
    }

    const vector<int>& getQuestionsIdsByMe() const {
        return questions_ids_by_me;
    }

    const map<int, vector<int>>& getQuestionIdsThread() const {
        return questionid_questionidsThead_to_map;
    }

};

// Defining question struct
class Question {
private:
    int question_id;
    int parent_question_id;
    // if parent_question_id is 0, then no parent (first question in the thread)
    int sender_id;
    int receiver_id;
    bool is_anonymous_questions;
    string question_text;
    string answer_text;
public:
    // default constructor with initializer list
    Question()
    : question_id(-1), parent_question_id(-1), sender_id(-1), receiver_id(-1), is_anonymous_questions(1){}
    // TODO
    // question constructor line 122

    string ToString() const {
        ostringstream oss;
        oss << question_id << " " << parent_question_id << " " << sender_id << " " << receiver_id << " " << is_anonymous_questions << " " << question_text << " " << answer_text;
        return oss.str(); // To get and set string object whose content is present in the stream
    }
    // printing functions
    void printToQuestion() const {
        string prefix;

        if (parent_question_id != -1)
            prefix = "\tThread: ";

        cout << prefix << "Question Id: " << question_id;
        if (!is_anonymous_questions)
            cout << " from user id: " << sender_id;
        cout << "\t Question: " << question_text << "\n";

        if (!answer_text.empty())
            cout << prefix << "\tAnswer: " << answer_text << "\n";
        cout << "\n";
    }

    void printFromQuestion() const {
        cout << "Question Id: " << question_id;
        if (!is_anonymous_questions)
            cout << " !AQ";

        cout << " to user id: " << receiver_id;
        cout << "\t Question: " << question_text;

        if (!answer_text.empty())
        cout << "\tAnswer: " << answer_text << "\n";
        else
            cout << "\tNOT Answered YET\n";
    }

    void printFeedQuestion() const {
        if (parent_question_id != -1)
            cout << "Thread Parent Question ID :" << parent_question_id;

        cout << "Question Id :" << question_id;
        if (!is_anonymous_questions)
            cout << " from user id :" << sender_id;

        cout << " To user id :" << receiver_id;

        cout << "\t Question: " << question_text << "\n";
        if (!answer_text.empty())
            cout << "\tAnswer: " << answer_text << "\n";
    }


    // setters and getters
    void setQuestionId(int question_id)  {
        this->question_id = question_id;
    }
    int getQuestionId() const {
        return question_id;
    }
    void setParentQuestionId(int parent_question_id) {
        this->parent_question_id = parent_question_id;
    }
    int getParentQuestionId() const {
        return parent_question_id;
    }
    void setSenderId(int sender_id) {
        this->sender_id = sender_id;
    }
    int getSenderId() const {
        return sender_id;
    }
    void setReceiverId(int receiver_id) {
        this->receiver_id = receiver_id;
    }
    int getReceiverId() const {
        return receiver_id;
    }
    void setIsAnonymousQuestion(bool is_anonymous_questions) {
        this->is_anonymous_questions = is_anonymous_questions;
    }
    bool getIsAnonymousQuestion() const {
        return is_anonymous_questions;
    }
    void setQuestionText(string question_text) {
        this->question_text = question_text;
    }
    const string& getQuestionText() const {
        return question_text;
    }
    void setAnswerText(string answer_text) {
        this->answer_text = answer_text;
    }
    const string& getAnswerText() const {
        return answer_text;
    }

};

class QuestionsManager {
private:
    // From question id to list of questions IDS on this question (thread questions) - All users
    map<int, vector<int>> questionid_questionidsThead_to_map;

    // Map the question id to question object. Let's keep one place ONLY with the object
    // When you study pointers, easier handling
    map<int, Question> questionid_questionobject_map;

    int last_id;

public:
    QuestionsManager() {
        last_id = 0;
    }
    void loadDatabase() {
        last_id = 0;
        questionid_questionidsThead_to_map.clear();
        questionid_questionobject_map.clear();

        ifstream qsfile;
        qsfile.open("./questions.txt");
        // TODO fix question.txt i.e add parent id
        while (!qsfile.eof()) {
            int question_id, parent_question_id, sender_id, receiver_id, is_anonymous_questions;
            string question_text, answer_text;
            qsfile >> question_id >> parent_question_id >> sender_id
                   >> receiver_id >> is_anonymous_questions;

            getline(qsfile, question_text, ',');
            getline(qsfile, answer_text,',');

            if (question_text.empty()) break; // handling the eof

            Question new_question;
            new_question.setQuestionId(question_id);
            new_question.setParentQuestionId(parent_question_id);
            new_question.setSenderId(sender_id);
            new_question.setReceiverId(receiver_id);
            new_question.setIsAnonymousQuestion(is_anonymous_questions);
            new_question.setQuestionText(question_text);
            new_question.setAnswerText(answer_text);

            last_id = max(last_id, new_question.getQuestionId());

            questionid_questionobject_map[question_id] = new_question;

            if (new_question.getParentQuestionId() == -1)
                questionid_questionidsThead_to_map[new_question.getQuestionId()].push_back(new_question.getQuestionId());
            else
                questionid_questionidsThead_to_map[new_question.getParentQuestionId()].push_back(new_question.getQuestionId());
        }
        qsfile.close();
    }
    vector<int> getUserToQuestions(const User &user) {
        vector<int> question_ids;

        for(const auto &pair : questionid_questionidsThead_to_map) { // pair<int, vector<Question>>
            for (const auto &question_id: pair.second) { // vector<Question>

                // get the question from the map
                const Question &question = questionid_questionobject_map.find(question_id)->second;

                if (question.getSenderId() == user.getUserId())
                    question_ids.push_back(question.getQuestionId());
            }
        }
        return question_ids;
    }

    vector<pair<int, int>> getUserFromQuestions(const User &user) const {
        vector<pair<int, int>> question_ids;

        for (const auto &pair : questionid_questionidsThead_to_map) {	// pair<int, vector<Question>>
            for (const auto &question_id : pair.second) {		//  vector<Question>

                const Question &question = questionid_questionobject_map.find(question_id)->second;

                if (question.getReceiverId() == user.getUserId()) {
                    if (question.getParentQuestionId() == -1)
                        question_ids.push_back(make_pair(question.getQuestionId(), question.getQuestionId()));
                    else
                        question_ids.push_back(make_pair(question.getParentQuestionId(), question.getQuestionId()));
                }
            }
        }
        return question_ids;
    }

    void printUserToQuestions(const User &user) const {
        cout << "\n";

        if (user.getQuestionIdsThread().size() == 0)
            cout << "No Questions";

        for (const auto &pair : user.getQuestionIdsThread()) {		// pair<int, vector<Question>>
            for (const auto &question_id : pair.second) {		//  vector<Question>

                // Get the question from the map. & means same in memory, DON'T COPY
                // Accessing questionid_questionobject_map[] change the map by adding if not exist. You can't use in const function
                // Here we just find, which return iterator (second is like a pointer to object)
                const Question &question = questionid_questionobject_map.find(question_id)->second;
                question.printToQuestion();
            }
        }
        cout << "\n";
    }

    void printUserFromQuestions(const User &user) const {
        cout << "\n";
        if(user.getQuestionsIdsByMe().size() == 0)
            cout << "No Questions";

        for (const auto &question_id : user.getQuestionsIdsByMe()) {    // vector<Question>
            const Question &question = questionid_questionobject_map.find(question_id)->second;
            question.printFromQuestion();
        }
        cout << "\n";
    }

    // To answer a question for you
    // whether it is a thraed one or a parent
    int readQuestionIdAny(const User &user) const {
        int question_id;
        cout << "Enter Question id or -1 to cancel: ";
        cin >> question_id;

        if (question_id == -1)
            return -1;

        if (!questionid_questionobject_map.count(question_id)) {
            cout << "\nERROR: Invalid question ID. Try again\n\n";
            return readQuestionIdAny(user);
        }
        return question_id;
    }

    // Used to ask a question on a specific thread for whatever user
    int readQuestionIdThread(const User &user) const {
        int question_id;
        cout << "For thread question: Enter Question id or -1 for new question: ";
        cin >> question_id;

        if(question_id == -1)
            return -1;

        if (!questionid_questionidsThead_to_map.count(question_id)){
            cout << "No thread question with such ID. Try again\n";
            return readQuestionIdThread(user);
        }
        return question_id;
    }

    void answerQuestion(const User &user) {
        int question_id = readQuestionIdAny(user);

        if (question_id == -1)
            return;

        Question &question = questionid_questionobject_map.find(question_id)->second;

        question.printToQuestion();

        if (!question.getAnswerText().empty())
            cout << "\nWarning: Already answered. Answer will be updated\n";

        cout << "Enter answer: ";

        string line;
        getline(cin, line);
        getline(cin, line);
        question.setAnswerText(line);
    }

    void deleteQuestion(const User &user) {
        int question_id = readQuestionIdAny(user);

        vector<int> ids_to_remove; // to remove from questionid_questionobject_map

        // if thread remove all of it
        if (questionid_questionidsThead_to_map.count(question_id)) {// thread
            ids_to_remove = questionid_questionidsThead_to_map[question_id];
            questionid_questionidsThead_to_map.erase(question_id);
        } else {
            ids_to_remove.push_back(question_id);

            // find in which thread to remove
            for (auto &pair : questionid_questionidsThead_to_map) {
                vector<int> &vec = pair.second;
                for (auto pos = 0; pos < (int) vec.size(); pos++) {
                    if (vec[pos] == question_id) {
                        vec.erase(vec.begin() + pos);
                        break;
                    }
                }
            }
        }
        for (const auto &id : ids_to_remove) {
            questionid_questionobject_map.erase(id);
        }
    }

    void askQuestion(const User &user, const pair<int, int> &to_user_pair){
       Question question;

       if (!to_user_pair.second) {
           cout << "Note: Anonymous questions are not allowed for this user\n";
           question.setIsAnonymousQuestion(0);
       } else {
           cout << "Is anonymous questions?: (0 or 1): ";
           int st;
           cin >> st;
           question.setIsAnonymousQuestion(st);
       }

       question.setParentQuestionId(readQuestionIdThread(user));

       cout << "Enter question text: ";
       string line;
       getline(cin, line);
       getline(cin, line);
       question.setQuestionText(line);

       question.setSenderId(user.getUserId());
       question.setReceiverId(to_user_pair.first);

       question.setQuestionId(++last_id);

       questionid_questionobject_map[question.getQuestionId()] = question;

       if (question.getParentQuestionId() == -1)
           questionid_questionidsThead_to_map[question.getQuestionId()].push_back(question.getQuestionId());
       else
           questionid_questionidsThead_to_map[question.getParentQuestionId()].push_back(question.getQuestionId());
    }

    void listFeed() const {
        for (const auto &pair : questionid_questionobject_map) {
            const Question &question = pair.second;

            if (question.getAnswerText().empty())
                continue;
            question.printFeedQuestion();
        }
    }

    void updateDatabase() {
        vector<string> lines;

        for (const auto &pair : questionid_questionobject_map)
            lines.push_back(pair.second.ToString());

        writeFileLines("questions.txt", lines, false);
    }
};

class UsersManager {
    private:
    map<string, User> username_userobject_map;
    User current_user;
    int last_id;

    public:
    // Default constructor
    UsersManager() {
        last_id = 0;
    }

    void loadDatabase() {
        // clearing the old data
        username_userobject_map.clear();

        ifstream usrsfile;
        usrsfile.open("./users.txt");

        while (!usrsfile.eof()) {
            User new_user;
            int id, allow_aq;
            string user_name, password, name, email;
            usrsfile >> id >> user_name >> password
                     >> name >> email >> allow_aq;
            new_user.setUserId(id);
            new_user.setUserName(user_name);
            new_user.setPassword(password);
            new_user.setName(name);
            new_user.setEmail(email);
            new_user.setAllowAQ(allow_aq);
            if (id == 0) break;

            username_userobject_map[new_user.getUserName()] = new_user;
            last_id = max(last_id, new_user.getUserId());
        }
        usrsfile.close();
    }

    void accessSystem() {
            int choice = menu();
            if (choice == 1)
                doLogin();
            else if (choice == 2)
                doSignup();
    }

    void doLogin() {
        loadDatabase(); // to allow parallel run

        while (true) {
            string name, pass;
            cout << "Enter username & password: ";
            cin >> name >> pass;
            current_user.setUserName(name);
            current_user.setPassword(pass);

            if (!username_userobject_map.count(current_user.getUserName())) {
                cout << "\nInvalid user name or password. Try again\n\n";
                continue;
            }
            User& user_exist = username_userobject_map[current_user.getUserName()];

            if (current_user.getPassword() != user_exist.getPassword()) {
                cout << "\nInvalid user name or password. Try again\n\n";
                continue;
            }

            current_user = user_exist;
            break;
        }
    }
    void doSignup() {
        string user_name;
        while (true) {
            cout << "Enter user name. (No spaces): ";
            cin >> user_name;

            if (username_userobject_map.count(user_name))
                cout << "Already used. Try again\n";
            else
                break;
        }
        // Move logic to user class, which may keep extending data members in future

        current_user.readUser(user_name, ++last_id);
        username_userobject_map[current_user.getUserName()] = current_user;

        updateDatabase(current_user);
    }

    void resetToQuestions(const vector<int> &to_question) {
        current_user.resetToQuestions(to_question);
    }

    void resetFromQuestions(const vector<pair<int, int>> &to_questions) {
        current_user.resetFromQuestions(to_questions);
    }

    void listUsersNamesIds() const {
        for (const auto &pair : username_userobject_map) {
            if (pair.second.getName().empty())
                continue;
            cout << "ID: " << pair.second.getUserId() << "\t\tName: " << pair.second.getName() << "\n";
        }
    }

    pair<int, int> readUserId() const {
        int user_id;
        cout << "Enter User id or -1 to cancel: ";
        cin >> user_id;

        if (user_id == -1)
            return make_pair(-1, -1);

        for (const auto &pair : username_userobject_map) {
            if (pair.second.getUserId() == user_id)
                return make_pair(user_id, pair.second.isAllowAQ());
        }

        cout << "Invalid User ID. Try again\n";
        return readUserId();
    }

    void updateDatabase(const User &user) {
        string line = user.ToString();
        vector<string> lines(1, line);
        writeFileLines("users.txt", lines);
    }

    const User& getCurrentUser() const {
        return current_user;
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

};

class AskMeSystem {
private:
    UsersManager users_manager;
    QuestionsManager questions_manager;

    void loadDatabase(bool fill_user_questions = false) {
        users_manager.loadDatabase();
        questions_manager.loadDatabase();

        if (fill_user_questions)    // first timw, waiting for user to login
            resetCurrentUserQuestions();
    }

    /*
	 * Probably the most important design change
	 * We needed to decouple the question manager from relying on User implementation
	 * We break to 2 steps
	 * 1) Question manager return relevant question
	 * 2) User manager helps reseting the user question. Even the manager doesn't do this by itself
	 *
	 * This is more OO now
	 */

    void resetCurrentUserQuestions() {
        const User& user = users_manager.getCurrentUser();

        const auto &to_questions = questions_manager.getUserToQuestions(user);
        users_manager.resetToQuestions(to_questions);

        const auto &from_questions = questions_manager.getUserFromQuestions(user);
        users_manager.resetFromQuestions(from_questions);
    }

public:
    void Run() {
        loadDatabase(false);
        users_manager.accessSystem();
        resetCurrentUserQuestions();

        while (true) {
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
                int choice;
                cin >> choice;

            loadDatabase(true);

            if (choice == 1)
                questions_manager.printUserToQuestions(users_manager.getCurrentUser());
            else if (choice == 2)
                questions_manager.printUserFromQuestions(users_manager.getCurrentUser());
            else if (choice == 3) {
                questions_manager.answerQuestion(users_manager.getCurrentUser());
                questions_manager.updateDatabase();
            } else if (choice == 4) {
                questions_manager.deleteQuestion(users_manager.getCurrentUser());
                // Let's build again (just easier, but slow)
                resetCurrentUserQuestions();
                questions_manager.updateDatabase();
            } else if (choice == 5) {
                pair<int, int> to_user_pair = users_manager.readUserId();
                if (to_user_pair.first != -1) {
                    questions_manager.askQuestion(users_manager.getCurrentUser(), to_user_pair);
                    questions_manager.updateDatabase();
                }
            } else if (choice == 6)
                users_manager.listUsersNamesIds();
            else if (choice == 7)
                questions_manager.listFeed();
            else if (choice >= 1 && choice < 8)
                choice = -1;
            else
                break;


        }

        Run();	// Restart again
    }
};

int main() {
    AskMeSystem ask_me_system;
    ask_me_system.Run();
    return 0;
}
