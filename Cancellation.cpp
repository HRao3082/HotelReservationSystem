#include "Cancellation.h"
#include "Screen.h"
#include "HotelDatabase.h"
#include "Keypad.h"

Cancellation::Cancellation(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad)
    : Transaction(userGuestID, theScreen, theHotelDatabase), keypad(theKeypad) {}

void Cancellation::execute() {
    Screen& screen = getScreen();
    HotelDatabase& db = getHotelDatabase();
    
    screen.displayMessage("\nEnter room number to cancel booking (or 0 to exit): ");
    int roomNumber = keypad.getInput();
    
    if (roomNumber == 0) {
        screen.displayMessageLine("\nCanceling transaction...");
        return;
    }
    
    if (db.cancelBooking(roomNumber)) {
        screen.displayMessageLine("\nBooking cancelled successfully.");
        screen.displayMessageLine("A partial refund has been noted and will be processed.");
    } else {
        screen.displayMessageLine("\nCancellation failed. Please check the room number.");
    }
}
