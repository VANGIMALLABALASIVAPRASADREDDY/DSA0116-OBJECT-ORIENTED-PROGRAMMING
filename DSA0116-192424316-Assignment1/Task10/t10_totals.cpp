// Task 10: network totals for 20,000 / 500,000 / 3,000,000 journeys:
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>

// exact long long paise versus double rupees versus a 32-bit int accumulator
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
    const long long sizes[] = {20000, 500000, 3000000};
    for (long long n : sizes) {
        std::mt19937 rng(12345);                                   // fixed seed
        std::uniform_int_distribution<int> zone(0, 2), minute(0, 24 * 60 - 1), cat(0, 99);
        long long exact = 0; double rupees = 0.0; std::int32_t wrapped = 0; long long firstOverflow = -1;
        for (long long i = 1; i <= n; ++i) {
            const int k = cat(rng);
            const Category c = k < 70 ? Category::Regular : (k < 90 ? Category::Student : Category::Senior);
            const int mm = minute(rng);
            const long long f = fareFor(static_cast<Zone>(zone(rng)), c, mm / 60, mm % 60);
            if (firstOverflow < 0 && exact + f > INT32_MAX) firstOverflow = i;
            exact += f;
            rupees += f / 100.0;
            wrapped = static_cast<std::int32_t>(static_cast<std::uint32_t>(wrapped) + static_cast<std::uint32_t>(f)); // wrap-around, no UB
        }
        std::cout << std::setw(9) << n << "  exact paise " << std::setw(12) << exact
                  << "  double Rs " << std::fixed << std::setprecision(6) << rupees
                  << "  diff " << rupees - exact / 100.0
                  << "  int32 " << wrapped << "  first overflow at journey " << firstOverflow << '\n'
                  << std::defaultfloat;
    }
}
