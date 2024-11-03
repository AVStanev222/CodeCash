#include "Main.h"
#include <iostream>
using namespace std;
int main() {
    User user;
    Finance finance;
    Budget budget;
    Reports reports;
    int choice;

    while (true) {
        ClearScreen();
        cout << "Welcome to Personal Finance Manager\n";
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (user.Register()) {
                cout << "Registration successful!\n";
            }
        }
        else if (choice == 2) {
            if (user.Login()) {
                finance.LoadFinanceData(user.username);
                budget.LoadBudgetData(user.username);

                while (true) {
                    ClearScreen();
                    cout << "1. Manage Incomes\n2. Manage Expenses\n";
                    cout << "3. Budget Planning\n4. Generate Reports\n";
                    cout << "5. Logout\nEnter choice: ";
                    cin >> choice;

                    if (choice == 1) {
                        finance.AddIncome();
                    }
                    else if (choice == 2) {
                        finance.AddExpense();
                    }
                    else if (choice == 3) {
                        budget.SetBudget();
                    }
                    else if (choice == 4) {
                        reports.GenerateReport(finance);
                    }
                    else if (choice == 5) {
                        finance.SaveFinanceData(user.username);
                        budget.SaveBudgetData(user.username);
                        break;
                    }
                }
            }
        }
        else if (choice == 3) {
            break;
        }
    }
    return 0;
}