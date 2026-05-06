#include "HotelDatabase.h"
#include <fstream>
#include <iostream>

HotelDatabase::HotelDatabase() {
    loadDatabase();
}

HotelDatabase::~HotelDatabase() {
    saveDatabase();
}

void HotelDatabase::addGuest(int id, int pin, std::string name) {
    guests.push_back(GuestAccount(id, pin, name, 0));
}

void HotelDatabase::loadDatabase() {
    std::ifstream guestFile("guests.txt");
    if (guestFile.is_open()) {
        int id, pin, points;
        std::string name;
        while (guestFile >> id >> pin >> name >> points) {
            guests.push_back(GuestAccount(id, pin, name, points));
        }
        guestFile.close();
    } else {
        guests.push_back(GuestAccount(11111, 12345, "Alice", 100));
        guests.push_back(GuestAccount(22222, 67890, "Bob", 50));
    }

    std::ifstream roomFile("rooms.txt");
    if (roomFile.is_open()) {
        int num;
        std::string type;
        double price;
        bool avail;
        while (roomFile >> num >> type >> price >> avail) {
            rooms.push_back(Room(num, type, price, avail));
        }
        roomFile.close();
    } else {
        rooms.push_back(Room(101, "Single", 80.0, true));
        rooms.push_back(Room(102, "Single", 80.0, true));
        rooms.push_back(Room(201, "Double", 120.0, true));
        rooms.push_back(Room(202, "Double", 120.0, true));
        rooms.push_back(Room(301, "Suite", 250.0, true));
    }
}

void HotelDatabase::saveDatabase() const {
    std::ofstream guestFile("guests.txt");
    for (size_t i = 0; i < guests.size(); ++i) {
        guestFile << guests[i].getGuestID() << " "
                  << guests[i].getPIN() << " "
                  << guests[i].getName() << " "
                  << guests[i].getLoyaltyPoints() << "\n";
    }
    guestFile.close();

    std::ofstream roomFile("rooms.txt");
    for (size_t i = 0; i < rooms.size(); ++i) {
        roomFile << rooms[i].getRoomNumber() << " "
                 << rooms[i].getType() << " "
                 << rooms[i].getPrice() << " "
                 << rooms[i].getAvailability() << "\n";
    }
    roomFile.close();
}

GuestAccount* HotelDatabase::getGuest(int userGuestID) {
    for (size_t i = 0; i < guests.size(); ++i) {
        if (guests[i].getGuestID() == userGuestID) {
            return &guests[i];
        }
    }
    return nullptr;
}

bool HotelDatabase::authenticateGuest(int userGuestID, int userPIN) {
    GuestAccount* guest = getGuest(userGuestID);
    if (guest != nullptr) {
        return guest->validatePIN(userPIN);
    }
    return false;
}

std::vector<Room> HotelDatabase::getAvailableRooms() const {
    std::vector<Room> availableRooms;
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].getAvailability()) {
            availableRooms.push_back(rooms[i]);
        }
    }
    return availableRooms;
}

Room* HotelDatabase::getRoomByNumber(int roomNumber) {
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].getRoomNumber() == roomNumber) {
            return &rooms[i];
        }
    }
    return nullptr;
}

bool HotelDatabase::bookRoom(int userGuestID, int roomNumber) {
    Room* room = getRoomByNumber(roomNumber);
    if (room != nullptr && room->getAvailability()) {
        room->setAvailability(false);
        return true;
    }
    return false;
}

bool HotelDatabase::cancelBooking(int roomNumber) {
    Room* room = getRoomByNumber(roomNumber);
    if (room != nullptr && !room->getAvailability()) {
        room->setAvailability(true);
        return true;
    }
    return false;
}

bool HotelDatabase::recordCheckIn(int roomNumber) {
    Room* room = getRoomByNumber(roomNumber);
    if (room != nullptr && !room->getAvailability()) {
        return true;
    }
    return false;
}

bool HotelDatabase::recordCheckOut(int roomNumber) {
    Room* room = getRoomByNumber(roomNumber);
    if (room != nullptr && !room->getAvailability()) {
        room->setAvailability(true);
        return true;
    }
    return false;
}
