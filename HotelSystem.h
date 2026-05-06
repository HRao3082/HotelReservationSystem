#ifndef HOTELSYSTEM_H
#define HOTELSYSTEM_H
#include "Screen.h"
#include "Keypad.h"
#include "PaymentTerminal.h"
#include "KeyCardDispenser.h"
#include "HotelDatabase.h"

class Transaction;

class HotelSystem {
private:
    bool guestAuthenticated;
    bool systemRunning;
    int currentGuestID;
    Screen screen;
    Keypad keypad;
    PaymentTerminal paymentTerminal;
    KeyCardDispenser keyCardDispenser;
    HotelDatabase hotelDatabase;

    void authenticateGuest();
    void performTransactions();
    int displayMainMenu() const;
    Transaction* createTransaction(int type);

public:
    HotelSystem();
    void run();
};
#endif
