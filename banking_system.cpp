// retail banking system project.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


class BankSystem {
    private:
    //attributes
        //vector<Account> accounts;
        string currentUser;
        bool loggedIn;
    //methods
        void loadUsers();
        void loadAccounts();

        void signUp();
        void login();
        void logOut();

        void getBalance();
        void deposit();
        void withdraw();
        void transfer();

        void saveUsers();
        void saveAccounts();

};

class Account { 
};



vector<vector<string>> LoadCSV(const string& filename){
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


bool UsernameExists(string username, vector<vector<string>> users){
    for (int i = 0; i < users.size(); i++){
        if (users[i].size() > 0 && users[i][0] == username){
            return true;
        }
    }
    return false;
}


//methods:
void BankSystem::signUp() {
    string username;
    string password;
    string confirmed_password;
    bool username_taken {false};
    vector<vector<string>> users = LoadCSV("users.csv");

    do {
    cout << "enter a username";
    cin >> username;
    
    if (UsernameExists(username, users) == true){
        username_taken = true;
    }
    else {
        username_taken = false;
    }


    cout << "enter a password";
    cin >> password;

    cout << "confirm your password";
    cin >> confirmed_password;

    } while (username_taken == true || password != confirmed_password);
}

void BankSystem::login() {

}








int main(){

    vector<vector<string>> users = LoadCSV("users.csv");

    for (int i = 1; i < users.size(); i++){
        cout << users[i][0] << "\n";
        }
    
    
    return 0;
}
