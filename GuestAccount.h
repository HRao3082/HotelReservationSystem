#ifndef GUESTACCOUNT_H
#define GUESTACCOUNT_H
#include <string>

class GuestAccount {
private:
    int guestID;
    int pin;
    std::string name;
    int loyaltyPoints;
public:
    GuestAccount(int id, int p, std::string n, int points);
    bool validatePIN(int userPIN) const;
    int getPIN() const;
    int getGuestID() const;
    std::string getName() const;
    int getLoyaltyPoints() const;
    void addLoyaltyPoints(int points);
    void deductLoyaltyPoints(int points);
};
#endif
