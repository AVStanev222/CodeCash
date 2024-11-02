#ifndef BUDGET_H
#define BUDGET_H

#include <string>
#include <map>

class BudgetManager {
private:
    std::map<std::string, double> categoryBudgets;

public:
    BudgetManager();
    void setBudget(const std::string& category, double amount);
    void checkBudget(const std::string& category, double currentTotal);
    void displayBudgets() const;
    void loadFromFile(const std::string& username);
    void saveToFile(const std::string& username) const;
    double getBudgetForCategory(const std::string& category) const;
};

#endif // BUDGET_H
