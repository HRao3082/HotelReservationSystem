#ifndef CANCELLATION_H
#define CANCELLATION_H
#include "Transaction.h"

class Keypad;

class Cancellation : public Transaction {
private:
    Keypad& keypad;
public:
    Cancellation(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad);
    virtual void execute() override;
};
#endif
