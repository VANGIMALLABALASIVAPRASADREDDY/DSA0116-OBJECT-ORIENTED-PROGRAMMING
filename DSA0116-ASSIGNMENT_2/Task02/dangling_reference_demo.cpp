#include <iostream>

// DANGEROUS FUNCTION: Returns a reference to a local stack variable
// This will trigger GCC compiler warning: [-Wreturn-local-addr]
#pragma GCC diagnostic push
#pragma GCC diagnostic warning "-Wreturn-local-addr"
int& returnLocalVariableReference()
{
    int localMark = 100; // Local variable allocated on this function's stack frame
    return localMark;   // DANGER: Stack frame is deallocated upon function return!
}
#pragma GCC diagnostic pop

int main()
{
    std::cout << "========================================================\n";
    std::cout << "  Q2: DEMONSTRATING DANGER OF RETURNING LOCAL REFERENCE \n";
    std::cout << "========================================================\n\n";

    std::cout << "Explanation of Compiler Warning [-Wreturn-local-addr]:\n";
    std::cout << "1. 'localMark' is created on the activation record (stack frame).\n";
    std::cout << "2. When returnLocalVariableReference() returns, the stack frame is deallocated.\n";
    std::cout << "3. Returning a reference creates a DANGLING REFERENCE to dead memory.\n";
    std::cout << "4. Any dereference in modern C++ (GCC 13) is undefined behaviour and\n";
    std::cout << "   causes invalid memory reads, corruption, or trap halts.\n";
    std::cout << "5. Compile-time evidence: GCC emits warning: reference to local variable returned!\n";

    return 0;
}
