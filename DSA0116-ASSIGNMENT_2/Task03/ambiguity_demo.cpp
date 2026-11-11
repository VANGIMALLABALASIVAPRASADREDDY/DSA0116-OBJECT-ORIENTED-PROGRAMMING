#include <iostream>

// The developer's problematic code as described in Q3:
// 1. Single argument
double charge(double weight)
{
    return weight * 50.0;
}

// 2. Two arguments
double charge(double weight, bool express)
{
    return (weight * 50.0) + (express ? 100.0 : 0.0);
}

// 3. Three arguments with default values for express and insured
double charge(double weight, bool express = false, bool insured = false)
{
    return (weight * 50.0) + (express ? 100.0 : 0.0) + (insured ? 50.0 : 0.0);
}

int main()
{
    // The following call will FAIL to compile due to ambiguity:
    // charge(10.5); 
    // Both charge(double) AND charge(double, bool=false, bool=false) are viable!
    
    std::cout << "Testing ambiguity...\n";
    // Uncommenting below causes compiler error:
    // double cost = charge(10.5);
    return 0;
}

