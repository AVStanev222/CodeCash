#include "Report.h"
#include <fstream>
#include <iostream>
#include <map>
#include <cstdlib> // for system()

using namespace std;

// Default constructor
ReportGenerator::ReportGenerator() {}

// Generate financial report
void ReportGenerator::generateReport(const IncomeManager& incomeManager, const ExpenseManager& expenseManager, const string& startDate, const string& endDate, const string& username) {
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    ofstream reportFile("reports/" + username + "_report.txt");
    reportFile << "Financial Report for the period " << startDate << " to " << endDate << "\n\n";

    // Income
    reportFile << "Income:\n";
    for (const auto& income : incomeManager.getIncomes()) {
        if (income.date >= startDate && income.date <= endDate) {
            reportFile << "Date: " << income.date << ", Category: " << income.category << ", Amount: " << income.amount << " BGN\n";
            totalIncome += income.amount;
        }
    }
    reportFile << "Total Income: " << totalIncome << " BGN\n\n";

    // Expenses
    reportFile << "Expenses:\n";
    for (const auto& expense : expenseManager.getExpenses()) {
        if (expense.date >= startDate && expense.date <= endDate) {
            reportFile << "Date: " << expense.date << ", Category: " << expense.category << ", Amount: " << expense.amount << " BGN\n";
            totalExpense += expense.amount;
        }
    }
    reportFile << "Total Expenses: " << totalExpense << " BGN\n\n";

    // Balance
    reportFile << "Net Balance: " << (totalIncome - totalExpense) << " BGN\n";

    reportFile.close();

    cout << "The report has been successfully generated and saved in the 'reports' folder.\n";
}

// Generate expense chart
void ReportGenerator::generateExpenseChart(const ExpenseManager& expenseManager, const string& username) {
    // Summarize expenses by category
    map<string, double> categoryTotals;
    for (const auto& expense : expenseManager.getExpenses()) {
        categoryTotals[expense.category] += expense.amount;
    }

    // Save data to file
    ofstream dataFile("reports/" + username + "_expense_data.dat");
    for (const auto& pair : categoryTotals) {
        dataFile << pair.first << " " << pair.second << endl;
    }
    dataFile.close();

    // Generate GNUplot script
    ofstream gnuplotScript("reports/" + username + "_expense_chart.plt");
    gnuplotScript << "set terminal png size 800,600\n";
    gnuplotScript << "set output 'reports/" << username << "_expense_chart.png'\n";
    gnuplotScript << "set title 'Expenses by Category'\n";
    gnuplotScript << "set xlabel 'Categories'\n";
    gnuplotScript << "set ylabel 'Amount (BGN)'\n";
    gnuplotScript << "set style data histograms\n";
    gnuplotScript << "set style fill solid\n";
    gnuplotScript << "set boxwidth 0.5\n";
    gnuplotScript << "plot 'reports/" << username << "_expense_data.dat' using 2:xtic(1) title 'Expenses'\n";
    gnuplotScript.close();

    // Execute the GNUplot script
    system(("gnuplot reports/" + username + "_expense_chart.plt").c_str());

    cout << "The expense chart has been successfully generated and saved in the 'reports' folder.\n";
}
