#ifndef ROOMBOOKING_H
#define ROOMBOOKING_H
#include "Transaction.h"

class Keypad;
class PaymentTerminal;

class RoomBooking : public Transaction {
private:
    int selectedRoomNumber;
    int numberOfNights;
    Keypad& keypad;
    PaymentTerminal& paymentTerminal;
public:
    RoomBooking(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad, PaymentTerminal& thePaymentTerminal);
    virtual void execute() override;
};
#endif
