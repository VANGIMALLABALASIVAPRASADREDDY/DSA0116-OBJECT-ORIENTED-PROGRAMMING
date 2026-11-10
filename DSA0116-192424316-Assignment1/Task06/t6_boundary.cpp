// Task 6: journeys at exactly 10 AM and 8 PM (and the minute before/after each window)
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

int main()
{
    const int times[][2] = {{7,59},{8,0},{9,59},{10,0},{16,59},{17,0},{19,59},{20,0}};
    for (const auto& t : times)
        std::cout << (t[0] < 10 ? "0" : "") << t[0] << ':' << (t[1] < 10 ? "0" : "") << t[1]
                  << "  peak=" << std::boolalpha << isPeak(t[0], t[1])
                  << "  Outer regular fare=" << fareFor(Zone::Outer, Category::Regular, t[0], t[1]) << " paise\n";
}
