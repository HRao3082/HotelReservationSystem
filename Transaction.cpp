#include "Transaction.h"

Transaction::Transaction(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase)
    : guestID(userGuestID), screen(theScreen), hotelDatabase(theHotelDatabase) {}

int Transaction::getGuestID() const {
    return guestID;
}

Screen& Transaction::getScreen() const {
    return screen;
}

HotelDatabase& Transaction::getHotelDatabase() const {
    return hotelDatabase;
}
