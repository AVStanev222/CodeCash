#include "Budget.h"
#include <iostream>
#include <fstream>

using namespace std;

// ����������� �� ������������
BudgetManager::BudgetManager() {}

// �������� �� ������ �� ���������
void BudgetManager::setBudget(const string& category, double amount) {
    categoryBudgets[category] = amount;
    cout << "�������� �� ��������� '" << category << "' � ������� �� " << amount << " ��.\n";
}

// �������� �� �������
void BudgetManager::checkBudget(const string& category, double currentTotal) {
    auto it = categoryBudgets.find(category);
    if (it != categoryBudgets.end()) {
        double budget = it->second;
        if (currentTotal >= 0.9 * budget) {
            cout << "��������: ���������� ��� 90% �� ������� �� ��������� '" << category << "'.\n";
        }
    }
}

// ��������� �� ������ �������
void BudgetManager::displayBudgets() const {
    cout << "�������� ������� �� ���������:\n";
    for (const auto& pair : categoryBudgets) {
        cout << "���������: " << pair.first << ", ������: " << pair.second << " ��.\n";
    }
}

// ��������� �� ������� �� ����
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

// ����� �� ������� ��� ����
void BudgetManager::saveToFile(const string& username) const {
    ofstream outfile("data/" + username + "_budgets.txt");
    for (const auto& pair : categoryBudgets) {
        outfile << pair.first << " " << pair.second << endl;
    }
    outfile.close();
}

// ������� �� ������� �� ������ ���������
double BudgetManager::getBudgetForCategory(const string& category) const {
    auto it = categoryBudgets.find(category);
    if (it != categoryBudgets.end()) {
        return it->second;
    }
    return 0.0;
}
