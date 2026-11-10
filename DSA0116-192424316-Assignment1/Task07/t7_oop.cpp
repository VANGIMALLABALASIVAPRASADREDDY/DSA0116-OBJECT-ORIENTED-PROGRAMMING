// Task 7: object-oriented version (uses smartcard.h)
#include <cstddef>
#include <iostream>

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

int main()
{
    SmartCard card{10000};
    long long f = fareFor(Zone::Outer, Category::Regular, 9, 0);
    std::cout << "trip 1 (Outer, 09:00) fare " << f << ": " << (card.deduct(f) ? "OK" : "DENIED")
              << ", balance " << card.balance() << '\n';
    f = fareFor(Zone::Middle, Category::Regular, 12, 0);
    std::cout << "trip 2 (Middle, 12:00) fare " << f << ": " << (card.deduct(f) ? "OK" : "DENIED")
              << ", balance " << card.balance() << '\n';
    std::cout << "recharge -500: " << (card.recharge(-500) ? "accepted" : "rejected") << ", balance " << card.balance() << '\n';
    std::cout << "recharge 2000: " << (card.recharge(2000) ? "accepted" : "rejected") << ", balance " << card.balance() << '\n';
    // card.balance_ = -300;   // error: 'long long SmartCard::balance_' is private within this context
}
