// Task 5 alternative: peak check by lookup table bool peak[24] built at compile time
#include <iostream>

constexpr bool peakExpr(int h) { return (h >= 8 && h < 10) || (h >= 17 && h < 20); }
struct Table { bool v[24]; constexpr Table() : v{} { for (int h = 0; h < 24; ++h) v[h] = peakExpr(h); } };
constexpr Table T{};          // built at compile time; the check is T.v[hour]
int main()
{
    int disagree = 0;
    for (int h = 0; h < 24; ++h) if (T.v[h] != peakExpr(h)) ++disagree;
    std::cout << "table and expression disagree on " << disagree << " hours; table size " << sizeof(T) << " bytes\n";
}
