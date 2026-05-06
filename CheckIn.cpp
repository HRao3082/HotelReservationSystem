#include "CheckIn.h"
#include "Screen.h"
#include "HotelDatabase.h"
#include "Keypad.h"
#include "KeyCardDispenser.h"
#include "PaymentTerminal.h"

CheckIn::CheckIn(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad, KeyCardDispenser& theKeyCardDispenser, PaymentTerminal& thePaymentTerminal)
    : Transaction(userGuestID, theScreen, theHotelDatabase), keypad(theKeypad), keyCardDispenser(theKeyCardDispenser), paymentTerminal(thePaymentTerminal) {}

void CheckIn::execute() {
    Screen& screen = getScreen();
    HotelDatabase& db = getHotelDatabase();
    
    screen.displayMessage("\nEnter room number to check in (or 0 to cancel): ");
    int roomNumber = keypad.getInput();
    
    if (roomNumber == 0) {
        screen.displayMessageLine("\nCanceling transaction...");
        return;
    }
    
    if (db.recordCheckIn(roomNumber)) {
        screen.displayMessageLine("\nCheck-in successful.");
        screen.displayMessageLine("Processing security deposit of $50.00...");
        paymentTerminal.processPayment(50.0);
        screen.displayMessageLine("Issuing key card...");
        if (keyCardDispenser.isKeyCardIssued()) {
            screen.displayMessageLine("Please take your key card from the dispenser.");
        }
    } else {
        screen.displayMessageLine("\nCheck-in failed. Please verify your booking.");
    }
}
