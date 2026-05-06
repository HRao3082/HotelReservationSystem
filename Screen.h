#ifndef SCREEN_H
#define SCREEN_H
#include <string>

class Screen {
public:
    void displayMessage(std::string message) const;
    void displayMessageLine(std::string message) const;
    void displayCurrencyAmount(double amount) const;
};
#endif
