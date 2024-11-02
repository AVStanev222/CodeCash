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

    cout << "Добре дошли в приложението за управление на лични финанси!\n";

    while (true) {
        cout << "\n1. Регистрация\n2. Вход\n3. Изход\nИзберете опция: ";
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Въведете потребителско име: ";
            cin >> username;
            cout << "Въведете парола: ";
            cin >> password;

            user.registerUser(username, password);
        }
        else if (choice == 2) {
            string username, password;
            cout << "Въведете потребителско име: ";
            cin >> username;
            cout << "Въведете парола: ";
            cin >> password;

            if (user.loginUser(username, password)) {
                incomeManager.loadFromFile(username);
                expenseManager.loadFromFile(username);
                budgetManager.loadFromFile(username);

                int userChoice;
                while (true) {
                    cout << "\n--- Меню на потребителя ---\n";
                    cout << "1. Управление на приходи\n";
                    cout << "2. Управление на разходи\n";
                    cout << "3. Планиране на бюджет\n";
                    cout << "4. Генериране на отчет\n";
                    cout << "5. Анализ на разходите\n";
                    cout << "6. Изход\n";
                    cout << "Изберете опция: ";
                    cin >> userChoice;

                    if (userChoice == 1) {
                        // Управление на приходи
                        int incomeChoice;
                        cout << "\n1. Добавяне на приход\n2. Редактиране на приход\n3. Изтриване на приход\n4. Показване на приходи\nИзберете опция: ";
                        cin >> incomeChoice;

                        if (incomeChoice == 1) {
                            // Добавяне на приход
                            IncomeRecord record;
                            cout << "Въведете дата (ГГГГ-ММ-ДД): ";
                            cin >> record.date;
                            cout << "Въведете категория: ";
                            cin >> record.category;
                            cout << "Въведете сума: ";
                            cin >> record.amount;

                            incomeManager.addIncome(record);
                        }
                        else if (incomeChoice == 2) {
                            // Редактиране на приход
                            int id;
                            cout << "Въведете ID на прихода за редактиране: ";
                            cin >> id;

                            IncomeRecord record;
                            cout << "Въведете нова дата (ГГГГ-ММ-ДД): ";
                            cin >> record.date;
                            cout << "Въведете нова категория: ";
                            cin >> record.category;
                            cout << "Въведете нова сума: ";
                            cin >> record.amount;

                            incomeManager.editIncome(id, record);
                        }
                        else if (incomeChoice == 3) {
                            // Изтриване на приход
                            int id;
                            cout << "Въведете ID на прихода за изтриване: ";
                            cin >> id;

                            incomeManager.deleteIncome(id);
                        }
                        else if (incomeChoice == 4) {
                            // Показване на приходи
                            incomeManager.displayIncomes();
                        }
                        else {
                            cout << "Невалидна опция.\n";
                        }
                    }
                    else if (userChoice == 2) {
                        // Управление на разходи
                        int expenseChoice;
                        cout << "\n1. Добавяне на разход\n2. Редактиране на разход\n3. Изтриване на разход\n4. Показване на разходи\nИзберете опция: ";
                        cin >> expenseChoice;

                        if (expenseChoice == 1) {
                            // Добавяне на разход
                            ExpenseRecord record;
                            cout << "Въведете дата (ГГГГ-ММ-ДД): ";
                            cin >> record.date;
                            cout << "Въведете категория: ";
                            cin >> record.category;
                            cout << "Въведете сума: ";
                            cin >> record.amount;

                            expenseManager.addExpense(record);
                            // Проверка на бюджета
                            double total = 0.0;
                            for (const auto& expense : expenseManager.getExpenses()) {
                                if (expense.category == record.category) {
                                    total += expense.amount;
                                }
                            }
                            budgetManager.checkBudget(record.category, total);
                        }
                        else if (expenseChoice == 2) {
                            // Редактиране на разход
                            int id;
                            cout << "Въведете ID на разхода за редактиране: ";
                            cin >> id;

                            ExpenseRecord record;
                            cout << "Въведете нова дата (ГГГГ-ММ-ДД): ";
                            cin >> record.date;
                            cout << "Въведете нова категория: ";
                            cin >> record.category;
                            cout << "Въведете нова сума: ";
                            cin >> record.amount;

                            expenseManager.editExpense(id, record);
                        }
                        else if (expenseChoice == 3) {
                            // Изтриване на разход
                            int id;
                            cout << "Въведете ID на разхода за изтриване: ";
                            cin >> id;

                            expenseManager.deleteExpense(id);
                        }
                        else if (expenseChoice == 4) {
                            // Показване на разходи
                            expenseManager.displayExpenses();
                        }
                        else {
                            cout << "Невалидна опция.\n";
                        }
                    }
                    else if (userChoice == 3) {
                        // Планиране на бюджет
                        string category;
                        double amount;
                        cout << "Въведете категория: ";
                        cin >> category;
                        cout << "Въведете бюджетна сума: ";
                        cin >> amount;

                        budgetManager.setBudget(category, amount);
                    }
                    else if (userChoice == 4) {
                        // Генериране на отчет
                        string startDate, endDate;
                        cout << "Въведете начална дата (ГГГГ-ММ-ДД): ";
                        cin >> startDate;
                        cout << "Въведете крайна дата (ГГГГ-ММ-ДД): ";
                        cin >> endDate;

                        reportGenerator.generateReport(incomeManager, expenseManager, startDate, endDate, username);
                    }
                    else if (userChoice == 5) {
                        // Анализ на разходите
                        reportGenerator.generateExpenseChart(expenseManager, username);
                    }
                    else if (userChoice == 6) {
                        // Запис на данните и изход
                        incomeManager.saveToFile(username);
                        expenseManager.saveToFile(username);
                        budgetManager.saveToFile(username);
                        break;
                    }
                    else {
                        cout << "Невалидна опция.\n";
                    }
                }
            }
        }
        else if (choice == 3) {
            cout << "Довиждане!\n";
            break;
        }
        else {
            cout << "Невалидна опция.\n";
        }
    }

    return 0;
}
