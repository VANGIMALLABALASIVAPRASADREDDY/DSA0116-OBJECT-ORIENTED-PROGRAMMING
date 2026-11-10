// Task 2: #define versus constexpr
#include <iostream>

#define DOUBLE_IT(x) x * 2
constexpr int doubleIt(int x) { return x * 2; }
int main()
{
    std::cout << "macro     DOUBLE_IT(3 + 4)  = " << DOUBLE_IT(3 + 4) << "   (expands to 3 + 4 * 2)\n";
    std::cout << "constexpr doubleIt(3 + 4)   = " << doubleIt(3 + 4) << '\n';
}
