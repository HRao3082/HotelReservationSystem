#include "HotelSystem.h"
#include "Transaction.h"
#include "RoomBooking.h"
#include "CheckIn.h"
#include "CheckOut.h"
#include "Cancellation.h"
#include <string>

enum MenuOption { ROOM_BOOKING = 1, CHECK_IN, CHECK_OUT, CANCELLATION, EXIT };

HotelSystem::HotelSystem() 
    : guestAuthenticated(false), currentGuestID(0), systemRunning(true) {}

void HotelSystem::run() {
    while (systemRunning) {
        while (!guestAuthenticated && systemRunning) {
            screen.displayMessageLine("\nWelcome to the Hotel Reservation System!");
            authenticateGuest();
        }
        
        if (!systemRunning) break;

        performTransactions();
        
        guestAuthenticated = false;
        currentGuestID = 0;
        screen.displayMessageLine("\nThank you! Goodbye!");
    }
}

void HotelSystem::authenticateGuest() {
    screen.displayMessageLine("\n1 - Login to existing account");
    screen.displayMessageLine("2 - Create a new account");
    screen.displayMessageLine("3 - Shutdown system");
    screen.displayMessage("Enter a choice: ");
    int choice = keypad.getInput();
    
    if (choice == 3) {
        screen.displayMessage("Enter Admin PIN: ");
        int adminPIN = keypad.getInput();
        if (adminPIN == 99999) {
            systemRunning = false;
            screen.displayMessageLine("\nSystem shutting down gracefully...");
            return;
        }
    } else if (choice == 2) {
        screen.displayMessage("\nEnter a new Guest ID (e.g. 55555): ");
        int newID = keypad.getInput();
        screen.displayMessage("Enter a new PIN: ");
        int newPIN = keypad.getInput();
        screen.displayMessage("Enter your first name: ");
        std::string newName = keypad.getStringInput();
        
        hotelDatabase.addGuest(newID, newPIN, newName);
        screen.displayMessageLine("\nAccount created successfully! You are now logged in.");
        screen.displayMessageLine("Welcome " + newName + "! You currently have 0 loyalty points.");
        currentGuestID = newID;
        guestAuthenticated = true;
    } else if (choice == 1) {
        screen.displayMessage("\nPlease enter your Guest ID: ");
        int guestID = keypad.getInput();
        screen.displayMessage("Enter your PIN: ");
        int pin = keypad.getInput();
        
        guestAuthenticated = hotelDatabase.authenticateGuest(guestID, pin);
        
        if (guestAuthenticated) {
            currentGuestID = guestID;
            GuestAccount* guest = hotelDatabase.getGuest(guestID);
            if (guest != nullptr) {
                screen.displayMessageLine("\nWelcome back! You currently have " + std::to_string(guest->getLoyaltyPoints()) + " loyalty points.");
            }
        } else {
            screen.displayMessageLine("Invalid Guest ID or PIN. Please try again.");
        }
    } else {
        screen.displayMessageLine("Invalid choice.");
    }
}

void HotelSystem::performTransactions() {
    Transaction* currentTransaction = nullptr;
    bool userExited = false;
    
    while (!userExited) {
        int mainMenuSelection = displayMainMenu();
        
        switch (mainMenuSelection) {
            case ROOM_BOOKING:
            case CHECK_IN:
            case CHECK_OUT:
            case CANCELLATION:
                currentTransaction = createTransaction(mainMenuSelection);
                if (currentTransaction != nullptr) {
                    currentTransaction->execute();
                    delete currentTransaction;
                }
                break;
            case EXIT:
                screen.displayMessageLine("\nExiting the system...");
                userExited = true;
                break;
            default:
                screen.displayMessageLine("\nYou did not enter a valid selection. Try again.");
                break;
        }
    }
}

int HotelSystem::displayMainMenu() const {
    screen.displayMessageLine("\nMain menu:");
    screen.displayMessageLine("1 - Book a Room");
    screen.displayMessageLine("2 - Check In");
    screen.displayMessageLine("3 - Check Out");
    screen.displayMessageLine("4 - Cancel Reservation");
    screen.displayMessageLine("5 - Exit");
    screen.displayMessage("Enter a choice: ");
    return keypad.getInput();
}

Transaction* HotelSystem::createTransaction(int type) {
    Transaction* tempPtr = nullptr;
    
    switch (type) {
        case ROOM_BOOKING:
            tempPtr = new RoomBooking(currentGuestID, screen, hotelDatabase, keypad, paymentTerminal);
            break;
        case CHECK_IN:
            tempPtr = new CheckIn(currentGuestID, screen, hotelDatabase, keypad, keyCardDispenser, paymentTerminal);
            break;
        case CHECK_OUT:
            tempPtr = new CheckOut(currentGuestID, screen, hotelDatabase, keypad, paymentTerminal);
            break;
        case CANCELLATION:
            tempPtr = new Cancellation(currentGuestID, screen, hotelDatabase, keypad);
            break;
    }
    
    return tempPtr;
}
