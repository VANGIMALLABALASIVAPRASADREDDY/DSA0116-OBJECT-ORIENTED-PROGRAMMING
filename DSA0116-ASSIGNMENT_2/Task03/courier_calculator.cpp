#include <iostream>
#include <iomanip>
#include <string>

// Structure representing a Parcel object
struct Parcel
{
    double weightKg;
    bool express;
    bool insured;
    std::string trackingId;
};

// 1. Redesigned function for weight in Kilograms (double) with default arguments
double charge(double weightKg, bool express = false, bool insured = false)
{
    std::cout << "  [SELECTED: charge(double, bool, bool)] -> weight: " 
              << weightKg << " kg, express: " << std::boolalpha << express 
              << ", insured: " << insured << '\n';
    
    double cost = weightKg * 50.0; // 50 INR per kg
    if (express) cost += 100.0;    // Express delivery charge
    if (insured) cost += 50.0;     // Insurance charge
    return cost;
}

// 2. Overload for weight in Grams (int) with default arguments
double charge(int weightGrams, bool express = false, bool insured = false)
{
    std::cout << "  [SELECTED: charge(int, bool, bool)] -> weight: " 
              << weightGrams << " g (" << (weightGrams / 1000.0) << " kg), express: " 
              << std::boolalpha << express << ", insured: " << insured << '\n';
    
    double weightKg = weightGrams / 1000.0;
    double cost = weightKg * 50.0;
    if (express) cost += 100.0;
    if (insured) cost += 50.0;
    return cost;
}

// 3. Overload for a Parcel object (passed by const reference for zero-copy efficiency)
double charge(const Parcel& p)
{
    std::cout << "  [SELECTED: charge(const Parcel&)] -> Parcel ID: " << p.trackingId 
              << ", weight: " << p.weightKg << " kg, express: " 
              << std::boolalpha << p.express << ", insured: " << p.insured << '\n';
    
    // Delegates to the primary calculation logic
    return charge(p.weightKg, p.express, p.insured);
}

int main()
{
    std::cout << "========================================================\n";
    std::cout << "   Q3: REDESIGNED COURIER CHARGE CALCULATOR             \n";
    std::cout << "========================================================\n\n";

    std::cout << std::fixed << std::setprecision(2);

    // CALL 1: charge(2) -> Literal integer '2'
    std::cout << "Test Call 1: charge(2)\n";
    std::cout << "  Prediction: Selects charge(int, bool, bool) by EXACT MATCH\n";
    double c1 = charge(2);
    std::cout << "  Charge: " << c1 << " INR\n\n";

    // CALL 2: charge(2.0f) -> Float literal '2.0f'
    std::cout << "Test Call 2: charge(2.0f)\n";
    std::cout << "  Prediction: Selects charge(double, bool, bool) by FLOATING-POINT PROMOTION (float -> double)\n";
    double c2 = charge(2.0f);
    std::cout << "  Charge: " << c2 << " INR\n\n";

    // CALL 3: charge(5.5) -> Double literal '5.5'
    std::cout << "Test Call 3: charge(5.5)\n";
    std::cout << "  Prediction: Selects charge(double, bool, bool) by EXACT MATCH with double\n";
    double c3 = charge(5.5);
    std::cout << "  Charge: " << c3 << " INR\n\n";

    // CALL 4: charge(500, true) -> Grams with express flag
    std::cout << "Test Call 4: charge(500, true)\n";
    std::cout << "  Prediction: Selects charge(int, bool, bool) by EXACT MATCH (default insured=false)\n";
    double c4 = charge(500, true);
    std::cout << "  Charge: " << c4 << " INR\n\n";

    // CALL 5: charge(12.5, false, true) -> Kg with insured flag
    std::cout << "Test Call 5: charge(12.5, false, true)\n";
    std::cout << "  Prediction: Selects charge(double, bool, bool) with all arguments provided\n";
    double c5 = charge(12.5, false, true);
    std::cout << "  Charge: " << c5 << " INR\n\n";

    // CALL 6: charge(Parcel object)
    std::cout << "Test Call 6: charge(Parcel{\"PKG-901\", 4.2, true, true})\n";
    std::cout << "  Prediction: Selects charge(const Parcel&) by EXACT MATCH with user-defined type\n";
    Parcel p1{4.2, true, true, "PKG-901"};
    double c6 = charge(p1);
    std::cout << "  Charge: " << c6 << " INR\n\n";

    std::cout << "All 6 calls resolved unambiguously and executed successfully!\n";
    return 0;
}

