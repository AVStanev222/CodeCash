#include "Expense.h"
#include <iostream>
#include <fstream>

using namespace std;

// Default constructor
ExpenseManager::ExpenseManager() : nextId(1) {}

// Add expense
void ExpenseManager::addExpense(const ExpenseRecord& record) {
    ExpenseRecord newRecord = record;
    newRecord.id = nextId++;
    expenses.push_back(newRecord);
    cout << "Expense added successfully.\n";
}

// Edit expense
void ExpenseManager::editExpense(int id, const ExpenseRecord& record) {
    for (auto& expense : expenses) {
        if (expense.id == id) {
            expense.date = record.date;
            expense.category = record.category;
            expense.amount = record.amount;
            cout << "Expense edited successfully.\n";
            return;
        }
    }
    cout << "Expense with the given ID not found.\n";
}

// Delete expense
void ExpenseManager::deleteExpense(int id) {
    for (auto it = expenses.begin(); it != expenses.end(); ++it) {
        if (it->id == id) {
            expenses.erase(it);
            cout << "Expense deleted successfully.\n";
            return;
        }
    }
    cout << "Expense with the given ID not found.\n";
}

// Display all expenses
void ExpenseManager::displayExpenses() const {
    cout << "List of expenses:\n";
    for (const auto& expense : expenses) {
        cout << "ID: " << expense.id
            << ", Date: " << expense.date
            << ", Category: " << expense.category
            << ", Amount: " << expense.amount << " units.\n";
    }
}

// Load expenses from file
void ExpenseManager::loadFromFile(const string& username) {
    expenses.clear();
    ifstream infile("data/" + username + "_expenses.txt");
    if (!infile) return;

    ExpenseRecord record;
    while (infile >> record.id >> record.date >> record.category >> record.amount) {
        expenses.push_back(record);
        if (record.id >= nextId) {
            nextId = record.id + 1;
        }
    }
    infile.close();
}

// Save expenses to file
void ExpenseManager::saveToFile(const string& username) const {
    ofstream outfile("data/" + username + "_expenses.txt");
    for (const auto& expense : expenses) {
        outfile << expense.id << " "
            << expense.date << " "
            << expense.category << " "
            << expense.amount << endl;
    }
    outfile.close();
}

// Get list of expenses
const vector<ExpenseRecord>& ExpenseManager::getExpenses() const {
    return expenses;
}
