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

    cout << "����� ����� � ������������ �� ���������� �� ����� �������!\n";

    while (true) {
        cout << "\n1. �����������\n2. ����\n3. �����\n�������� �����: ";
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "�������� ������������� ���: ";
            cin >> username;
            cout << "�������� ������: ";
            cin >> password;

            user.registerUser(username, password);
        }
        else if (choice == 2) {
            string username, password;
            cout << "�������� ������������� ���: ";
            cin >> username;
            cout << "�������� ������: ";
            cin >> password;

            if (user.loginUser(username, password)) {
                incomeManager.loadFromFile(username);
                expenseManager.loadFromFile(username);
                budgetManager.loadFromFile(username);

                int userChoice;
                while (true) {
                    cout << "\n--- ���� �� ����������� ---\n";
                    cout << "1. ���������� �� �������\n";
                    cout << "2. ���������� �� �������\n";
                    cout << "3. ��������� �� ������\n";
                    cout << "4. ���������� �� �����\n";
                    cout << "5. ������ �� ���������\n";
                    cout << "6. �����\n";
                    cout << "�������� �����: ";
                    cin >> userChoice;

                    if (userChoice == 1) {
                        // ���������� �� �������
                        int incomeChoice;
                        cout << "\n1. �������� �� ������\n2. ����������� �� ������\n3. ��������� �� ������\n4. ��������� �� �������\n�������� �����: ";
                        cin >> incomeChoice;

                        if (incomeChoice == 1) {
                            // �������� �� ������
                            IncomeRecord record;
                            cout << "�������� ���� (����-��-��): ";
                            cin >> record.date;
                            cout << "�������� ���������: ";
                            cin >> record.category;
                            cout << "�������� ����: ";
                            cin >> record.amount;

                            incomeManager.addIncome(record);
                        }
                        else if (incomeChoice == 2) {
                            // ����������� �� ������
                            int id;
                            cout << "�������� ID �� ������� �� �����������: ";
                            cin >> id;

                            IncomeRecord record;
                            cout << "�������� ���� ���� (����-��-��): ";
                            cin >> record.date;
                            cout << "�������� ���� ���������: ";
                            cin >> record.category;
                            cout << "�������� ���� ����: ";
                            cin >> record.amount;

                            incomeManager.editIncome(id, record);
                        }
                        else if (incomeChoice == 3) {
                            // ��������� �� ������
                            int id;
                            cout << "�������� ID �� ������� �� ���������: ";
                            cin >> id;

                            incomeManager.deleteIncome(id);
                        }
                        else if (incomeChoice == 4) {
                            // ��������� �� �������
                            incomeManager.displayIncomes();
                        }
                        else {
                            cout << "��������� �����.\n";
                        }
                    }
                    else if (userChoice == 2) {
                        // ���������� �� �������
                        int expenseChoice;
                        cout << "\n1. �������� �� ������\n2. ����������� �� ������\n3. ��������� �� ������\n4. ��������� �� �������\n�������� �����: ";
                        cin >> expenseChoice;

                        if (expenseChoice == 1) {
                            // �������� �� ������
                            ExpenseRecord record;
                            cout << "�������� ���� (����-��-��): ";
                            cin >> record.date;
                            cout << "�������� ���������: ";
                            cin >> record.category;
                            cout << "�������� ����: ";
                            cin >> record.amount;

                            expenseManager.addExpense(record);
                            // �������� �� �������
                            double total = 0.0;
                            for (const auto& expense : expenseManager.getExpenses()) {
                                if (expense.category == record.category) {
                                    total += expense.amount;
                                }
                            }
                            budgetManager.checkBudget(record.category, total);
                        }
                        else if (expenseChoice == 2) {
                            // ����������� �� ������
                            int id;
                            cout << "�������� ID �� ������� �� �����������: ";
                            cin >> id;

                            ExpenseRecord record;
                            cout << "�������� ���� ���� (����-��-��): ";
                            cin >> record.date;
                            cout << "�������� ���� ���������: ";
                            cin >> record.category;
                            cout << "�������� ���� ����: ";
                            cin >> record.amount;

                            expenseManager.editExpense(id, record);
                        }
                        else if (expenseChoice == 3) {
                            // ��������� �� ������
                            int id;
                            cout << "�������� ID �� ������� �� ���������: ";
                            cin >> id;

                            expenseManager.deleteExpense(id);
                        }
                        else if (expenseChoice == 4) {
                            // ��������� �� �������
                            expenseManager.displayExpenses();
                        }
                        else {
                            cout << "��������� �����.\n";
                        }
                    }
                    else if (userChoice == 3) {
                        // ��������� �� ������
                        string category;
                        double amount;
                        cout << "�������� ���������: ";
                        cin >> category;
                        cout << "�������� �������� ����: ";
                        cin >> amount;

                        budgetManager.setBudget(category, amount);
                    }
                    else if (userChoice == 4) {
                        // ���������� �� �����
                        string startDate, endDate;
                        cout << "�������� ������� ���� (����-��-��): ";
                        cin >> startDate;
                        cout << "�������� ������ ���� (����-��-��): ";
                        cin >> endDate;

                        reportGenerator.generateReport(incomeManager, expenseManager, startDate, endDate, username);
                    }
                    else if (userChoice == 5) {
                        // ������ �� ���������
                        reportGenerator.generateExpenseChart(expenseManager, username);
                    }
                    else if (userChoice == 6) {
                        // ����� �� ������� � �����
                        incomeManager.saveToFile(username);
                        expenseManager.saveToFile(username);
                        budgetManager.saveToFile(username);
                        break;
                    }
                    else {
                        cout << "��������� �����.\n";
                    }
                }
            }
        }
        else if (choice == 3) {
            cout << "���������!\n";
            break;
        }
        else {
            cout << "��������� �����.\n";
        }
    }

    return 0;
}
