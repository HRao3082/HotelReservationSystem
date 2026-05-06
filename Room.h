#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
private:
    int roomNumber;
    std::string type;
    double pricePerNight;
    bool isAvailable;
public:
    Room(int number, std::string t, double price, bool available);
    int getRoomNumber() const;
    std::string getType() const;
    double getPrice() const;
    bool getAvailability() const;
    void setAvailability(bool available);
};
#endif
