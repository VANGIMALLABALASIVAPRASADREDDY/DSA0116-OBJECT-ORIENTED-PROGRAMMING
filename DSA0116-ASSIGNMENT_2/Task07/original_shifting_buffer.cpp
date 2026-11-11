#include <iostream>
#include <iomanip>

template <int CAPACITY>
class ShiftingTransactionAccount
{
private:
    long long accountNumber;
    double balance;
    double transactions[CAPACITY];
    int count;

public:
    ShiftingTransactionAccount(long long acc, double bal)
        : accountNumber(acc), balance(bal), count(0)
    {
        for (int i = 0; i < CAPACITY; ++i) transactions[i] = 0.0;
    }

    // O(k) linear shifting insertion
    void record(double amount)
    {
        if (count < CAPACITY)
        {
            transactions[count++] = amount;
        }
        else
        {
            for (int i = 0; i < CAPACITY - 1; ++i)
            {
                transactions[i] = transactions[i + 1]; // Linear memory shift
            }
            transactions[CAPACITY - 1] = amount;
        }
    }

    void deposit(double amount)
    {
        balance += amount;
        record(amount);
    }

    double getBalance() const { return balance; }
};

int main()
{
    ShiftingTransactionAccount<10> acc(123456789, 1000.0);
    for (int i = 1; i <= 15; ++i)
    {
        acc.deposit(100.0 * i);
    }
    std::cout << "Original Shifting Buffer test finished. Balance: " << acc.getBalance() << '\n';
    return 0;
}

