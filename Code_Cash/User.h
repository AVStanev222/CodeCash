#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string passwordHash;

    bool userExists(const std::string& username);
    std::string hashPassword(const std::string& password);

public:
    User();
    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    std::string getUsername() const;
};

#endif // USER_H
