// Task 9: test table - inputs, expected result, actual result for every case
#include <chrono>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

// smartcard.h : the card owns its balance; nothing else can change it
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

class SmartCard {
    long long balance_;                                // private: only the card changes it
public:
    explicit SmartCard(long long openingPaise = 0) : balance_{openingPaise < 0 ? 0 : openingPaise} {}
    long long balance() const { return balance_; }
    bool canTravel(long long fare) const { return fare >= 0 && balance_ - fare >= MIN_BALANCE_PAISE; }
    bool deduct(long long fare) { if (!canTravel(fare)) return false; balance_ -= fare; return true; }
    bool recharge(long long paise) { if (paise <= 0) return false; balance_ += paise; return true; }
};

// validate.h : input validation helpers
// whole-string integer parse with range check; false for letters, trailing junk or out-of-range
inline bool parseIntInRange(const std::string& s, int lo, int hi, int& out)
{
    std::istringstream in(s);
    int v{};
    if (!(in >> v) || !in.eof() || v < lo || v > hi) return false;
    out = v; return true;
}
inline bool toZone(int n, Zone& z)
{
    if (n < 0 || n >= static_cast<int>(Zone::Count)) return false;
    z = static_cast<Zone>(n); return true;
}

struct Case { const char* name; Zone z; Category c; int h, m; long long expected; };
int main()
{
    const Case cases[] = {
        {"Inner off-peak",        Zone::Inner,  Category::Regular, 12,  0, 1000},
        {"Middle off-peak",       Zone::Middle, Category::Regular, 12,  0, 2000},
        {"Outer off-peak",        Zone::Outer,  Category::Regular, 12,  0, 3000},
        {"Inner peak",            Zone::Inner,  Category::Regular,  9,  0, 1200},
        {"Middle peak",           Zone::Middle, Category::Regular, 18,  0, 2400},
        {"Outer peak",            Zone::Outer,  Category::Regular,  8, 30, 3600},
        {"Boundary 08:00 peak",   Zone::Outer,  Category::Regular,  8,  0, 3600},
        {"Boundary 09:59 peak",   Zone::Outer,  Category::Regular,  9, 59, 3600},
        {"Boundary 10:00 off",    Zone::Outer,  Category::Regular, 10,  0, 3000},
        {"Boundary 17:00 peak",   Zone::Outer,  Category::Regular, 17,  0, 3600},
        {"Boundary 19:59 peak",   Zone::Outer,  Category::Regular, 19, 59, 3600},
        {"Boundary 20:00 off",    Zone::Outer,  Category::Regular, 20,  0, 3000},
        {"Student Inner off-peak",Zone::Inner,  Category::Student, 12,  0,  750},
        {"Student Outer peak",    Zone::Outer,  Category::Student,  9,  0, 2700},
        {"Senior Outer off-peak", Zone::Outer,  Category::Senior,  12,  0, 1500},
        {"Senior Inner peak",     Zone::Inner,  Category::Senior,   9,  0,  600},
    };
    int failed = 0;
    const auto t0 = std::chrono::steady_clock::now();
    for (const Case& c : cases) {
        const long long got = fareFor(c.z, c.c, c.h, c.m);
        if (got != c.expected) { ++failed; std::cout << "FAIL " << c.name << ": expected " << c.expected << " got " << got << '\n'; }
    }
    const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t0).count();
    const int total = static_cast<int>(sizeof(cases) / sizeof(cases[0]));

    // card rules: exactly Rs 50 must remain
    int checks = 0;
    auto check = [&](const char* what, bool ok) { ++checks; if (!ok) { ++failed; std::cout << "FAIL " << what << '\n'; } };
    SmartCard card{8000};
    check("leaves exactly Rs 50 -> allowed", card.canTravel(3000));
    check("leaves Rs 49.99 -> denied", !card.canTravel(3001));
    check("deduct exact boundary", card.deduct(3000) && card.balance() == 5000);
    check("deduct below minimum refused", !card.deduct(1) && card.balance() == 5000);
    check("negative recharge rejected", !card.recharge(-100) && card.balance() == 5000);
    check("zero recharge rejected", !card.recharge(0));
    check("recharge accepted", card.recharge(2000) && card.balance() == 7000);
    check("negative opening balance clamped to 0", SmartCard{-500}.balance() == 0);

    // invalid input cases
    int v = 0; Zone z{};
    check("letters rejected", !parseIntInRange("abc", 0, 23, v));
    check("trailing junk rejected", !parseIntInRange("12abc", 0, 23, v));
    check("out of range rejected", !parseIntInRange("25", 0, 23, v));
    check("valid accepted", parseIntInRange("9", 0, 23, v) && v == 9);
    check("unknown zone 5 rejected", !toZone(5, z));
    check("negative zone rejected", !toZone(-1, z));
    check("zone 2 accepted", toZone(2, z) && z == Zone::Outer);

    // five journeys totalled by hand: Inner 12:00 regular 1000 + Middle 09:00 regular 2400
    // + Outer 12:00 student 2250 + Outer 18:00 senior 1800 + Inner 12:00 senior 500 = 7950
    long long total5 = fareFor(Zone::Inner, Category::Regular, 12, 0) + fareFor(Zone::Middle, Category::Regular, 9, 0)
                     + fareFor(Zone::Outer, Category::Student, 12, 0) + fareFor(Zone::Outer, Category::Senior, 18, 0)
                     + fareFor(Zone::Inner, Category::Senior, 12, 0);
    check("hand-calculated total of 5 journeys = 7950", total5 == 7950);

    std::cout << total << " fare cases + " << checks << " rule checks, " << failed << " failed; table occupies "
              << sizeof(cases) << " bytes; loop took " << ns << " ns\n";
    return failed ? 1 : 0;
}
