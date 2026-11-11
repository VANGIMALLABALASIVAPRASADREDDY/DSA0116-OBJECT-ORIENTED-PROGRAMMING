#include <iostream>
#include <iomanip>

template <int CAPACITY>
class CircularTransactionAccount
{
private:
    long long accountNumber;
    double balance;
    double buffer[CAPACITY];
    int head;  // Index of the oldest valid transaction
    int count; // Number of elements currently stored (0 to CAPACITY)

public:
    CircularTransactionAccount(long long acc, double bal)
        : accountNumber(acc), balance(bal), head(0), count(0)
    {
        for (int i = 0; i < CAPACITY; ++i) buffer[i] = 0.0;
    }

    // O(1) constant time insertion via modular arithmetic
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
            buffer[head] = amount;
            head = (head + 1) % CAPACITY; // O(1) pointer advance
        }
    }

    void deposit(double amount)
    {
        balance += amount;
        record(amount);
    }

    double getBalance() const { return balance; }

    void printMiniStatement() const
    {
        std::cout << "Mini-Statement (Last " << count << " entries):\n";
        for (int i = 0; i < count; ++i)
        {
            int idx = (head + i) % CAPACITY;
            std::cout << "  #" << (i + 1) << ": " << buffer[idx] << " INR\n";
        }
    }
};

int main()
{
    CircularTransactionAccount<10> acc(987654321, 1000.0);
    for (int i = 1; i <= 15; ++i)
    {
        acc.deposit(100.0 * i);
    }
    std::cout << "Redesigned Circular Buffer test finished. Balance: " << acc.getBalance() << '\n';
    acc.printMiniStatement();
    return 0;
}

