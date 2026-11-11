#include <iostream>
#include <chrono>
#include <cmath>

class TimeBench
{
    int h, m;

public:
    TimeBench(int hh, int mm) : h(hh), m(mm) {}

    // Non-inline declaration
    friend int minutesBetweenNoInline(const TimeBench& a, const TimeBench& b);
    
    // Explicit inline declaration
    friend inline int minutesBetweenInline(const TimeBench& a, const TimeBench& b)
    {
        return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m));
    }

    friend inline bool earlierInline(const TimeBench& a, const TimeBench& b)
    {
        return (a.h != b.h) ? (a.h < b.h) : (a.m < b.m);
    }
};

// Non-inline definition in separate linkage
__attribute__((noinline))
int minutesBetweenNoInline(const TimeBench& a, const TimeBench& b)
{
    return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m));
}

int main()
{
    const int ITERATIONS = 10000000;
    TimeBench t1(8, 25);
    TimeBench t2(17, 45);

    std::cout << "========================================================\n";
    std::cout << "  Q6 GROWTH INVESTIGATION: 10,000,000 CALLS BENCHMARK   \n";
    std::cout << "========================================================\n";
    std::cout << "Iterations: " << ITERATIONS << " calls\n\n";

    // 1. Benchmark Non-Inline Function
    auto start1 = std::chrono::high_resolution_clock::now();
    volatile long long sum1 = 0;
    for (int i = 0; i < ITERATIONS; ++i)
    {
        sum1 += minutesBetweenNoInline(t1, t2);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    double timeNoInline = std::chrono::duration<double, std::milli>(end1 - start1).count();

    // 2. Benchmark Inline Function
    auto start2 = std::chrono::high_resolution_clock::now();
    volatile long long sum2 = 0;
    for (int i = 0; i < ITERATIONS; ++i)
    {
        sum2 += minutesBetweenInline(t1, t2);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    double timeInline = std::chrono::duration<double, std::milli>(end2 - start2).count();

    std::cout << "Results:\n";
    std::cout << "  Without inline (noinline): " << timeNoInline << " ms (Checksum: " << sum1 << ")\n";
    std::cout << "  With inline              : " << timeInline << " ms (Checksum: " << sum2 << ")\n";
    if (timeInline > 0.0001)
    {
        std::cout << "  Speedup Factor           : " << (timeNoInline / timeInline) << "x\n";
    }

    return 0;
}

