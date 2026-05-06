#include "GuestAccount.h"
using namespace std;

GuestAccount::GuestAccount(int id, int p, string n, int points)
    : guestID(id), pin(p), name(n), loyaltyPoints(points) {}

bool GuestAccount::validatePIN(int userPIN) const {
    return userPIN == pin;
}

int GuestAccount::getPIN() const {
    return pin;
}

int GuestAccount::getGuestID() const {
    return guestID;
}

string GuestAccount::getName() const {
    return name;
}

int GuestAccount::getLoyaltyPoints() const {
    return loyaltyPoints;
}

void GuestAccount::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
}

void GuestAccount::deductLoyaltyPoints(int points) {
    loyaltyPoints -= points;
}
