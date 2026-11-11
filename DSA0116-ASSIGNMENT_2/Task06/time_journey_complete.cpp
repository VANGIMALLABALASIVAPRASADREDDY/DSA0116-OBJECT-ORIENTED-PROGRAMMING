#include <iostream>
#include <cmath>
#include <iomanip>

class Time
{
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}

    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);

    void print() const
    {
        std::cout << std::setfill('0') << std::setw(2) << h << ":"
                  << std::setfill('0') << std::setw(2) << m;
    }
};

int minutesBetween(const Time& a, const Time& b)
{
    // TODO 1: Using the private members h and m, return the absolute difference between
    // the two times in minutes
    int totalMinsA = a.h * 60 + a.m;
    int totalMinsB = b.h * 60 + b.m;
    return std::abs(totalMinsA - totalMinsB);
}

bool earlier(const Time& a, const Time& b)
{
    // TODO 2: Return true if a is earlier in the day than b
    if (a.h != b.h)
    {
        return a.h < b.h;
    }
    return a.m < b.m;
}

int main()
{
    std::cout << "========================================================\n";
    std::cout << "  Q6: TRAIN JOURNEY PLANNER (FRIEND FUNCTIONS)          \n";
    std::cout << "========================================================\n\n";

    // Standard Expected Test Case from PDF
    Time departure(9, 45), arrival(13, 10);
    std::cout << "Primary Test Case (Departure 09:45, Arrival 13:10):\n";
    std::cout << "Output: " << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';
    std::cout << "Expected: 205 false\n\n";

    // Correctness Hand Verification Test 1: Same time twice
    std::cout << "--- Correctness Check 1: Same time twice (10:30 and 10:30) ---\n";
    Time t1(10, 30), t2(10, 30);
    std::cout << "  t1: "; t1.print(); std::cout << " | t2: "; t2.print(); std::cout << '\n';
    std::cout << "  minutesBetween(t1, t2) = " << minutesBetween(t1, t2) << " min (Expected: 0)\n";
    std::cout << "  earlier(t1, t2)        = " << std::boolalpha << earlier(t1, t2) << " (Expected: false)\n\n";

    // Correctness Hand Verification Test 2: Times on either side of noon
    std::cout << "--- Correctness Check 2: Either side of noon (11:45 and 12:15) ---\n";
    Time morning(11, 45), afternoon(12, 15);
    std::cout << "  morning: "; morning.print(); std::cout << " | afternoon: "; afternoon.print(); std::cout << '\n';
    std::cout << "  minutesBetween(morning, afternoon) = " << minutesBetween(morning, afternoon) << " min (Expected: 30)\n";
    std::cout << "  earlier(morning, afternoon)        = " << std::boolalpha << earlier(morning, afternoon) << " (Expected: true)\n";
    std::cout << "  earlier(afternoon, morning)        = " << std::boolalpha << earlier(afternoon, morning) << " (Expected: false)\n";

    return 0;
}

