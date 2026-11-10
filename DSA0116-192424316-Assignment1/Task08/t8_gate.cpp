// Task 8: the gate program - safe input with cin, formatted money output
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>

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

// read one int in [lo, hi]; keeps asking until valid; returns false only on end of input
bool readInt(const char* prompt, int lo, int hi, int& out)
{
    while (true) {
        std::cout << prompt << std::flush;
        if (std::cin >> out) {
            if (out >= lo && out <= hi) return true;
            std::cout << "  -> out of range (" << lo << ".." << hi << "), try again\n";
        } else if (std::cin.eof()) {
            return false;
        } else {
            std::cout << "  -> not a number, try again\n";
            std::cin.clear();                                                    // clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the bad line
        }
    }
}
void printMoney(long long paise)
{
    std::cout << std::setw(5) << paise / 100 << '.' << std::setw(2) << std::setfill('0') << paise % 100 << std::setfill(' ');
}
int main()
{
    SmartCard card{10000};                       // Rs 100.00
    int recharge = 0;
    while (true) {                               // negative recharge is rejected, 0 means none
        if (!readInt("Recharge in whole rupees (0 for none): ", -1000000, 1000000, recharge)) return 0;
        if (recharge < 0) { std::cout << "  -> negative recharge rejected\n"; continue; }
        break;
    }
    if (recharge > 0) card.recharge(recharge * 100LL);
    std::cout << "Opening balance: Rs "; printMoney(card.balance()); std::cout << "\n\n";
    std::cout << "No  Zone    Time           Fare       Balance  Status\n";
    int served = 0, denied = 0, n = 0; long long collected = 0;
    while (true) {
        int z, h, m, c;
        if (!readInt("Zone (0 Inner, 1 Middle, 2 Outer): ", 0, 2, z)) break;
        if (!readInt("Hour (0-23): ", 0, 23, h)) break;
        if (!readInt("Minute (0-59): ", 0, 59, m)) break;
        if (!readInt("Category (0 Regular, 1 Student, 2 Senior): ", 0, 2, c)) break;
        const long long f = fareFor(static_cast<Zone>(z), static_cast<Category>(c), h, m);
        const bool ok = card.deduct(f);
        ++n;
        std::cout << '\n' << n << "   " << z << "       " << std::setw(2) << std::setfill('0') << h << ':'
                  << std::setw(2) << m << std::setfill(' ') << "   ";
        printMoney(f); std::cout << "  "; printMoney(card.balance());
        std::cout << "   " << (ok ? "OPEN" : "DENIED (low balance)") << "\n\n";
        if (ok) { ++served; collected += f; } else ++denied;
    }
    std::cout << "\nJourneys served: " << served << ", denied: " << denied << '\n';
    std::cout << "Collected: Rs " << collected / 100 << '.' << std::setw(2) << std::setfill('0') << collected % 100 << std::setfill(' ') << '\n';
    if (served > 0) std::cout << "Average fare: " << std::fixed << std::setprecision(2) << collected / 100.0 / served << " Rs\n";
    std::cout << "Closing balance: Rs " << card.balance() / 100 << '.' << std::setw(2) << std::setfill('0') << card.balance() % 100 << '\n';
}
