#ifndef CHECKIN_H
#define CHECKIN_H
#include "Transaction.h"

class Keypad;
class KeyCardDispenser;
class PaymentTerminal;

class CheckIn : public Transaction {
private:
    Keypad& keypad;
    KeyCardDispenser& keyCardDispenser;
    PaymentTerminal& paymentTerminal;
public:
    CheckIn(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad, KeyCardDispenser& theKeyCardDispenser, PaymentTerminal& thePaymentTerminal);
    virtual void execute() override;
};
#endif
