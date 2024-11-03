#include "Reports.h"
#include <iostream>
#include <map>
using namespace std;
void Reports::GenerateReport(const Finance& finance) {
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    for (const auto& income : finance.incomes) {
        totalIncome += income.amount;
    }
    for (const auto& expense : finance.expenses) {
        totalExpense += expense.amount;
    }

    cout << "Financial Report:\n";
    cout << "Total Income: $" << totalIncome << "\n";
    cout << "Total Expenses: $" << totalExpense << "\n";
    cout << "Net Savings: $" << (totalIncome - totalExpense) << "\n";
}

void Reports::AnalyzeExpenses(const Finance& finance) {
    map<string, double> expenseByCategory;
    double totalExpense = 0.0;

    for (const auto& expense : finance.expenses) {
        expenseByCategory[expense.category] += expense.amount;
        totalExpense += expense.amount;
    }

    cout << "Expense Analysis:\n";
    for (const auto& pair : expenseByCategory) {
        double percentage = (pair.second / totalExpense) * 100;
        cout << pair.first << ": $" << pair.second << " (" << percentage << "%)\n";
    }
}
