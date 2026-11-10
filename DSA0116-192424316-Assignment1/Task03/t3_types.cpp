// Task 3: sizes, limits and the problem with floating-point money
#include <climits>
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "sizeof(bool)=" << sizeof(bool) << " char=" << sizeof(char) << " int=" << sizeof(int)
              << " unsigned=" << sizeof(unsigned) << " long long=" << sizeof(long long)
              << " float=" << sizeof(float) << " double=" << sizeof(double) << '\n';
    std::cout << "INT_MAX=" << INT_MAX << "  INT_MIN=" << INT_MIN << '\n';
    std::cout << "UINT_MAX=" << UINT_MAX << "  LLONG_MAX=" << LLONG_MAX << '\n';
    std::cout << std::setprecision(17);
    std::cout << "0.1+0.2 = " << 0.1 + 0.2 << '\n';
    std::cout << "10.8*3 = " << 10.8 * 3 << "  (expected 32.4)\n";
    double sum = 0; for (int i = 0; i < 10; ++i) sum += 0.10;
    std::cout << "ten times 0.10 = " << sum << "  == 1.00 ? " << std::boolalpha << (sum == 1.00) << '\n';
    long long paise = 0; for (int i = 0; i < 10; ++i) paise += 10;
    std::cout << "ten times 10 paise = " << paise << "  == 100 ? " << (paise == 100) << '\n';
    unsigned int big = static_cast<unsigned int>(INT_MAX) + 1u;   // defined for unsigned
    std::cout << "INT_MAX + 1 as unsigned (defined) = " << big << '\n';
    std::cout << "true + 2 = " << true + 2 << ", 7 / 2.0 = " << 7 / 2.0 << ", 'A' + 1 = " << 'A' + 1 << '\n';
}
