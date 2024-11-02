#include "Income.h"
#include <iostream>
#include <fstream>

using namespace std;

// Default constructor
IncomeManager::IncomeManager() : nextId(1) {}

// Add income
void IncomeManager::addIncome(const IncomeRecord& record) {
    IncomeRecord newRecord = record;
    newRecord.id = nextId++;
    incomes.push_back(newRecord);
    cout << "Income added successfully.\n";
}

// Edit income
void IncomeManager::editIncome(int id, const IncomeRecord& record) {
    for (auto& income : incomes) {
        if (income.id == id) {
            income.date = record.date;
            income.category = record.category;
            income.amount = record.amount;
            cout << "Income edited successfully.\n";
            return;
        }
    }
    cout << "Income with the given ID not found.\n";
}

// Delete income
void IncomeManager::deleteIncome(int id) {
    for (auto it = incomes.begin(); it != incomes.end(); ++it) {
        if (it->id == id) {
            incomes.erase(it);
            cout << "Income deleted successfully.\n";
            return;
        }
    }
    cout << "Income with the given ID not found.\n";
}

// Display all incomes
void IncomeManager::displayIncomes() const {
    cout << "List of incomes:\n";
    for (const auto& income : incomes) {
        cout << "ID: " << income.id
            << ", Date: " << income.date
            << ", Category: " << income.category
            << ", Amount: " << income.amount << " units.\n";
    }
}

// Load incomes from file
void IncomeManager::loadFromFile(const string& username) {
    incomes.clear();
    ifstream infile("data/" + username + "_incomes.txt");
    if (!infile) return;

    IncomeRecord record;
    while (infile >> record.id >> record.date >> record.category >> record.amount) {
        incomes.push_back(record);
        if (record.id >= nextId) {
            nextId = record.id + 1;
        }
    }
    infile.close();
}

// Save incomes to file
void IncomeManager::saveToFile(const string& username) const {
    ofstream outfile("data/" + username + "_incomes.txt");
    for (const auto& income : incomes) {
        outfile << income.id << " "
            << income.date << " "
            << income.category << " "
            << income.amount << endl;
    }
    outfile.close();
}

// Get list of incomes
const vector<IncomeRecord>& IncomeManager::getIncomes() const {
    return incomes;
}
