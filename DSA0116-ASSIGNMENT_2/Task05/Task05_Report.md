# Task 05: Static Members and Arrays of Objects (Q5)

**Bloom's Level**: K5 (Evaluate)  
**Problem Context**: College Bus Seat Tickets

---

## 1. Design Starting Point & Core Principles

> **Core Principle**: *"Data that belongs to the whole class – not to any one object – should exist only once, however many objects are created."*

### Key Architectural Decisions
1. **Which Members Must Be Static and Where Defined**:
   - `issued`: Must be static because it records the cumulative total of seats issued for the entire bus across all ticket instances.
   - `CAPACITY`: Static constant (`static const int CAPACITY = 3;`), shared by all tickets.
   - **Where Defined**: In C++, non-inline static data members are only *declared* within the class definition. They must be *defined and allocated* exactly once at file scope outside the class:
     ```cpp
     int BusTicket::issued = 0; // Definition and storage allocation
     ```
2. **Why a Static Member Function Cannot Use `this` or Non-Static Members**:
   - A non-static member function has an implicit first parameter: `this`, a pointer to the invoking instance (`BusTicket* const this`).
   - A `static` member function (like `BusTicket::count()`) belongs to the class namespace itself, not to any individual object instance.
   - It can be called even when zero objects exist (`BusTicket::count()`).
   - Consequently, no `this` pointer exists in its activation frame, and attempting to reference non-static members (like `seat` or `name`) results in a compile-time error (`error: invalid use of member in static member function`).
3. **How an Array of `BusTicket` Objects Is Created and Initialised**:
   - When declaring an array of objects:
     ```cpp
     BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"),
                          BusTicket("Chitra"), BusTicket("Dev")};
     ```
   - Each element is initialized sequentially in increasing index order (`0` through `3`).
   - Each constructor call accesses and increments the single shared static `issued` variable.
4. **What Happens When Tickets Are Created Inside a Loop or Function**:
   - Static data members have **static storage duration** (they exist from program startup until program termination).
   - When objects created inside a function or loop go out of scope, their local stack frames are destroyed, but the **static member retains its accumulated value**. Subsequent function invocations continue from the previous count.

---

## 2. Predict the Output Analysis (Token Program)

### Program Analyzed
```cpp
#include <iostream>
class Token {
    static int next;
    int id;
public:
    Token() { id = ++next; }
    int get() const { return id; }
    static int issued() { return next - 100; }
};
int Token::next = 100;
int main() {
    Token counter[3];
    Token extra;
    std::cout << counter[0].get() << ' ' << counter[2].get() << ' ' << extra.get()
              << ' ' << Token::issued() << '\n';
}
```

### Prediction (Written Before Running)
```text
101 103 104 4
```

### Actual Output (Observed)
```text
101 103 104 4
```

### Explanation of Prediction & C++ Rules
1. `Token::next = 100`: The static variable is initialized to 100 at global startup.
2. `Token counter[3]`: The default constructor executes 3 times sequentially:
   - `counter[0]`: `next` becomes 101, `id` = 101.
   - `counter[1]`: `next` becomes 102, `id` = 102.
   - `counter[2]`: `next` becomes 103, `id` = 103.
3. `Token extra`: Constructor executes for the 4th time:
   - `extra`: `next` becomes 104, `id` = 104.
4. Constructor ran **4 times total** (3 for array elements + 1 for `extra`).
5. Output values:
   - `counter[0].get()` = `101`
   - `counter[2].get()` = `103`
   - `extra.get()` = `104`
   - `Token::issued()` = $104 - 100 = \mathbf{4}$.

---

## 3. Complete the Code Program

### Code Completed
```cpp
// TODO 1: If fewer than CAPACITY tickets have been issued, increase issued and
// give this ticket the next seat number; otherwise leave seat as 0 (waiting list)
if (issued < CAPACITY)
{
    seat = ++issued;
}
else
{
    seat = 0; // waiting list
}

// TODO 2: Return the number of seats issued so far
static int count()
{
    return issued;
}
```

### Execution Output
- Expected Output:
  ```text
  Asha: Seat 1
  Bala: Seat 2
  Chitra: Seat 3
  Dev: Waiting
  Issued: 3
  ```
- Observed Output:
  ```text
  Asha: Seat 1
  Bala: Seat 2
  Chitra: Seat 3
  Dev: Waiting
  Issued: 3
  ```

---

## 4. Multi-Run Function Call Analysis

When ticket creation is encapsulated inside a function `issueBatch()` called twice:
- **First Call (`issueBatch(1)`)**:
  - `Passenger_1A` allocated $\rightarrow$ `seat = 1`, `issued = 1`.
  - `Passenger_1B` allocated $\rightarrow$ `seat = 2`, `issued = 2`.
  - Function returns: local ticket objects are destroyed, but `BusTicketStatic::issued` remains `2`.
- **Second Call (`issueBatch(2)`)**:
  - `Passenger_2A` allocated $\rightarrow$ `seat = 3`, `issued = 3` (Capacity reached!).
  - `Passenger_2B` allocated $\rightarrow$ `issued < CAPACITY` evaluates to false. `seat = 0` (Waiting list).
- **Conclusion**: Proves that static class state transcends individual call frames and object lifetimes.

---

## 5. Alternative Concept and Complexity Analysis

### Comparison: Global Variable vs. Static Class Member vs. `TicketOffice` Object

```cpp
// 1. Global Variable
int g_issuedSeats = 0;

// 2. Static Member (Class Level)
class BusTicket { static int issued; ... };

// 3. Separate TicketOffice Object (Multi-Tenant)
class TicketOffice { int issued; int capacity; ... };
class BusTicket { BusTicket(TicketOffice& office); ... };
```

### Evaluation Matrix
| Evaluation Criteria | Global Variable | Static Class Member | `TicketOffice` Object |
|---|---|---|---|
| **Time Complexity** | $O(1)$ per ticket | $O(1)$ per ticket | $O(1)$ per ticket |
| **Space Overhead** | 1 integer ($O(1)$) | 1 integer ($O(1)$) | 1 counter per office ($O(B)$ for $B$ buses) |
| **Encapsulation** | **Violated**: Accessible and mutable by any part of the codebase without restriction. | **Strong**: Encapsulated within class; modified only through constructor logic. | **Highest**: Encapsulated within dedicated domain model. |
| **Multi-Bus Capability** | **Impossible**: All tickets across all routes share one global counter. | **Impossible / Rigid**: Since `static int issued` belongs to the `BusTicket` class type, every bus must share the same counter. Running two buses at once corrupts quotas! | **Superior**: Allows instantiating separate offices for Route 101, Route 202, etc., allowing any number of buses to operate concurrently. |

**Verdict**: The static class member provides clean encapsulation for a single bus, but introducing a dedicated **`TicketOffice` entity** is the superior object-oriented architecture for scalable, multi-bus transit systems.

