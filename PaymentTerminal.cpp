#include "PaymentTerminal.h"

PaymentTerminal::PaymentTerminal() : balance(50000.0) {}

void PaymentTerminal::processPayment(double amount) {
    balance += amount;
}

bool PaymentTerminal::isPaymentAccepted(double amount) {
    return true; // We accept all payments for simulation
}
