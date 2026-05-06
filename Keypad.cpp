#include <iostream>
#include <limits>
#include <string>
#include "Keypad.h"
using namespace std;

int Keypad::getInput() const {
    int input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    return input;
}

string Keypad::getStringInput() const {
    string input;
    cin >> input;
    return input;
}
