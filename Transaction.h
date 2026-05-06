#ifndef TRANSACTION_H
#define TRANSACTION_H

class Screen;
class HotelDatabase;

class Transaction {
private:
    int guestID;
    Screen& screen;
    HotelDatabase& hotelDatabase;
public:
    Transaction(int userGuestID, Screen& theScreen, HotelDatabase& theHotelDatabase);
    virtual ~Transaction() = default;
    int getGuestID() const;
    Screen& getScreen() const;
    HotelDatabase& getHotelDatabase() const;
    virtual void execute() = 0;
};
#endif
