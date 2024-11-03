#include "Utils.h"
#include <regex>
#include <iostream>
using namespace std;
bool IsValidDate(const string& date) {
    regex datePattern("\\d{4}-\\d{2}-\\d{2}");
    return regex_match(date, datePattern);
}

bool IsValidAmount(const string& amountStr) {
    regex amountPattern("^\\d+(\\.\\d{1,2})?$");
    return regex_match(amountStr, amountPattern);
}

void ClearScreen() {
    // Platform-specific screen clear
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
