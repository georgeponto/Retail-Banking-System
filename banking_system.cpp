// retail banking system project.

// things to do: 05/07/2026
//  - make 2 do while loops for username and password seperatly in SignUp
//  - add \n to all couts
//  - add to 2dp for outputs in checkbalance and other outputs of balance
//  - rename password to pin and add validation for 4 letter length
//  - add validation to username so that no special characters or spaces can be entered only _ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


class BankSystem {
    public:
    //attributes
        string currentUser;
        bool loggedIn {false};
    //methods
        vector<vector<string>> loadUsers(const string& filename);
 
        void signUp(vector<vector<string>>& users);
        void login(const vector<vector<string>>& users);
        void logOut();

        void getBalance(string username, const vector<vector<string>>& users);
        void deposit(string username, vector<vector<string>>& users);
        void withdraw(string username, vector<vector<string>>& users);

        void saveUsers(const vector<vector<string>>& users, const string& filename);

};


void BankSystem::saveUsers(const vector<vector<string>>& users, const string& filename) {

    ofstream myfile(filename);
    if (myfile.is_open()) {
        for (int i = 0; i < users.size(); i++) {
        myfile << users[i][0] << "," << users[i][1] << "," << users[i][2] << "," << users[i][3] << "\n";
        }
    }
}

vector<vector<string>> BankSystem::loadUsers(const string& filename){
    vector<vector<string>> users;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "file: " << filename << " failed to open.";
        return users;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')){
            row.push_back(cell);
        }
        users.push_back(row);
    }
    return users;
}


bool UsernameExists(string username, const vector<vector<string>> users){
    for (int i = 0; i < users.size(); i++){
        if (users[i].size() > 0 && users[i][0] == username){
            return true;
        }
    }
    return false;
}

int LargestAccNum(const vector<vector<string>> users){
    int largestNum {0};
    for (int i = 1; i < users.size(); i++){
        if (users.size() > 2 && stoi(users[i][2]) > largestNum){
            largestNum = stoi(users[i][2]);
        }
    }
    return largestNum;
}


//methods:

void BankSystem::signUp(vector<vector<string>>& users) {
    string username;
    string password;
    string confirmed_password;
    string accountNumber;
    bool username_taken {false};
    bool passwords_match {false};
    int LargestAccNumber = LargestAccNum(users);
    string balance = "0.00";

    do {
    cout << "enter a username\n";
    cin >> username;
    
    if (UsernameExists(username, users) == true){
        username_taken = true;
        cout << "Username already taken, please try again.\n";
    }
    else {
        username_taken = false;
    }
    } while (username_taken == true);


    do {
    cout << "enter a password\n";
    cin >> password;

    cout << "confirm your password\n";
    cin >> confirmed_password;

    if (password == confirmed_password) {
        passwords_match = true;
    }
    else {
        passwords_match = false;
        cout << "Passwords do not match, please try again.\n";
    }

    } while (password != confirmed_password);
    accountNumber = to_string(LargestAccNumber+1);

    users.push_back({username, password,accountNumber,balance});
    saveUsers(users, "users.csv");

}

void BankSystem::login(const vector<vector<string>>& users) {
    
    string username;
    string password;
    loggedIn = false;
    bool userFound {false};

    do {
    cout << "enter your username:\n";
    cin >> username;

    cout << "enter your password\n";
    cin >> password;

    for (int i = 0; i < users.size(); i++){
        if (users[i].size() > 1 && users[i][0] == username && users[i][1] == password){
            cout << "Welcome " << username <<"\n";
            userFound = true;
            currentUser = username;
            loggedIn = true;
            break;
        }
    }
    if (userFound == false) {
        cout << "No user found, Please try again\n";
    }

    } while(userFound == false);
}

void BankSystem::getBalance(string username, const vector<vector<string>>& users){
    for (int i = 0; i < users.size(); i++){
        if (users[i].size() > 3 && users[i][0] == username){
            cout << "Your balance is: £" << users[i][3] << "\n";
        }
    }
}

void BankSystem::deposit(string username, vector<vector<string>>& users){
    
    double amountToDeposit {0};
    cout << "enter amount to deposit: ";
    cin >> amountToDeposit;

    for (int i = 0; i < users.size(); i++){
        if (users[i].size() > 3 && users[i][0] == username){
            users[i][3] = to_string(stod(users[i][3]) + amountToDeposit); 
            cout << "Your new balance is: £" << users[i][3] << "\n";
        }

    }
    saveUsers(users, "users.csv");
}

void BankSystem::withdraw(string username, vector<vector<string>>& users){

    double newBalance {-1};
    do {
    double amountToWithdraw {0};
    cout << "enter amount to withdraw: ";
    cin >> amountToWithdraw;


    for (int i = 0; i < users.size(); i++){
        if (users[i].size() > 3 && users[i][0] == username){
            newBalance = (stod(users[i][3]) - amountToWithdraw); 
            if (newBalance >= 0) {
                users[i][3] = to_string(newBalance);
                cout << "You new balance is: £" << users[i][3] << "\n";
                break;
            }
            else {
                cout << "You have insufficient funds.\n";
                break;
            }
        }
    }
    } while (newBalance < 0);
    saveUsers(users, "users.csv");
}

void BankSystem::logOut(){
    loggedIn = false;
    currentUser = "";
}





int main(){
    BankSystem bank;
    vector<vector<string>> users = bank.loadUsers("users.csv");

    int choice;

    do {
        cout << "--- RETAIL BANKING SYSTEM ---\n";
        cout << "1 - Log in\n";
        cout << "2 - Sign up\n";
        cout << "3 - Exit\n";
        cout << "Enter an option (1-3)\n";
        cin >> choice;

        if (choice == 1) {
            bank.login(users);

            int bankingChoice;

            do {
            cout << "\n-- BANKING MENU --\n";
            cout << "1 - Check Balance\n";
            cout << "2 - Deposit\n";
            cout << "3 - Withdraw\n";
            cout << "4 - Log Out\n";
            cout << "Enter an option.\n";
            cin >> bankingChoice;

            if (bankingChoice == 1) {
                bank.getBalance(bank.currentUser, users);
            }
            else if (bankingChoice == 2) {
                bank.deposit(bank.currentUser, users);
            }
            else if (bankingChoice == 3) {
                bank.withdraw(bank.currentUser, users);
            }
            else if (bankingChoice == 4) {
                bank.logOut();
                cout << "You have been successfully logged out.\n";
            }
            else {
                cout << "Invalid option.\n";
            }

            } while (bank.loggedIn == true);
        }

        else if (choice == 2) {
            bank.signUp(users);
            cout << "Your account has successfully been created.\n";
        }

        else if (choice == 3) {
            cout << "Exiting...\n";
        }

        else {
            cout << "Invalid option.\n";
        }

    } while (choice != 3);

    return 0;

}
