#include "Expense.h"
#include <iostream>
#include <fstream>

using namespace std;

// ����������� �� ������������
ExpenseManager::ExpenseManager() : nextId(1) {}

// �������� �� ������
void ExpenseManager::addExpense(const ExpenseRecord& record) {
    ExpenseRecord newRecord = record;
    newRecord.id = nextId++;
    expenses.push_back(newRecord);
    cout << "�������� � ������� �������.\n";
}

// ����������� �� ������
void ExpenseManager::editExpense(int id, const ExpenseRecord& record) {
    for (auto& expense : expenses) {
        if (expense.id == id) {
            expense.date = record.date;
            expense.category = record.category;
            expense.amount = record.amount;
            cout << "�������� � ���������� �������.\n";
            return;
        }
    }
    cout << "������ � ������� ID �� � �������.\n";
}

// ��������� �� ������
void ExpenseManager::deleteExpense(int id) {
    for (auto it = expenses.begin(); it != expenses.end(); ++it) {
        if (it->id == id) {
            expenses.erase(it);
            cout << "�������� � ������ �������.\n";
            return;
        }
    }
    cout << "������ � ������� ID �� � �������.\n";
}

// ��������� �� ������ �������
void ExpenseManager::displayExpenses() const {
    cout << "������ �� ���������:\n";
    for (const auto& expense : expenses) {
        cout << "ID: " << expense.id
            << ", ����: " << expense.date
            << ", ���������: " << expense.category
            << ", ����: " << expense.amount << " ��.\n";
    }
}

// ��������� �� ������� �� ����
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

// ����� �� ������� ��� ����
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

// ������� �� ������� � �������
const vector<ExpenseRecord>& ExpenseManager::getExpenses() const {
    return expenses;
}
