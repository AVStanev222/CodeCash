#include "Expense.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор по подразбиране
ExpenseManager::ExpenseManager() : nextId(1) {}

// Добавяне на разход
void ExpenseManager::addExpense(const ExpenseRecord& record) {
    ExpenseRecord newRecord = record;
    newRecord.id = nextId++;
    expenses.push_back(newRecord);
    cout << "Разходът е добавен успешно.\n";
}

// Редактиране на разход
void ExpenseManager::editExpense(int id, const ExpenseRecord& record) {
    for (auto& expense : expenses) {
        if (expense.id == id) {
            expense.date = record.date;
            expense.category = record.category;
            expense.amount = record.amount;
            cout << "Разходът е редактиран успешно.\n";
            return;
        }
    }
    cout << "Разход с дадения ID не е намерен.\n";
}

// Изтриване на разход
void ExpenseManager::deleteExpense(int id) {
    for (auto it = expenses.begin(); it != expenses.end(); ++it) {
        if (it->id == id) {
            expenses.erase(it);
            cout << "Разходът е изтрит успешно.\n";
            return;
        }
    }
    cout << "Разход с дадения ID не е намерен.\n";
}

// Показване на всички разходи
void ExpenseManager::displayExpenses() const {
    cout << "Списък на разходите:\n";
    for (const auto& expense : expenses) {
        cout << "ID: " << expense.id
            << ", Дата: " << expense.date
            << ", Категория: " << expense.category
            << ", Сума: " << expense.amount << " лв.\n";
    }
}

// Зареждане на разходи от файл
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

// Запис на разходи във файл
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

// Вземане на списъка с разходи
const vector<ExpenseRecord>& ExpenseManager::getExpenses() const {
    return expenses;
}
