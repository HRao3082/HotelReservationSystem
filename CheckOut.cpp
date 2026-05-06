#include "CheckOut.h"
#include "Screen.h"
#include "HotelDatabase.h"
#include "Keypad.h"
#include "PaymentTerminal.h"
#include "GuestAccount.h"
#include <string>

CheckOut::CheckOut(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad, PaymentTerminal& thePaymentTerminal)
    : Transaction(userGuestID, theScreen, theHotelDatabase), keypad(theKeypad), paymentTerminal(thePaymentTerminal) {}

void CheckOut::execute() {
    Screen& screen = getScreen();
    HotelDatabase& db = getHotelDatabase();
    
    screen.displayMessage("\nEnter room number to check out (or 0 to cancel): ");
    int roomNumber = keypad.getInput();
    
    if (roomNumber == 0) {
        screen.displayMessageLine("\nCanceling transaction...");
        return;
    }
    
    if (db.recordCheckOut(roomNumber)) {
        screen.displayMessageLine("\nCheck-out successful.");
        screen.displayMessageLine("Refunding security deposit of $50.00...");
        paymentTerminal.processPayment(-50.0);
        GuestAccount* guest = db.getGuest(getGuestID());
        if (guest != nullptr) {
            int earnedPoints = 10; // arbitrary points
            guest->addLoyaltyPoints(earnedPoints);
            screen.displayMessageLine("Stay summary: You have earned " + std::to_string(earnedPoints) + " loyalty points.");
            screen.displayMessageLine("Total loyalty points: " + std::to_string(guest->getLoyaltyPoints()));
        }
        screen.displayMessageLine("Thank you for staying with us!");
    } else {
        screen.displayMessageLine("\nCheck-out failed. Invalid room number or room is already available.");
    }
}
