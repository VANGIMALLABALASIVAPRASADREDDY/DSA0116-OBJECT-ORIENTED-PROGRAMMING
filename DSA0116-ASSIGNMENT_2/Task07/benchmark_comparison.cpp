#include <iostream>
#include <chrono>
#include <iomanip>

template <int CAPACITY>
class ShiftingAccount
{
public:
    double balance = 1000.0;
    double transactions[CAPACITY]{0.0};
    int count = 0;

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
                transactions[i] = transactions[i + 1];
            }
            transactions[CAPACITY - 1] = amount;
        }
    }

    void deposit(double amount)
    {
        balance += amount;
        record(amount);
    }

    double checksum() const
    {
        double sum = balance;
        for (int i = 0; i < count; ++i) sum += transactions[i];
        return sum;
    }
};

template <int CAPACITY>
class CircularAccount
{
public:
    double balance = 1000.0;
    double buffer[CAPACITY]{0.0};
    int head = 0;
    int count = 0;

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
            head = (head + 1) % CAPACITY;
        }
    }

    void deposit(double amount)
    {
        balance += amount;
        record(amount);
    }

    double checksum() const
    {
        double sum = balance;
        for (int i = 0; i < count; ++i) sum += buffer[i];
        return sum;
    }
};

template <int K>
void runBenchmark(int numTransactions)
{
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Testing Buffer Capacity k = " << K 
              << " (" << numTransactions << " transactions)\n";
    std::cout << "--------------------------------------------------------\n";

    // 1. Benchmark Shifting Account
    ShiftingAccount<K> shiftAcc;
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTransactions; ++i)
    {
        shiftAcc.deposit(10.0 + (i % 50));
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    volatile double sVal = shiftAcc.checksum();
    double shiftTime = std::chrono::duration<double, std::milli>(t1 - t0).count();

    // 2. Benchmark Circular Account
    CircularAccount<K> circAcc;
    auto t2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTransactions; ++i)
    {
        circAcc.deposit(10.0 + (i % 50));
    }
    auto t3 = std::chrono::high_resolution_clock::now();
    volatile double cVal = circAcc.checksum();
    double circTime = std::chrono::duration<double, std::milli>(t3 - t2).count();

    // Prevent division by zero if circTime is ultra fast
    if (circTime < 0.001) circTime = 0.001;

    std::cout << "  Original (Shifting Array) : " << std::fixed << std::setprecision(3) 
              << shiftTime << " ms (chk: " << (long long)sVal << ")\n";
    std::cout << "  Redesigned (Circular Ring): " << circTime << " ms (chk: " << (long long)cVal << ")\n";
    std::cout << "  Speedup Factor            : " << (shiftTime / circTime) << "x\n";
    double reduction = ((shiftTime - circTime) / shiftTime) * 100.0;
    if (reduction < 0.0) reduction = 0.0;
    std::cout << "  Time Reduction            : " << reduction << " %\n\n";
}

int main()
{
    const int N = 200000;
    std::cout << "========================================================\n";
    std::cout << "  DAY-4 DESIGN CHALLENGE: BENCHMARK COMPARISON          \n";
    std::cout << "  N = " << N << " Transactions per test                \n";
    std::cout << "========================================================\n\n";

    runBenchmark<10>(N);
    runBenchmark<50>(N);
    runBenchmark<100>(N);
    runBenchmark<200>(N);

    return 0;
}
