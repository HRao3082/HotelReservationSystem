#ifndef KEYPAD_H
#define KEYPAD_H
#include <string>

class Keypad {
public:
    int getInput() const;
    std::string getStringInput() const;
};
#endif
