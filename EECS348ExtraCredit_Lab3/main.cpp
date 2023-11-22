#include <iostream>
#include <iomanip>

class Account {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    Account(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    virtual ~Account() {}

    virtual void displayDetails() const {
        std::cout << "Account Details for " << getAccountType() << " (ID: " << accountNumber << "):" << std::endl;
        std::cout << "   Holder: " << accountHolder << std::endl;
        std::cout << "   Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }

    virtual std::string getAccountType() const {
        return "Account";
    }

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
        }
    }

    double getBalance() const {
        return balance;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& number, const std::string& holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    void displayDetails() const override {
        std::cout << "Account Details for " << getAccountType() << " (ID: " << accountNumber << "):" << std::endl;
        std::cout << "   Holder: " << accountHolder << std::endl;
        std::cout << "   Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "   Interest Rate: " << std::fixed << std::setprecision(2) << interestRate * 100 << "%" << std::endl;
    }

    std::string getAccountType() const override {
        return "Savings Account";
    }

    void withdraw(double amount) override {
        const double minBalance = 100;
        if (balance - amount >= minBalance) {
            balance -= amount;
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(const std::string& number, const std::string& holder, double initialBalance, double overdraft)
        : Account(number, holder, initialBalance), overdraftLimit(overdraft) {}

    void displayDetails() const override {
        std::cout << "Account Details for " << getAccountType() << " (ID: " << accountNumber << "):" << std::endl;
        std::cout << "   Holder: " << accountHolder << std::endl;
        std::cout << "   Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "   Overdraft Limit: $" << std::fixed << std::setprecision(2) << overdraftLimit << std::endl;
    }

    std::string getAccountType() const override {
        return "Current Account";
    }

    void withdraw(double amount) override {
        if (balance - amount >= -overdraftLimit) {
            balance -= amount;
        }
    }

    double getOverdraftLimit() const {
        return overdraftLimit;
    }
};

// Overload + operator for transferring money from SavingsAccount to CurrentAccount
CurrentAccount operator+(CurrentAccount current, SavingsAccount& savings) {
    double transferAmount = 300;
    if (savings.getBalance() >= transferAmount) {
        current.deposit(transferAmount);
        savings.withdraw(transferAmount);
    }
    return current;
}

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    std::cout << std::endl;

    current.displayDetails();
    std::cout << std::endl;

    savings.deposit(500);
    current.withdraw(1000);

    std::cout << "Account Details after deposit and withdrawal:" << std::endl;
    savings.displayDetails();
    std::cout << std::endl;

    current.displayDetails();
    std::cout << std::endl;

    // Transfer 300 from savings to current
    current = current + savings;

    std::cout << "Account Details after transfer:" << std::endl;
    savings.displayDetails();
    std::cout << std::endl;

    current.displayDetails();
    std::cout << std::endl;

    return 0;
}

