#pragma once

#include <string>
#include <map>
using namespace std;

class Budget {
public:
    map<string, double> categoryBudgets;

    void SetBudget();
    void CheckBudget(const string& category, double amount);
    void SaveBudgetData(const string& username);
    bool LoadBudgetData(const string& username);
};
