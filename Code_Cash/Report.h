#ifndef REPORT_H
#define REPORT_H

#include "Income.h"
#include "Expense.h"
#include <string>

class ReportGenerator {
public:
    ReportGenerator();
    void generateReport(const IncomeManager& incomeManager, const ExpenseManager& expenseManager, const std::string& startDate, const std::string& endDate, const std::string& username);
    void generateExpenseChart(const ExpenseManager& expenseManager, const std::string& username);
};

#endif // REPORT_H
