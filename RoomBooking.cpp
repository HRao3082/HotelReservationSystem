#include "RoomBooking.h"
#include "Screen.h"
#include "HotelDatabase.h"
#include "Keypad.h"
#include "PaymentTerminal.h"
#include "Room.h"
#include <string>
#include <vector>

RoomBooking::RoomBooking(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase, Keypad& theKeypad, PaymentTerminal& thePaymentTerminal)
    : Transaction(userGuestID, theScreen, theHotelDatabase), keypad(theKeypad), paymentTerminal(thePaymentTerminal), selectedRoomNumber(0), numberOfNights(0) {}

void RoomBooking::execute() {
    Screen& screen = getScreen();
    HotelDatabase& db = getHotelDatabase();
    
    screen.displayMessageLine("\nRoom Filters:");
    screen.displayMessageLine("1 - Show All Rooms");
    screen.displayMessageLine("2 - Single");
    screen.displayMessageLine("3 - Double");
    screen.displayMessageLine("4 - Suite");
    screen.displayMessage("Select filter: ");
    int filter = keypad.getInput();
    
    std::string typeFilter = "All";
    if (filter == 2) typeFilter = "Single";
    else if (filter == 3) typeFilter = "Double";
    else if (filter == 4) typeFilter = "Suite";

    screen.displayMessageLine("\nAvailable Rooms:");
    std::vector<Room> available = db.getAvailableRooms();
    bool found = false;
    
    for (size_t i = 0; i < available.size(); ++i) {
        if (typeFilter == "All" || available[i].getType() == typeFilter) {
            screen.displayMessage("Room " + std::to_string(available[i].getRoomNumber()) + " (" + available[i].getType() + ") - ");
            screen.displayCurrencyAmount(available[i].getPrice());
            screen.displayMessageLine(" per night");
            found = true;
        }
    }
    
    if (!found) {
        screen.displayMessageLine("No rooms match your filter.");
        return;
    }
    
    screen.displayMessage("\nEnter room number to book (or 0 to cancel): ");
    selectedRoomNumber = keypad.getInput();
    
    if (selectedRoomNumber == 0) {
        screen.displayMessageLine("\nCanceling transaction...");
        return;
    }
    
    Room* room = db.getRoomByNumber(selectedRoomNumber);
    if (room != nullptr && room->getAvailability()) {
        screen.displayMessage("\nEnter number of nights: ");
        numberOfNights = keypad.getInput();
        
        double totalCost = room->getPrice() * numberOfNights;
        screen.displayMessage("\nTotal cost: ");
        screen.displayCurrencyAmount(totalCost);
        screen.displayMessageLine("");
        
        screen.displayMessage("Processing payment...\n");
        if (paymentTerminal.isPaymentAccepted(totalCost)) {
            paymentTerminal.processPayment(totalCost);
            db.bookRoom(getGuestID(), selectedRoomNumber);
            screen.displayMessageLine("Booking confirmed! You may now check in.");
        } else {
            screen.displayMessageLine("Payment failed. Booking canceled.");
        }
    } else {
        screen.displayMessageLine("Invalid room selection or room is not available.");
    }
}
