#include "Report.h"
#include <fstream>
#include <iostream>
#include <map>
#include <cstdlib> // �� system()

using namespace std;

// ����������� �� ������������
ReportGenerator::ReportGenerator() {}

// ���������� �� �������� �����
void ReportGenerator::generateReport(const IncomeManager& incomeManager, const ExpenseManager& expenseManager, const string& startDate, const string& endDate, const string& username) {
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    ofstream reportFile("reports/" + username + "_report.txt");
    reportFile << "�������� ����� �� ������� " << startDate << " �� " << endDate << "\n\n";

    // �������
    reportFile << "�������:\n";
    for (const auto& income : incomeManager.getIncomes()) {
        if (income.date >= startDate && income.date <= endDate) {
            reportFile << "����: " << income.date << ", ���������: " << income.category << ", ����: " << income.amount << " ��.\n";
            totalIncome += income.amount;
        }
    }
    reportFile << "���� �������: " << totalIncome << " ��.\n\n";

    // �������
    reportFile << "�������:\n";
    for (const auto& expense : expenseManager.getExpenses()) {
        if (expense.date >= startDate && expense.date <= endDate) {
            reportFile << "����: " << expense.date << ", ���������: " << expense.category << ", ����: " << expense.amount << " ��.\n";
            totalExpense += expense.amount;
        }
    }
    reportFile << "���� �������: " << totalExpense << " ��.\n\n";

    // ������
    reportFile << "����� ������: " << (totalIncome - totalExpense) << " ��.\n";

    reportFile.close();

    cout << "������� � ��������� ������� � � ������� � ������� 'reports'.\n";
}

// ���������� �� �������� �� ���������
void ReportGenerator::generateExpenseChart(const ExpenseManager& expenseManager, const string& username) {
    // ���������� �� ��������� �� ���������
    map<string, double> categoryTotals;
    for (const auto& expense : expenseManager.getExpenses()) {
        categoryTotals[expense.category] += expense.amount;
    }

    // ��������� �� ������� ��� ����
    ofstream dataFile("reports/" + username + "_expense_data.dat");
    for (const auto& pair : categoryTotals) {
        dataFile << pair.first << " " << pair.second << endl;
    }
    dataFile.close();

    // ���������� �� GNUplot ������
    ofstream gnuplotScript("reports/" + username + "_expense_chart.plt");
    gnuplotScript << "set terminal png size 800,600\n";
    gnuplotScript << "set output 'reports/" << username << "_expense_chart.png'\n";
    gnuplotScript << "set title '������� �� ���������'\n";
    gnuplotScript << "set xlabel '���������'\n";
    gnuplotScript << "set ylabel '���� (��.)'\n";
    gnuplotScript << "set style data histograms\n";
    gnuplotScript << "set style fill solid\n";
    gnuplotScript << "set boxwidth 0.5\n";
    gnuplotScript << "plot 'reports/" << username << "_expense_data.dat' using 2:xtic(1) title '�������'\n";
    gnuplotScript.close();

    // ���������� �� GNUplot �������
    system(("gnuplot reports/" + username + "_expense_chart.plt").c_str());

    cout << "���������� �� ��������� � ���������� ������� � � �������� � ������� 'reports'.\n";
}
