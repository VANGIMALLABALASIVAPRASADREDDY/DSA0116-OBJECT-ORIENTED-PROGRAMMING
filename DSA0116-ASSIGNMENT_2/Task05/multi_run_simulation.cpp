#include <iostream>
#include <string>
#include <vector>

// 1. BusTicket using static member
class BusTicketStatic
{
public:
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    std::string name;

    explicit BusTicketStatic(const std::string& n) : seat(0), name(n)
    {
        if (issued < CAPACITY)
        {
            seat = ++issued;
        }
        else
        {
            seat = 0;
        }
    }

    void print() const
    {
        std::cout << "    " << name << ": "
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting"))
                  << '\n';
    }
};

int BusTicketStatic::issued = 0;

void issueBatch(int batchNumber)
{
    std::cout << "--> Function issueBatch(" << batchNumber << ") called:\n";
    BusTicketStatic t1("Passenger_" + std::to_string(batchNumber) + "A");
    BusTicketStatic t2("Passenger_" + std::to_string(batchNumber) + "B");
    t1.print();
    t2.print();
    std::cout << "    Current Static Issued Count: " << BusTicketStatic::issued << "\n\n";
}

// 2. Multi-bus alternative: TicketOffice encapsulation
class TicketOffice
{
    int issued;
    const int capacity;
    std::string busRoute;

public:
    TicketOffice(const std::string& route, int cap)
        : issued(0), capacity(cap), busRoute(route) {}

    int issueSeat()
    {
        if (issued < capacity) return ++issued;
        return 0; // Waiting list
    }

    int getIssued() const { return issued; }
    std::string getRoute() const { return busRoute; }
};

class MultiBusTicket
{
    int seat;
    std::string name;
    std::string route;

public:
    MultiBusTicket(const std::string& n, TicketOffice& office)
        : seat(office.issueSeat()), name(n), route(office.getRoute()) {}

    void print() const
    {
        std::cout << "    [" << route << "] " << name << ": "
                  << (seat ? "Seat " + std::to_string(seat) : "Waiting") << '\n';
    }
};

int main()
{
    std::cout << "========================================================\n";
    std::cout << "  Q5: MULTI-RUN FUNCTION CALL & MULTI-BUS SIMULATION     \n";
    std::cout << "========================================================\n\n";

    std::cout << "PART 1: Calling issueBatch() TWICE:\n";
    std::cout << "Expectation: Static count persists across function returns.\n";
    std::cout << "First call fills seats 1 and 2. Second call fills seat 3 and places next passenger on waiting list.\n\n";

    issueBatch(1);
    issueBatch(2);

    std::cout << "PART 2: Multi-Bus Capability (Alternative TicketOffice Object):\n";
    TicketOffice morningBus("Route 101 - Morning", 2);
    TicketOffice eveningBus("Route 202 - Evening", 2);

    MultiBusTicket mb1("Alice", morningBus);
    MultiBusTicket mb2("Bob", morningBus);
    MultiBusTicket mb3("Charlie", morningBus); // waiting list for morning

    MultiBusTicket eb1("David", eveningBus);
    MultiBusTicket eb2("Emma", eveningBus);

    std::cout << "Morning Bus Passengers (Capacity 2):\n";
    mb1.print();
    mb2.print();
    mb3.print();
    std::cout << "  Total Issued: " << morningBus.getIssued() << "\n\n";

    std::cout << "Evening Bus Passengers (Capacity 2):\n";
    eb1.print();
    eb2.print();
    std::cout << "  Total Issued: " << eveningBus.getIssued() << "\n\n";

    return 0;
}

