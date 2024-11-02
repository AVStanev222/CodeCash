#include "Report.h"
#include <fstream>
#include <iostream>
#include <map>
#include <cstdlib> // за system()

using namespace std;

// Конструктор по подразбиране
ReportGenerator::ReportGenerator() {}

// Генериране на финансов отчет
void ReportGenerator::generateReport(const IncomeManager& incomeManager, const ExpenseManager& expenseManager, const string& startDate, const string& endDate, const string& username) {
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    ofstream reportFile("reports/" + username + "_report.txt");
    reportFile << "Финансов отчет за периода " << startDate << " до " << endDate << "\n\n";

    // Приходи
    reportFile << "Приходи:\n";
    for (const auto& income : incomeManager.getIncomes()) {
        if (income.date >= startDate && income.date <= endDate) {
            reportFile << "Дата: " << income.date << ", Категория: " << income.category << ", Сума: " << income.amount << " лв.\n";
            totalIncome += income.amount;
        }
    }
    reportFile << "Общо приходи: " << totalIncome << " лв.\n\n";

    // Разходи
    reportFile << "Разходи:\n";
    for (const auto& expense : expenseManager.getExpenses()) {
        if (expense.date >= startDate && expense.date <= endDate) {
            reportFile << "Дата: " << expense.date << ", Категория: " << expense.category << ", Сума: " << expense.amount << " лв.\n";
            totalExpense += expense.amount;
        }
    }
    reportFile << "Общо разходи: " << totalExpense << " лв.\n\n";

    // Баланс
    reportFile << "Нетен баланс: " << (totalIncome - totalExpense) << " лв.\n";

    reportFile.close();

    cout << "Отчетът е генериран успешно и е записан в папката 'reports'.\n";
}

// Генериране на диаграма на разходите
void ReportGenerator::generateExpenseChart(const ExpenseManager& expenseManager, const string& username) {
    // Обобщаване на разходите по категории
    map<string, double> categoryTotals;
    for (const auto& expense : expenseManager.getExpenses()) {
        categoryTotals[expense.category] += expense.amount;
    }

    // Записване на данните във файл
    ofstream dataFile("reports/" + username + "_expense_data.dat");
    for (const auto& pair : categoryTotals) {
        dataFile << pair.first << " " << pair.second << endl;
    }
    dataFile.close();

    // Генериране на GNUplot скрипт
    ofstream gnuplotScript("reports/" + username + "_expense_chart.plt");
    gnuplotScript << "set terminal png size 800,600\n";
    gnuplotScript << "set output 'reports/" << username << "_expense_chart.png'\n";
    gnuplotScript << "set title 'Разходи по категории'\n";
    gnuplotScript << "set xlabel 'Категории'\n";
    gnuplotScript << "set ylabel 'Сума (лв.)'\n";
    gnuplotScript << "set style data histograms\n";
    gnuplotScript << "set style fill solid\n";
    gnuplotScript << "set boxwidth 0.5\n";
    gnuplotScript << "plot 'reports/" << username << "_expense_data.dat' using 2:xtic(1) title 'Разходи'\n";
    gnuplotScript.close();

    // Изпълнение на GNUplot скрипта
    system(("gnuplot reports/" + username + "_expense_chart.plt").c_str());

    cout << "Диаграмата на разходите е генерирана успешно и е записана в папката 'reports'.\n";
}
