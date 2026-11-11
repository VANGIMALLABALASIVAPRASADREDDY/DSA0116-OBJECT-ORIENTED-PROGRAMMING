#include <iostream>
#include <iomanip>
#include <string>

// Alternative implementation using a CIRCULAR BUFFER
class CircularSavingsAccount
{
private:
    static const int CAPACITY = 10;
    long long accountNumber;
    double balance;
    double buffer[CAPACITY]; // Circular ring buffer
    int head;                // Points to oldest valid transaction
    int count;               // Current number of stored transactions (0 to CAPACITY)

public:
    CircularSavingsAccount(long long accNum, double initialBal)
        : accountNumber(accNum), balance(initialBal), head(0), count(0)
    {
        for (int i = 0; i < CAPACITY; ++i) buffer[i] = 0.0;
    }

    void deposit(double amount)
    {
        if (amount <= 0) return;
        balance += amount;
        record(amount);
    }

    bool withdraw(double amount)
    {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        record(-amount);
        return true;
    }

    // O(1) Circular Insertion: NO elements shifted!
    void record(double amount)
    {
        if (count < CAPACITY)
        {
            int insertIdx = (head + count) % CAPACITY;
            buffer[insertIdx] = amount;
            count++;
        }
        else
        {
            // When full, overwrite oldest item at head and advance head pointer!
            buffer[head] = amount;
            head = (head + 1) % CAPACITY; // O(1) pointer advance
        }
    }

    void miniStatement() const
    {
        std::cout << "\n--- CIRCULAR BUFFER MINI-STATEMENT (Account: " << accountNumber << ") ---\n";
        std::cout << "Balance: " << std::fixed << std::setprecision(2) << balance << " INR\n";
        std::cout << "Displaying last " << count << " transactions (O(1) insertion architecture):\n";
        for (int i = 0; i < count; ++i)
        {
            int idx = (head + i) % CAPACITY;
            double tx = buffer[idx];
            std::cout << "  [" << (i + 1) << "] " << (tx >= 0 ? "+ " : "- ") 
                      << (tx >= 0 ? tx : -tx) << " INR (physical index: " << idx << ")\n";
        }
        std::cout << "--------------------------------------------------------------------\n\n";
    }
};

int main()
{
    std::cout << "========================================================\n";
    std::cout << "  Q4: CIRCULAR BUFFER SAVINGS ACCOUNT DEMONSTRATION     \n";
    std::cout << "========================================================\n\n";

    CircularSavingsAccount acc(987654321012LL, 10000.0);

    for (int i = 1; i <= 10; ++i)
    {
        acc.deposit(100.0 * i);
    }
    acc.miniStatement();

    std::cout << "Adding 11th and 12th transactions to Circular Buffer (Zero Shifting Cost):\n";
    acc.deposit(1111.0);
    acc.withdraw(2222.0);
    acc.miniStatement();

    return 0;
}

