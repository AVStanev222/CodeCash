#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

struct ExpenseRecord {
    int id;
    std::string date;
    std::string category;
    double amount;
};

class ExpenseManager {
private:
    std::vector<ExpenseRecord> expenses;
    int nextId;

public:
    ExpenseManager();
    void addExpense(const ExpenseRecord& record);
    void editExpense(int id, const ExpenseRecord& record);
    void deleteExpense(int id);
    void displayExpenses() const;
    void loadFromFile(const std::string& username);
    void saveToFile(const std::string& username) const;
    const std::vector<ExpenseRecord>& getExpenses() const;
};

#endif // EXPENSE_H
