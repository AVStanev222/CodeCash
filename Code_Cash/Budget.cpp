#include "Budget.h"
#include <iostream>
#include <fstream>

using namespace std;

// Default constructor
BudgetManager::BudgetManager() {}

// Set budget for a category
void BudgetManager::setBudget(const string& category, double amount) {
    categoryBudgets[category] = amount;
    cout << "The budget for category '" << category << "' is set to " << amount << " units.\n";
}

// Check budget
void BudgetManager::checkBudget(const string& category, double currentTotal) {
    auto it = categoryBudgets.find(category);
    if (it != categoryBudgets.end()) {
        double budget = it->second;
        if (currentTotal >= 0.9 * budget) {
            cout << "Warning: You have reached 90% of the budget for category '" << category << "'.\n";
        }
    }
}

// Display all budgets
void BudgetManager::displayBudgets() const {
    cout << "Budgets set by category:\n";
    for (const auto& pair : categoryBudgets) {
        cout << "Category: " << pair.first << ", Budget: " << pair.second << " units.\n";
    }
}

// Load budgets from file
void BudgetManager::loadFromFile(const string& username) {
    categoryBudgets.clear();
    ifstream infile("data/" + username + "_budgets.txt");
    if (!infile) return;

    string category;
    double amount;
    while (infile >> category >> amount) {
        categoryBudgets[category] = amount;
    }
    infile.close();
}

// Save budgets to file
void BudgetManager::saveToFile(const string& username) const {
    ofstream outfile("data/" + username + "_budgets.txt");
    for (const auto& pair : categoryBudgets) {
        outfile << pair.first << " " << pair.second << endl;
    }
    outfile.close();
}

// Get budget for a specific category
double BudgetManager::getBudgetForCategory(const string& category) const {
    auto it = categoryBudgets.find(category);
    if (it != categoryBudgets.end()) {
        return it->second;
    }
    return 0.0;
}
