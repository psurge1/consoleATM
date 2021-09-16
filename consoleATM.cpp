#include <iostream>
#include <unordered_map>

using namespace std;

struct newUser {
    string name;
    string password;
    float money;
};

unordered_map<string, newUser> users;
bool loggedIn = false, signedUp = false;
string activeUser;
const string exitString = "exit()";

int mainMenu() {
    cout << "\n"
        << "         $$$   $$$" << endl
        << "         $$$   $$$" << endl
        << "     $$$$$$$$$$$$$$$" << endl
        << "   $$$$$$$$$$$$$$$$$$$$" << endl
        << "  $$$$$ $$$   $$$  $$$$" << endl
        << " $$$$$  $$$   $$$" << endl
        << " $$$$$  $$$   $$$" << endl
        << "  $$$$$  $$$   $$$" << endl
        << "   $$$$$$$$$$$$$$$$$$$" << endl
        << "     $$$$$$$$$$$$$$$$$$$$" << endl
        << "         $$$   $$$   $$$$$" << endl
        << "          $$$   $$$   $$$$$" << endl
        << "          $$$   $$$   $$$$$" << endl
        << " $$$$   $$$   $$$    $$$$$" << endl
        << "  $$$$$$$$$$$$$$$$$$$$$$" << endl
        << "    $$$$$$$$$$$$$$$$$$$" << endl
        << "       $$$    $$$" << endl
        << "       $$$    $$$" << endl;

    cout << "\n\nWelcome to Money Monkey ATM! What would you like to do?" <<endl;
    cout << "1) Login\n2) SignUp\n3) Quit" << endl;
    int userPick;
    bool picking = true;
    while (picking) {
        cin >> userPick;
        if (userPick == 1 || userPick == 2 || userPick == 3) {
            return userPick;
        }
        else {
            cout << "\nPlease enter a valid number (1, 2, or 3)" << endl;
        }
    }
}

int accountMenu() {
    cout << "\n\nHello " << activeUser << " what would you like to do?" << endl;
    cout << "1) Deposit Money\n2) Withdraw Money\n3) See Account\n4) Log Out\n";
    int userPick;
    bool picking = true;
    while (picking) {
        cin >> userPick;
        if (userPick == 1 || userPick == 2 || userPick == 3 || userPick == 4) {
            return userPick;
        }
        else {
            cout << "\nPlease enter a valid number (1, 2, or 3)" << endl;
        }
    }
}

bool checkIfIn(string key) {
    if (users.find(key) == users.end()) {
        return false;
    }
    return true;
}

string logIn() {
    bool loggingIn = true;
    while (loggingIn) {
        string username;
        string password;
        cout << "\nUsername: ";
        cin >> username;
        if (username == exitString) { 
            loggingIn = false;
        }
        else if (!checkIfIn(username)) {
            cout << "\n\nUsername doesn't exist. Retry or exit by typing  " << exitString << endl;
        }
        else {
            bool verifying = true;
            while (verifying) {
                cout << "\nPassword: ";
                cin >> password;
                if (password == exitString) {
                    verifying = false;
                }
                else {
                    if (users[username].password == password) {
                        loggedIn = true;
                        cout << "\nLogin successful!\n" << endl;
                        return username;
                    }
                    else {
                        cout << "\n\nUsername and Password dont match. Retry or exit by typing " << exitString << endl;
                    }
                }
            }
            loggingIn = false;
        }
    }
    loggedIn = false;
    return "";
}

string signUp() {
    string userN;
    string passW;
    float balance;
    bool signingUp = true;
    while (signingUp) {
        cout << "\nUsername: ";
        cin >> userN;
        if (userN == exitString) {
            signingUp = false;
        }
        else if (checkIfIn(userN) || userN == "") {
            cout << "\nUsername already taken or invalid! Try another name or exit by typing " << exitString << endl;
        }
        else {
            cout << "\nPassword: ";
            cin >> passW;
            if (passW == exitString) {
                signingUp = false;
            }
            else {
                cout << "\nInitial Deposit: ";
                cin >> balance;
                if (balance < 0) {
                    balance = 0;
                }
                signedUp = true;
                cout << "\nSign Up successful\n" << endl;
                newUser n = {
                    userN,
                    passW,
                    balance
                };
                users[userN] = n;
                return userN;
            }
        }
    }
}

void depositMoney() {
    int deposit;
    cout << "\nDeposit: ";
    cin >> deposit;
    users[activeUser].money += abs(deposit);
}

void withdrawMoney() {
    int withdrawal;
    cout << "\nWithdrawal: ";
    cin >> withdrawal;
    users[activeUser].money -= abs(withdrawal);
}

void runProgram() {
    bool runningP = true;
    while (runningP) {
        int accountSelection = accountMenu();
        if (accountSelection == 1) {
            depositMoney();
        }
        else if (accountSelection == 2) {
            withdrawMoney();
        }
        else if (accountSelection == 3) {
            cout << "\nName: " << users[activeUser].name << endl
                << "Password: " << users[activeUser].password << endl //delete
                << "Balance: " << users[activeUser].money << endl;
        }
        else if (accountSelection == 4) {
            loggedIn = false;
            signedUp = false;
            runningP = false;
        }
    }
}

int main() {
    bool running = true;
    while (running) {
        int selection = mainMenu();
            if (selection == 1) {
                activeUser = logIn();
                if (loggedIn) {
                    runProgram();
                }
                else {
                    continue;
                }
            }
            else if (selection == 2) {
                activeUser = signUp();
                if (signedUp) {
                    runProgram();
                }
                else {
                    continue;
                }
            }
            else if (selection == 3) {
                running = false;
            }
    }
    return 0;
}
