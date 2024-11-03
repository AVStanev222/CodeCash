#pragma once

#include <string>
using namespace std;

// User class for handling user-related functionalities
class User {
public:
    string username;
    string password;

    User();
    bool Register();
    bool Login();
    void SaveUserData();
    bool LoadUserData();
};