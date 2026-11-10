// Task 7 alternative: a public data member - any code can break the Rs 50 rule
#include <iostream>

struct OpenCard { long long balance; };
int main()
{
    OpenCard c{6400};
    c.balance -= 2000;                              // any code can do this
    std::cout << "balance " << c.balance << " (below 5000: rule R1 broken)\n";
    c.balance -= 9000;
    std::cout << "balance " << c.balance << " (negative!)\n";
}
