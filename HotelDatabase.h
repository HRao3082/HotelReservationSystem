#ifndef HOTELDATABASE_H
#define HOTELDATABASE_H
#include <vector>
#include "GuestAccount.h"
#include "Room.h"

class HotelDatabase {
private:
    std::vector<GuestAccount> guests;
    std::vector<Room> rooms;
    void loadDatabase();
    void saveDatabase() const;
public:
    HotelDatabase();
    ~HotelDatabase();
    void addGuest(int id, int pin, std::string name);
    bool authenticateGuest(int userGuestID, int userPIN);
    GuestAccount* getGuest(int userGuestID);
    std::vector<Room> getAvailableRooms() const;
    Room* getRoomByNumber(int roomNumber);
    bool bookRoom(int userGuestID, int roomNumber);
    bool cancelBooking(int roomNumber);
    bool recordCheckIn(int roomNumber);
    bool recordCheckOut(int roomNumber);
};
#endif
