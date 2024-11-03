#pragma once

#include "Finance.h"

class Reports {
public:
    void GenerateReport(const Finance& finance);
    void AnalyzeExpenses(const Finance& finance);
};
