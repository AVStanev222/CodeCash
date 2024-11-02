#ifndef INCOME_H
#define INCOME_H

#include <string>
#include <vector>

struct IncomeRecord {
    int id;
    std::string date;
    std::string category;
    double amount;
};

class IncomeManager {
private:
    std::vector<IncomeRecord> incomes;
    int nextId;

public:
    IncomeManager();
    void addIncome(const IncomeRecord& record);
    void editIncome(int id, const IncomeRecord& record);
    void deleteIncome(int id);
    void displayIncomes() const;
    void loadFromFile(const std::string& username);
    void saveToFile(const std::string& username) const;
    const std::vector<IncomeRecord>& getIncomes() const;
};

#endif // INCOME_H
