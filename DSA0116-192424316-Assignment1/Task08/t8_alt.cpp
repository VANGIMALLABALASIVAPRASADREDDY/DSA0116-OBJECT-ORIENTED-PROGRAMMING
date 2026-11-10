// Task 8 alternative: std::getline() + std::stoi() inside try/catch instead of cin >>
#include <iostream>
#include <stdexcept>
#include <string>

bool readIntLine(const char* prompt, int lo, int hi, int& out)
{
    std::string line;
    while (true) {
        std::cout << prompt << std::flush;
        if (!std::getline(std::cin, line)) return false;           // end of input
        try {
            std::size_t pos = 0;
            const int v = std::stoi(line, &pos);                   // throws invalid_argument / out_of_range
            if (pos != line.size()) throw std::invalid_argument("trailing characters");
            if (v < lo || v > hi) throw std::out_of_range("outside allowed range");
            out = v; return true;
        } catch (const std::exception& e) {
            std::cout << "  -> rejected (" << e.what() << ")\n";
        }
    }
}
int main()
{
    int zone = 0, hour = 0;
    if (!readIntLine("Zone (0-2): ", 0, 2, zone)) return 0;
    if (!readIntLine("Hour (0-23): ", 0, 23, hour)) return 0;
    std::cout << "accepted zone " << zone << ", hour " << hour << '\n';
}
