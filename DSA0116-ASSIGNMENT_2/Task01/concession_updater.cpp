#include <iostream>
#include <iomanip>

// 1. Pass by value: operates strictly on a local stack copy
void applyConcessionByValue(long long fee, int percent)
{
    fee -= (fee * percent) / 100;
    std::cout << "  [Inside applyConcessionByValue] fee calculated = " << fee << '\n';
}

// 2. Pass by reference: operates directly on caller's variable via alias
void applyConcessionByReference(long long& fee, int percent)
{
    fee -= (fee * percent) / 100;
    std::cout << "  [Inside applyConcessionByReference] fee updated = " << fee << '\n';
}

// 3. Pass by pointer: operates directly on caller's variable via memory address
void applyConcessionByPointer(long long* fee, int percent)
{
    if (fee != nullptr)
    {
        *fee -= (*fee * percent) / 100;
        std::cout << "  [Inside applyConcessionByPointer] fee updated = " << *fee << '\n';
    }
}

int main()
{
    std::cout << "====================================================\n";
    std::cout << "  HOSTEL FEE CONCESSION UPDATER (Q1 DEMONSTRATION)  \n";
    std::cout << "====================================================\n\n";

    long long fee = 45000;
    std::cout << "Initial Base Hostel Fee: " << fee << " INR\n\n";

    // Call 1: By Value (Merit Concession 10%)
    std::cout << "--- 1. Applying Merit Concession (10%) by VALUE ---\n";
    std::cout << "Predicted fee after call: 45000 (No change to caller's fee)\n";
    applyConcessionByValue(fee, 10);
    std::cout << "Actual fee stored for student: " << fee << " INR (VERIFIED: UNCHANGED)\n\n";

    // Call 2: By Reference (Sports Concession 15%)
    std::cout << "--- 2. Applying Sports Concession (15%) by REFERENCE ---\n";
    std::cout << "Predicted fee after call: 38250 (45000 - 15% = 38250)\n";
    applyConcessionByReference(fee, 15);
    std::cout << "Actual fee stored for student: " << fee << " INR (VERIFIED: UPDATED)\n\n";

    // Call 3: By Pointer (Single Parent Concession 25%)
    std::cout << "--- 3. Applying Single Parent Concession (25%) by POINTER ---\n";
    std::cout << "Predicted fee after call: 28688 (38250 - 25% = 28687.5 -> 28688)\n";
    applyConcessionByPointer(&fee, 25);
    std::cout << "Actual fee stored for student: " << fee << " INR (VERIFIED: UPDATED)\n\n";

    std::cout << "Final Fee Stored: " << fee << " INR\n";
    return 0;
}

