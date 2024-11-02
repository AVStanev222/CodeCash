#include "Budget.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор по подразбиране
BudgetManager::BudgetManager() {}

// Задаване на бюджет за категория
void BudgetManager::setBudget(const string& category, double amount) {
    categoryBudgets[category] = amount;
    cout << "Бюджетът за категория '" << category << "' е зададен на " << amount << " лв.\n";
}

// Проверка на бюджета
void BudgetManager::checkBudget(const string& category, double currentTotal) {
    auto it = categoryBudgets.find(category);
    if (it != categoryBudgets.end()) {
        double budget = it->second;
        if (currentTotal >= 0.9 * budget) {
            cout << "Внимание: Достигнали сте 90% от бюджета за категория '" << category << "'.\n";
        }
    }
}

// Показване на всички бюджети
void BudgetManager::displayBudgets() const {
    cout << "Зададени бюджети по категории:\n";
    for (const auto& pair : categoryBudgets) {
        cout << "Категория: " << pair.first << ", Бюджет: " << pair.second << " лв.\n";
    }
}

// Зареждане на бюджети от файл
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

// Запис на бюджети във файл
void BudgetManager::saveToFile(const string& username) const {
    ofstream outfile("data/" + username + "_budgets.txt");
    for (const auto& pair : categoryBudgets) {
        outfile << pair.first << " " << pair.second << endl;
    }
    outfile.close();
}

// Вземане на бюджета за дадена категория
double BudgetManager::getBudgetForCategory(const string& category) const {
    auto it = categoryBudgets.find(category);
    if (it != categoryBudgets.end()) {
        return it->second;
    }
    return 0.0;
}
