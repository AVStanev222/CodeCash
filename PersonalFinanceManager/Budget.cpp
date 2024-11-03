#include "Budget.h"
#include <iostream>
#include <fstream>
#include "Utils.h"
using namespace std;

void Budget::SetBudget() {
    string category;
    string amountStr;
    double amount;
    cout << "Enter category to set budget for: ";
    cin >> category;
    cout << "Enter budget amount: ";
    cin >> amountStr;
    if (!IsValidAmount(amountStr)) {
        cout << "Invalid amount!\n";
        return;
    }
    amount = stod(amountStr);
    categoryBudgets[category] = amount;
    cout << "Budget set successfully!\n";
}

void Budget::CheckBudget(const string& category, double amount) {
    if (categoryBudgets.find(category) != categoryBudgets.end()) {
        if (amount >= categoryBudgets[category]) {
            cout << "Warning: You have reached your budget for " << category << "!\n";
        }
    }
}

void Budget::SaveBudgetData(const string& username) {
    ofstream outFile("data/" + username + "_budget.dat");
    outFile << categoryBudgets.size() << "\n";
    for (const auto& budget : categoryBudgets) {
        outFile << budget.first << " " << budget.second << "\n";
    }
    outFile.close();
}

bool Budget::LoadBudgetData(const string& username) {
    ifstream inFile("data/" + username + "_budget.dat");
    if (!inFile.is_open()) return false;

    size_t size;
    inFile >> size;
    for (size_t i = 0; i < size; ++i) {
        string category;
        double amount;
        inFile >> category >> amount;
        categoryBudgets[category] = amount;
    }
    inFile.close();
    return true;
}
