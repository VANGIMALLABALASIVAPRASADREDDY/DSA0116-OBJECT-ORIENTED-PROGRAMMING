// Task 12: the MODIFIED design - fourth zone, weekend discount, monthly pass
#include <cstddef>
#include <iostream>

// fare_v2.h (revised rules): 4th zone, weekend discount, monthly pass
enum class Zone { Inner, Middle, Outer, Airport, Count };
enum class Category { Regular, Student, Senior };
enum class Day { Mon, Tue, Wed, Thu, Fri, Sat, Sun };

constexpr long long BASE_PAISE[] = {1000, 2000, 3000, 6000};          // Airport Rs 60 added
static_assert(sizeof(BASE_PAISE) / sizeof(BASE_PAISE[0]) == static_cast<std::size_t>(Zone::Count),
              "fare table must have exactly one entry per zone");
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;                           // new named constant
constexpr int STUDENT_CONCESSION_PERCENT = 25, SENIOR_CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_AM_START = 480, PEAK_AM_END = 600, PEAK_PM_START = 1020, PEAK_PM_END = 1200;

constexpr long long pctOf(long long paise, int percent) { return (paise * percent + 50) / 100; }
constexpr bool isPeak(int h, int m)
{ const int t = h * 60 + m; return (t >= PEAK_AM_START && t < PEAK_AM_END) || (t >= PEAK_PM_START && t < PEAK_PM_END); }
constexpr bool isWeekend(Day d) { return d == Day::Sat || d == Day::Sun; }

struct Journey { Zone zone; Category cat; Day day; int hour, minute, year, month; };

// monthly pass: unlimited journeys whose zone is one of two chosen zones, in one calendar month
class Pass {
    Zone a_, b_; int year_, month_;
public:
    constexpr Pass(Zone a, Zone b, int year, int month) : a_{a}, b_{b}, year_{year}, month_{month} {}
    constexpr bool covers(const Journey& j) const
    { return j.year == year_ && j.month == month_ && (j.zone == a_ || j.zone == b_); }
};

// concession first, then EITHER the weekend discount OR the peak surcharge (never both)
constexpr long long fare(const Journey& j)
{
    long long f = BASE_PAISE[static_cast<std::size_t>(j.zone)];
    if (j.cat == Category::Student)      f -= pctOf(f, STUDENT_CONCESSION_PERCENT);
    else if (j.cat == Category::Senior)  f -= pctOf(f, SENIOR_CONCESSION_PERCENT);
    if (isWeekend(j.day))                f -= pctOf(f, WEEKEND_DISCOUNT_PERCENT);
    else if (isPeak(j.hour, j.minute))   f += pctOf(f, PEAK_SURCHARGE_PERCENT);
    return f;
}

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long p = 0) : balance_{p < 0 ? 0 : p} {}
    long long balance() const { return balance_; }
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
};
enum class Outcome { OpenFreePass, OpenPaid, Denied };
Outcome gate(SmartCard& card, const Pass* pass, const Journey& j)       // pass journeys never touch the balance
{
    if (pass && pass->covers(j)) return Outcome::OpenFreePass;
    return card.deduct(fare(j)) ? Outcome::OpenPaid : Outcome::Denied;
}
static const char* name(Outcome o)
{ return o == Outcome::OpenFreePass ? "OPEN (pass)" : o == Outcome::OpenPaid ? "OPEN (paid)" : "DENIED"; }
int main()
{
    std::cout << "Airport off-peak (regular, Wed 12:00): " << fare({Zone::Airport, Category::Regular, Day::Wed, 12, 0, 2026, 11}) << " (expect 6000)\n";
    std::cout << "Airport Saturday 09:00, student: " << fare({Zone::Airport, Category::Student, Day::Sat, 9, 0, 2026, 11}) << " (expect 4050 = 6000-25%-10%)\n";
    std::cout << "Outer Saturday 09:00, regular (no peak surcharge on weekend): " << fare({Zone::Outer, Category::Regular, Day::Sat, 9, 0, 2026, 11}) << " (expect 2700)\n";
    std::cout << "Outer Monday 09:00, regular (peak): " << fare({Zone::Outer, Category::Regular, Day::Mon, 9, 0, 2026, 11}) << " (expect 3600)\n";

    const Pass pass{Zone::Inner, Zone::Middle, 2026, 11};
    SmartCard card{1000};                                                // Rs 10 only
    const Journey j1{Zone::Middle, Category::Regular, Day::Tue, 12, 0, 2026, 11};
    const Journey j2{Zone::Outer,  Category::Regular, Day::Tue, 12, 0, 2026, 11};
    const Journey j3{Zone::Middle, Category::Regular, Day::Tue, 12, 0, 2026, 12};   // next month: pass expired
    std::cout << "Middle journey, pass holder, balance Rs 10: " << name(gate(card, &pass, j1)) << ", balance " << card.balance() << '\n';
    std::cout << "Outer journey (not covered), balance Rs 10: " << name(gate(card, &pass, j2)) << ", balance " << card.balance() << '\n';
    std::cout << "Middle journey next month (pass expired): " << name(gate(card, &pass, j3)) << ", balance " << card.balance() << '\n';
}
