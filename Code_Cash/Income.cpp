#include "Income.h"
#include <iostream>
#include <fstream>

using namespace std;

// Конструктор по подразбиране
IncomeManager::IncomeManager() : nextId(1) {}

// Добавяне на приход
void IncomeManager::addIncome(const IncomeRecord& record) {
    IncomeRecord newRecord = record;
    newRecord.id = nextId++;
    incomes.push_back(newRecord);
    cout << "Приходът е добавен успешно.\n";
}

// Редактиране на приход
void IncomeManager::editIncome(int id, const IncomeRecord& record) {
    for (auto& income : incomes) {
        if (income.id == id) {
            income.date = record.date;
            income.category = record.category;
            income.amount = record.amount;
            cout << "Приходът е редактиран успешно.\n";
            return;
        }
    }
    cout << "Приход с дадения ID не е намерен.\n";
}

// Изтриване на приход
void IncomeManager::deleteIncome(int id) {
    for (auto it = incomes.begin(); it != incomes.end(); ++it) {
        if (it->id == id) {
            incomes.erase(it);
            cout << "Приходът е изтрит успешно.\n";
            return;
        }
    }
    cout << "Приход с дадения ID не е намерен.\n";
}

// Показване на всички приходи
void IncomeManager::displayIncomes() const {
    cout << "Списък на приходите:\n";
    for (const auto& income : incomes) {
        cout << "ID: " << income.id
            << ", Дата: " << income.date
            << ", Категория: " << income.category
            << ", Сума: " << income.amount << " лв.\n";
    }
}

// Зареждане на приходи от файл
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

// Запис на приходи във файл
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

// Вземане на списъка с приходи
const vector<IncomeRecord>& IncomeManager::getIncomes() const {
    return incomes;
}
