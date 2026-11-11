#include <iostream>
#include <vector>

int main()
{
    std::cout << "========================================================\n";
    std::cout << "  Q2 CHANGED CONDITION: STD::VECTOR REALLOCATION DEMO   \n";
    std::cout << "========================================================\n\n";

    std::vector<int> marks;
    marks.reserve(2); // Set initial capacity to 2

    marks.push_back(88);
    marks.push_back(92);

    std::cout << "Initial Vector State:\n";
    std::cout << "  Size: " << marks.size() << ", Capacity: " << marks.capacity() << '\n';
    std::cout << "  Address of marks[0]: " << (void*)&marks[0] << '\n';
    std::cout << "  Address of marks[1]: " << (void*)&marks[1] << '\n';

    // Obtain a reference to element 1 before vector grows
    int& highestRef = marks[1];
    const int* originalAddress = &highestRef;

    std::cout << "\nCaptured reference 'highestRef' to marks[1]: " << highestRef << '\n';
    std::cout << "  Memory location stored in reference: " << (void*)originalAddress << '\n';

    // Allocate an intervening block on the heap to prevent in-place buffer expansion
    int* interveningBlock = new int[100];
    interveningBlock[0] = 999;

    // Now push elements to exceed capacity and force memory reallocation to a new heap block
    std::cout << "\n--> Adding 10 elements to trigger vector memory relocation...\n";
    for (int i = 0; i < 10; ++i)
    {
        marks.push_back(70 + i);
    }

    std::cout << "New Vector State after growth:\n";
    std::cout << "  Size: " << marks.size() << ", New Capacity: " << marks.capacity() << '\n';
    std::cout << "  New Address of marks[0]: " << (void*)&marks[0] << '\n';
    std::cout << "  New Address of marks[1]: " << (void*)&marks[1] << '\n';

    std::cout << "\nAnalysis of Reference Invalidation:\n";
    std::cout << "  Original memory location of reference: " << (void*)originalAddress << '\n';
    std::cout << "  Current memory location of marks[1] : " << (void*)&marks[1] << '\n';

    if (originalAddress != &marks[1])
    {
        std::cout << "  STATUS: MEMORY ADDRESS HAS CHANGED!\n";
        std::cout << "  'highestRef' is now a DANGLING REFERENCE pointing to deallocated memory.\n";
        std::cout << "  Mutating through 'highestRef' corrupts memory or causes crashes!\n";
    }

    delete[] interveningBlock;
    return 0;
}
