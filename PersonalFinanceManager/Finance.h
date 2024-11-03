#pragma once

#include <string>
#include <vector>
using namespace std;

// Structure for financial records
struct Record {
    string date;
    string category;
    double amount;
};

class Finance {
public:
    vector<Record> incomes;
    vector<Record> expenses;

    void AddIncome();
    void EditIncome();
    void DeleteIncome();
    void AddExpense();
    void EditExpense();
    void DeleteExpense();
    void SaveFinanceData(const string& username);
    bool LoadFinanceData(const string& username);
};

