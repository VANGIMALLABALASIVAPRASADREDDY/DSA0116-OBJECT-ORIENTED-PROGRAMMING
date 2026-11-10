// Task 4: corrected code (brace initialisation and static_cast)
#include <iostream>

int main()
{
    const int a{7}, b{2};
    const double c{static_cast<double>(a) / b};           // 3.5, not 3
    const char ch{static_cast<char>('A' + 2)};            // brace init would reject an unchecked narrowing
    const bool flag{5 != 0};                              // explicit comparison instead of int -> bool
    const unsigned int u{1};
    const int s{-1};
    const bool less{s < 0 || static_cast<unsigned>(s) < u}; // compare signed and unsigned safely
    std::cout << c << ' ' << ch << ' ' << std::boolalpha << flag << ' ' << less << '\n';
    // int x{3.7};   // error: narrowing conversion of '3.7e+0' from 'double' to 'int'
}
