#include "Finance.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
using namespace std;

void Finance::AddIncome() {
    Record record;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> record.date;
    if (!IsValidDate(record.date)) {
        cout << "Invalid date format!\n";
        return;
    }
    cout << "Enter category: ";
    cin >> record.category;
    cout << "Enter amount: ";
    string amountStr;
    cin >> amountStr;
    if (!IsValidAmount(amountStr)) {
        cout << "Invalid amount!\n";
        return;
    }
    record.amount = stod(amountStr);
    incomes.push_back(record);
    cout << "Income added successfully!\n";
}

void Finance::AddExpense() {
    Record record;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> record.date;
    if (!IsValidDate(record.date)) {
        cout << "Invalid date format!\n";
        return;
    }
    cout << "Enter category: ";
    cin >> record.category;
    cout << "Enter amount: ";
    string amountStr;
    cin >> amountStr;
    if (!IsValidAmount(amountStr)) {
        cout << "Invalid amount!\n";
        return;
    }
    record.amount = stod(amountStr);
    expenses.push_back(record);
    cout << "Expense added successfully!\n";
}

void Finance::SaveFinanceData(const string& username) {
    ofstream outFile("data/" + username + "_finance.dat");
    outFile << incomes.size() << "\n";
    for (const auto& income : incomes) {
        outFile << income.date << " " << income.category << " " << income.amount << "\n";
    }
    outFile << expenses.size() << "\n";
    for (const auto& expense : expenses) {
        outFile << expense.date << " " << expense.category << " " << expense.amount << "\n";
    }
    outFile.close();
}

bool Finance::LoadFinanceData(const string& username) {
    ifstream inFile("data/" + username + "_finance.dat");
    if (!inFile.is_open()) return false;

    size_t size;
    inFile >> size;
    incomes.resize(size);
    for (auto& income : incomes) {
        inFile >> income.date >> income.category >> income.amount;
    }
    inFile >> size;
    expenses.resize(size);
    for (auto& expense : expenses) {
        inFile >> expense.date >> expense.category >> expense.amount;
    }
    inFile.close();
    return true;
}
