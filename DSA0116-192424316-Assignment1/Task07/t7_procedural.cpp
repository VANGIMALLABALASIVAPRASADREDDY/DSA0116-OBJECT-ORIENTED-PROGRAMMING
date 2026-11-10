// Task 7: procedural version - global data, free functions, caller must remember the rule
#include <cstddef>
#include <iostream>

// fare_rules.h : the ONLY place where fares, percentages and limits are written

enum class Zone { Inner, Middle, Outer, Count };           // Count = number of zones
enum class Category { Regular, Student, Senior };

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};      // Rs 10, 20, 30
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int STUDENT_CONCESSION_PERCENT = 25;              // assumption A1
constexpr int SENIOR_CONCESSION_PERCENT = 50;               // assumption A1
constexpr long long MIN_BALANCE_PAISE = 5000;               // Rs 50 must remain

// peak windows in minutes since midnight, half-open [start, end)
constexpr int PEAK_AM_START = 8 * 60,  PEAK_AM_END = 10 * 60;
constexpr int PEAK_PM_START = 17 * 60, PEAK_PM_END = 20 * 60;

// integer percentage, rounded half-up (no floating point anywhere)
constexpr long long pctOf(long long paise, int percent) { return (paise * percent + 50) / 100; }

constexpr bool isPeak(int hour, int minute)
{
    const int t = hour * 60 + minute;
    return (t >= PEAK_AM_START && t < PEAK_AM_END) || (t >= PEAK_PM_START && t < PEAK_PM_END);
}

// concession first, then the peak surcharge on the concession-adjusted fare
constexpr long long fareFor(Zone z, Category c, int hour, int minute)
{
    long long f = BASE_PAISE[static_cast<std::size_t>(z)];
    if (c == Category::Student)     f -= pctOf(f, STUDENT_CONCESSION_PERCENT);
    else if (c == Category::Senior) f -= pctOf(f, SENIOR_CONCESSION_PERCENT);
    if (isPeak(hour, minute))       f += pctOf(f, PEAK_SURCHARGE_PERCENT);
    return f;
}

long long g_balance = 10000;                       // anyone can change this
long long g_collected = 0;
void deductRaw(long long f) { g_balance -= f; g_collected += f; }   // no check inside
int main()
{
    long long f = fareFor(Zone::Outer, Category::Regular, 9, 0);   // 3600
    if (g_balance - f >= MIN_BALANCE_PAISE) deductRaw(f);          // caller remembered
    std::cout << "after trip 1: " << g_balance << " paise\n";
    f = fareFor(Zone::Middle, Category::Regular, 12, 0);           // 2000: 6400-2000=4400 < 5000
    deductRaw(f);                                                  // caller FORGOT the check
    std::cout << "after trip 2: " << g_balance << " paise  (rule broken: below 5000)\n";
    g_balance = -300;                                              // any code can do this
    std::cout << "after direct write: " << g_balance << " paise\n";
}
