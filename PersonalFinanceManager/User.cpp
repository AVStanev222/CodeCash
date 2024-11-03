#include "User.h"
#include <iostream>
#include <fstream>
using namespace std;
User::User() : username(""), password("") {}

bool User::Register() {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Save user data
    SaveUserData();
    return true;
}

bool User::Login() {
    string inputUsername, inputPassword;
    cout << "Enter username: ";
    cin >> inputUsername;
    cout << "Enter password: ";
    cin >> inputPassword;

    username = inputUsername;
    if (LoadUserData() && password == inputPassword) {
        cout << "Login successful!\n";
        return true;
    }
    else {
        cout << "Invalid credentials!\n";
        return false;
    }
}

void User::SaveUserData() {
    ofstream outFile("data/" + username + "_user.dat");
    outFile << password;
    outFile.close();
}

bool User::LoadUserData() {
    ifstream inFile("data/" + username + "_user.dat");
    if (inFile.is_open()) {
        inFile >> password;
        inFile.close();
        return true;
    }
    return false;
}
