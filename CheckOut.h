#ifndef CHECKOUT_H
#define CHECKOUT_H
#include "Transaction.h"

class Keypad;
class PaymentTerminal;

class CheckOut : public Transaction {
private:
    Keypad& keypad;
    PaymentTerminal& paymentTerminal;
public:
    CheckOut(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad, PaymentTerminal& thePaymentTerminal);
    virtual void execute() override;
};
#endif
