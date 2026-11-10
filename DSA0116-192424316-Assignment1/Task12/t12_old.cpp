// Task 12: the ORIGINAL design meets the new requirement (4th zone) - expect a -Wswitch warning
#include <iostream>

enum class Zone { Inner, Middle, Outer, Airport };      // Airport added
long long fare(Zone z, bool peak)
{
    long long base = 0;
    switch (z) {                                        // no case for Airport
        case Zone::Inner:  base = 1000; break;
        case Zone::Middle: base = 2000; break;
        case Zone::Outer:  base = 3000; break;
    }
    if (peak) base += base * 20 / 100;
    return base;
}
int main()
{
    std::cout << "Airport off-peak fare: " << fare(Zone::Airport, false) << " paise (should be 6000)\n";
    std::cout << "Airport on a Saturday at 09:00 (peak=true passed): " << fare(Zone::Airport, true) << " paise\n";
    const long long balance = 1000, f = 2000;           // pass holder: journey should be free
    std::cout << "Middle journey for a pass holder: old deduct rule says canTravel = "
              << std::boolalpha << (balance - f >= 5000) << " (should be free and allowed)\n";
}
