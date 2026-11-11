# Task 04: Specifying a Class with an Array Inside It (Q4)

**Bloom's Level**: K5 (Evaluate)  
**Problem Context**: Savings Account Mini-Statement

---

## 1. Class Specification & Architecture

### Complete Class Layout
```cpp
class SavingsAccount
{
private:
    static const int MAX_TX = 10;
    long long accountNumber;
    double balance;
    double transactions[MAX_TX]; // Fixed array for last 10 transactions
    int count;                   // Current count of stored transactions (0 to 10)

public:
    // Defined OUTSIDE using scope resolution operator
    SavingsAccount(long long accNum, double initialBalance);

    // Defined INSIDE the class specification: inline candidate
    void deposit(double amount)
    {
        if (amount <= 0) return;
        balance += amount;
        recordTransaction(amount);
    }

    // Defined OUTSIDE using scope resolution operator
    bool withdraw(double amount);
    void miniStatement() const;

private:
    void recordTransaction(double amount);
};
```

### Member Function Definition Placement
1. **Inside the Class (`deposit`)**:
   - Automatically treated as an inline candidate by the compiler.
   - Ideal for short, frequently called accessor or mutator routines without complex branching.
2. **Outside the Class using Scope Resolution Operator `::` (`withdraw`, `miniStatement`, Constructor)**:
   - Separates interface specification from implementation details.
   - Keeps class headers clean, readable, and decoupled from heavy formatting/printing dependencies (`<iostream>`, `<iomanip>`).

---

## 2. Inquiry: Encapsulation & The 11th Transaction

### Why the Array Must Be Private
1. **Data Integrity & Invariant Preservation**:
   - The transactions array represents the audit trail of the account.
   - If public, external code could alter historical entries without modifying `balance`, or forge deposits/withdrawals, causing catastrophic data corruption.
2. **Implementation Hiding**:
   - Making `transactions` private ensures that whether the bank stores transactions as a shifting array, a circular ring buffer, or a dynamic deque is an internal implementation detail hidden behind `miniStatement()`.

### Handling the 11th Transaction: Shifting Array vs. Circular Index
When the 11th transaction arrives in a 10-element capacity buffer:

1. **Approach A: Shifting Fixed Array**:
   - **Mechanism**: The oldest transaction at index `0` is overwritten by copying element `1` into `0`, element `2` into `1`, ..., element `9` into `8`. The new 11th transaction is written into index `9`.
   - **Operations**: Requires $(k - 1)$ read-and-write memory shift operations.
   - **Cost**: **$O(k)$ time complexity** per transaction.

2. **Approach B: Circular Index / Ring Buffer**:
   - **Mechanism**: An integer pointer `head` tracks the oldest transaction. When full, the new transaction is written directly into `buffer[head]`, and `head` is updated via modular arithmetic:
     $$\text{head} = (\text{head} + 1) \pmod k$$
   - **Operations**: Exactly 1 array write + 1 integer modulo increment.
   - **Cost**: **$O(1)$ constant time complexity** per transaction.

---

## 3. Design Decision: Scaling to 50 Transactions

**Scenario**: The bank increases the mini-statement requirement from the last 10 to the last 50 transactions.

### Evaluation of Which Design Changes Least
| Metric | Shifting Array Design | Circular Buffer Design |
|---|---|---|
| **Constant Changed** | `MAX_TX = 50` | `CAPACITY = 50` |
| **Code Changes Required** | None in logic, but internal loop now shifts 49 elements | None in logic; pointer advance remains `(head + 1) % 50` |
| **Performance Impact** | **$5\times$ Slowdown**: Shifts 49 doubles (392 bytes) on **EVERY SINGLE TRANSACTION** | **$0\times$ Impact**: Strictly $O(1)$ write time remains identical! |

### Defense of Circular Buffer
The **Circular Buffer** changes least in terms of architectural impact and algorithmic performance. While both require updating a single capacity constant in code, the shifting array suffers a **$5\times$ degradation in write latency** per transaction ($O(50)$ vs $O(10)$), whereas the circular buffer maintains **flat $O(1)$ constant overhead** regardless of capacity scaling.

---

## 4. Alternative Concept and Complexity Analysis

### Comparison: Shifting Array vs. Circular Buffer vs. `std::deque`

```cpp
// 1. Shifting Fixed Array
double transactions[k]; // O(k) per full insertion

// 2. Circular Buffer
double buffer[k]; int head = 0; // O(1) per full insertion

// 3. std::deque
std::deque<double> txQueue;
if (txQueue.size() == k) txQueue.pop_front();
txQueue.push_back(amount); // O(1) amortized
```

### Complexity Matrix
| Design Pattern | Time to Add Transaction ($k$ items full) | Auxiliary Space Complexity | Memory Allocation Type | Cache Locality |
|---|---|---|---|---|
| **Shifting Array** | $O(k)$ (shifts $k-1$ elements) | $O(k)$ ($k \times 8$ bytes) | Stack / Contiguous in-object | High |
| **Circular Buffer** | **$O(1)$** (1 write + 1 modulo) | $O(k)$ ($k \times 8$ bytes + 8 bytes pointers) | Stack / Contiguous in-object | **Maximum** |
| **`std::deque`** | $O(1)$ amortized | $O(k) + O(\text{chunks})$ | Dynamic Heap (Multiple chunk buffers + map) | Moderate |

### Conclusion
The **Circular Ring Buffer** is the optimal engineering solution: it matches the $O(1)$ write speed of `std::deque` while completely avoiding dynamic heap allocations and fragmentation, and utterly eliminates the $O(k)$ element-shifting overhead of the naive array.

