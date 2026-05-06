#ifndef PAYMENTTERMINAL_H
#define PAYMENTTERMINAL_H

class PaymentTerminal {
private:
    double balance;
public:
    PaymentTerminal();
    void processPayment(double amount);
    bool isPaymentAccepted(double amount);
};
#endif
