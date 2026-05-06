#include "Room.h"
using namespace std;

Room::Room(int number, string t, double price, bool available)
    : roomNumber(number), type(t), pricePerNight(price), isAvailable(available) {}

int Room::getRoomNumber() const {
    return roomNumber;
}

string Room::getType() const {
    return type;
}

double Room::getPrice() const {
    return pricePerNight;
}

bool Room::getAvailability() const {
    return isAvailable;
}

void Room::setAvailability(bool available) {
    isAvailable = available;
}
