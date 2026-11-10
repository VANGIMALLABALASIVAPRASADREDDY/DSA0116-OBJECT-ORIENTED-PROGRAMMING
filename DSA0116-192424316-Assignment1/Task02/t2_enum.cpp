// Task 2: plain enum versus enum class
#include <iostream>

enum Colour { Red };                  // plain enum: converts silently to int, leaks its names
enum class Zone { Inner, Middle, Outer };
int main()
{
    int a = Red + 1;                                  // compiles: Red silently becomes 0
    std::cout << "plain enum Red + 1 = " << a << '\n';
    // Zone z = Zone::Inner;  int b = z + 1;         // error: no match for operator+ (enum class)
    int b = static_cast<int>(Zone::Inner) + 1;       // enum class needs an explicit cast
    std::cout << "enum class Inner + 1 (explicit cast) = " << b << '\n';
}
