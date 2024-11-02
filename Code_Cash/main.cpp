#include <iostream>
#include "User.h"
#include "Income.h"
#include "Expense.h"
#include "Budget.h"
#include "Report.h"

using namespace std;

int main() {
    User user;
    IncomeManager incomeManager;
    ExpenseManager expenseManager;
    BudgetManager budgetManager;
    ReportGenerator reportGenerator;

    int choice;

    cout << "Welcome to the personal finance management application!\n";

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            user.registerUser(username, password);
        }
        else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (user.loginUser(username, password)) {
                incomeManager.loadFromFile(username);
                expenseManager.loadFromFile(username);
                budgetManager.loadFromFile(username);

                int userChoice;
                while (true) {
                    cout << "\n--- User Menu ---\n";
                    cout << "1. Manage Income\n";
                    cout << "2. Manage Expenses\n";
                    cout << "3. Budget Planning\n";
                    cout << "4. Generate Report\n";
                    cout << "5. Expense Analysis\n";
                    cout << "6. Logout\n";
                    cout << "Choose an option: ";
                    cin >> userChoice;

                    if (userChoice == 1) {
                        // Manage Income
                        int incomeChoice;
                        cout << "\n1. Add Income\n2. Edit Income\n3. Delete Income\n4. View Income\nChoose an option: ";
                        cin >> incomeChoice;

                        if (incomeChoice == 1) {
                            // Add Income
                            IncomeRecord record;
                            cout << "Enter date (YYYY-MM-DD): ";
                            cin >> record.date;
                            cout << "Enter category: ";
                            cin >> record.category;
                            cout << "Enter amount: ";
                            cin >> record.amount;

                            incomeManager.addIncome(record);
                        }
                        else if (incomeChoice == 2) {
                            // Edit Income
                            int id;
                            cout << "Enter income ID to edit: ";
                            cin >> id;

                            IncomeRecord record;
                            cout << "Enter new date (YYYY-MM-DD): ";
                            cin >> record.date;
                            cout << "Enter new category: ";
                            cin >> record.category;
                            cout << "Enter new amount: ";
                            cin >> record.amount;

                            incomeManager.editIncome(id, record);
                        }
                        else if (incomeChoice == 3) {
                            // Delete Income
                            int id;
                            cout << "Enter income ID to delete: ";
                            cin >> id;

                            incomeManager.deleteIncome(id);
                        }
                        else if (incomeChoice == 4) {
                            // View Income
                            incomeManager.displayIncomes();
                        }
                        else {
                            cout << "Invalid option.\n";
                        }
                    }
                    else if (userChoice == 2) {
                        // Manage Expenses
                        int expenseChoice;
                        cout << "\n1. Add Expense\n2. Edit Expense\n3. Delete Expense\n4. View Expenses\nChoose an option: ";
                        cin >> expenseChoice;

                        if (expenseChoice == 1) {
                            // Add Expense
                            ExpenseRecord record;
                            cout << "Enter date (YYYY-MM-DD): ";
                            cin >> record.date;
                            cout << "Enter category: ";
                            cin >> record.category;
                            cout << "Enter amount: ";
                            cin >> record.amount;

                            expenseManager.addExpense(record);
                            // Check budget
                            double total = 0.0;
                            for (const auto& expense : expenseManager.getExpenses()) {
                                if (expense.category == record.category) {
                                    total += expense.amount;
                                }
                            }
                            budgetManager.checkBudget(record.category, total);
                        }
                        else if (expenseChoice == 2) {
                            // Edit Expense
                            int id;
                            cout << "Enter expense ID to edit: ";
                            cin >> id;

                            ExpenseRecord record;
                            cout << "Enter new date (YYYY-MM-DD): ";
                            cin >> record.date;
                            cout << "Enter new category: ";
                            cin >> record.category;
                            cout << "Enter new amount: ";
                            cin >> record.amount;

                            expenseManager.editExpense(id, record);
                        }
                        else if (expenseChoice == 3) {
                            // Delete Expense
                            int id;
                            cout << "Enter expense ID to delete: ";
                            cin >> id;

                            expenseManager.deleteExpense(id);
                        }
                        else if (expenseChoice == 4) {
                            // View Expenses
                            expenseManager.displayExpenses();
                        }
                        else {
                            cout << "Invalid option.\n";
                        }
                    }
                    else if (userChoice == 3) {
                        // Budget Planning
                        string category;
                        double amount;
                        cout << "Enter category: ";
                        cin >> category;
                        cout << "Enter budget amount: ";
                        cin >> amount;

                        budgetManager.setBudget(category, amount);
                    }
                    else if (userChoice == 4) {
                        // Generate Report
                        string startDate, endDate;
                        cout << "Enter start date (YYYY-MM-DD): ";
                        cin >> startDate;
                        cout << "Enter end date (YYYY-MM-DD): ";
                        cin >> endDate;

                        reportGenerator.generateReport(incomeManager, expenseManager, startDate, endDate, username);
                    }
                    else if (userChoice == 5) {
                        // Expense Analysis
                        reportGenerator.generateExpenseChart(expenseManager, username);
                    }
                    else if (userChoice == 6) {
                        // Save data and logout
                        incomeManager.saveToFile(username);
                        expenseManager.saveToFile(username);
                        budgetManager.saveToFile(username);
                        break;
                    }
                    else {
                        cout << "Invalid option.\n";
                    }
                }
            }
        }
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
