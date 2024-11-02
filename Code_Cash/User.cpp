#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h> // �� �������� �� ������

using namespace std;

// ����������� �� ������������
User::User() {}

// �������� ���� ��������������� ��� ����������
bool User::userExists(const string& username) {
    ifstream infile("data/users.txt");
    string line;
    while (getline(infile, line)) {
        if (line == username) {
            return true;
        }
    }
    return false;
}

// �������� �� �������� � SHA256
string User::hashPassword(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.length(), hash);

    stringstream ss;
    for (unsigned char c : hash)
        ss << hex << setw(2) << setfill('0') << static_cast<int>(c);
    return ss.str();
}

// ����������� �� ����������
bool User::registerUser(const string& username, const string& password) {
    if (userExists(username)) {
        cout << "��������������� ��� ���� ����������.\n";
        return false;
    }

    string hashedPassword = hashPassword(password);

    ofstream outfile("data/users.txt", ios::app);
    outfile << username << endl << hashedPassword << endl;
    outfile.close();

    this->username = username;
    this->passwordHash = hashedPassword;

    cout << "������� �����������!\n";
    return true;
}

// ���� �� ����������
bool User::loginUser(const string& username, const string& password) {
    ifstream infile("data/users.txt");
    string storedUsername, storedPasswordHash;
    string hashedPassword = hashPassword(password);

    while (getline(infile, storedUsername) && getline(infile, storedPasswordHash)) {
        if (storedUsername == username && storedPasswordHash == hashedPassword) {
            this->username = username;
            this->passwordHash = storedPasswordHash;
            cout << "������� ����!\n";
            return true;
        }
    }

    cout << "��������� ������������� ��� ��� ������.\n";
    return false;
}

// ������� �� ��������������� ���
string User::getUsername() const {
    return username;
}
