#include <iostream>
#include <iomanip>
#include <string>

class SavingsAccount
{
private:
    static const int MAX_TX = 10;
    long long accountNumber;
    double balance;
    double transactions[MAX_TX]; // Fixed array for last 10 transactions
    int count;                   // Number of transactions currently stored (0 to 10)

public:
    // Constructor defined outside using scope resolution
    SavingsAccount(long long accNum, double initialBalance);

    // Member function defined INSIDE the class specification: deposit()
    void deposit(double amount)
    {
        if (amount <= 0)
        {
            std::cout << "Invalid deposit amount: " << amount << '\n';
            return;
        }
        balance += amount;
        recordTransaction(amount); // positive indicates deposit
        std::cout << "Deposited: " << std::fixed << std::setprecision(2) << amount 
                  << " | Current Balance: " << balance << '\n';
    }

    // Member functions defined OUTSIDE the class using scope resolution operator (::)
    bool withdraw(double amount);
    void miniStatement() const;

private:
    void recordTransaction(double amount);
};

// Constructor defined outside class using scope resolution operator
SavingsAccount::SavingsAccount(long long accNum, double initialBalance)
    : accountNumber(accNum), balance(initialBalance), count(0)
{
    for (int i = 0; i < MAX_TX; ++i)
    {
        transactions[i] = 0.0;
    }
}

// Private helper to record transaction via SHIFTING ARRAY
void SavingsAccount::recordTransaction(double amount)
{
    if (count < MAX_TX)
    {
        transactions[count++] = amount;
    }
    else
    {
        // 11th transaction arrives: shift elements left (discard oldest at index 0)
        // Cost: O(MAX_TX) memory copy operations
        for (int i = 0; i < MAX_TX - 1; ++i)
        {
            transactions[i] = transactions[i + 1];
        }
        transactions[MAX_TX - 1] = amount;
    }
}

// Member function defined outside: withdraw()
bool SavingsAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid withdrawal amount: " << amount << '\n';
        return false;
    }
    if (amount > balance)
    {
        std::cout << "Declined: Insufficient funds for withdrawal of " << amount 
                  << " (Balance: " << balance << ")\n";
        return false;
    }
    balance -= amount;
    recordTransaction(-amount); // negative indicates withdrawal
    std::cout << "Withdrew : " << std::fixed << std::setprecision(2) << amount 
              << " | Current Balance: " << balance << '\n';
    return true;
}

// Member function defined outside: miniStatement()
void SavingsAccount::miniStatement() const
{
    std::cout << "\n========================================\n";
    std::cout << "         ATM MINI-STATEMENT             \n";
    std::cout << "========================================\n";
    std::cout << "Account Number: " << accountNumber << '\n';
    std::cout << "Current Balance: " << std::fixed << std::setprecision(2) << balance << " INR\n";
    std::cout << "Last " << count << " Transaction(s):\n";
    std::cout << "----------------------------------------\n";
    std::cout << " #  | Type       | Amount (INR)\n";
    std::cout << "----+------------+----------------------\n";
    for (int i = 0; i < count; ++i)
    {
        double tx = transactions[i];
        std::string type = (tx >= 0) ? "DEPOSIT   " : "WITHDRAWAL";
        double absAmt = (tx >= 0) ? tx : -tx;
        std::cout << std::setw(2) << (i + 1) << " | " << type << " | "
                  << std::setw(10) << absAmt << '\n';
    }
    std::cout << "========================================\n\n";
}

int main()
{
    std::cout << "========================================================\n";
    std::cout << "  Q4: SAVINGS ACCOUNT MINI-STATEMENT (SHIFTING ARRAY)   \n";
    std::cout << "========================================================\n\n";

    SavingsAccount acc(100234567890LL, 5000.0);

    // Execute 10 initial transactions
    std::cout << "--- Executing First 10 Transactions ---\n";
    acc.deposit(1000.0);  // 1
    acc.withdraw(500.0);  // 2
    acc.deposit(2500.0);  // 3
    acc.withdraw(1200.0); // 4
    acc.deposit(800.0);   // 5
    acc.withdraw(300.0);  // 6
    acc.deposit(1500.0);  // 7
    acc.withdraw(700.0);  // 8
    acc.deposit(2000.0);  // 9
    acc.withdraw(450.0);  // 10

    std::cout << "\nMini-statement after 10 transactions (Buffer Full):\n";
    acc.miniStatement();

    // Now execute 11th, 12th, and 13th transactions (triggering array shifting)
    std::cout << "--- Executing 11th, 12th, and 13th Transactions (Triggering Shift) ---\n";
    std::cout << "-> 11th Transaction arrives: oldest transaction (+1000.0) is discarded.\n";
    acc.deposit(3500.0);  // 11
    std::cout << "-> 12th Transaction arrives: oldest transaction (-500.0) is discarded.\n";
    acc.withdraw(900.0);  // 12
    std::cout << "-> 13th Transaction arrives: oldest transaction (+2500.0) is discarded.\n";
    acc.deposit(4000.0);  // 13

    std::cout << "\nMini-statement after 13 total transactions (Oldest 3 Discarded):\n";
    acc.miniStatement();

    return 0;
}

