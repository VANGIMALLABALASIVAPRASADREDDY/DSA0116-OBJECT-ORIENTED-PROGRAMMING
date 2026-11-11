# Task 01: Call by Value, by Reference, and by Pointer (Q1)

**Bloom's Level**: K5 (Evaluate)  
**Problem Context**: Hostel Fee Concession Updater

---

## 1. Challenge & Inquiry

### Implementation of Three Passing Mechanisms
1. **Pass by Value (`applyConcessionByValue`)**:
   - Parameter `fee` is allocated on the activation frame (stack frame) of the function.
   - The caller's value is bitwise copied into this local variable.
   - Any modifications (`fee -= ...`) affect only this local stack slot. When the function returns, this frame is popped and the modification is completely lost.
2. **Pass by Reference (`applyConcessionByReference`)**:
   - Parameter `long long& fee` is an alias bound directly to the caller's memory address.
   - Under the hood, the compiler passes the memory address, but dereferencing is implicit and automatic.
   - Any modification directly mutates the caller's original variable in memory.
3. **Pass by Pointer (`applyConcessionByPointer`)**:
   - Parameter `long long* fee` is an explicit pointer variable holding the memory address of the caller's variable.
   - Dereferencing `*fee` reads or writes directly to that caller memory location.
   - Requires explicit address-of operator (`&fee`) at call site and explicit null-checking inside the function.

### Why Only Two of Them Change the Caller's Fee
Only **Call by Reference** and **Call by Pointer** change the caller's fee because they operate on the actual memory location allocated by the caller. Call by Value operates on an isolated stack copy.

### When a Const Reference Parameter Should Be Used
A `const` reference parameter (`const T&`) should be used when:
1. The function requires **read-only access** to the argument.
2. The argument type is a non-trivial user-defined type, large struct, or class object (e.g. `std::string`, `Student`, `std::vector`), where copying creates unacceptable $O(N)$ CPU and memory overhead.
3. It allows binding to **rvalues and temporary values** (e.g., literals and temporary expressions) safely.

---

## 2. Design Decision: In-Place Mutation vs. Pure Function Returning New Fee

**Problem**: Several concessions (e.g., Merit 10%, Sports 15%, Single Parent 25%) may apply to one student.

**Evaluation & Defense**:
- **Option A (In-Place Mutation via Reference)**:
  - Modifies the object state directly: `applyConcession(fee, 10); applyConcession(fee, 15);`.
  - *Advantage*: Zero return-copying overhead; matches an object-oriented mutating method.
  - *Risk*: Hidden side effects; non-reproducible calculations if an intermediate step fails or if multiple dry-run quotes need to be generated without mutating persistent records.
- **Option B (Pure Function Returning New Fee - DEFENDED CHOICE)**:
  - Signature: `long long applyConcession(long long fee, int percent) { return fee - (fee * percent / 100); }`
  - *Advantage*: Enables clean functional chaining:
    ```cpp
    long long finalFee = applyConcession(applyConcession(baseFee, 10), 15);
    ```
  - Eliminates temporal coupling and side-effects. Facilitates audit logging (before/after states easily preserved) and unit testing.

---

## 3. Predict the Output Analysis

### Program Analyzed
```cpp
#include <iostream>
void change(int a, int& b, int* c) {
    a += 10;
    b += 10;
    *c += 10;
}
int& bigger(int& p, int& q) { return p > q ? p : q; }
void show(int x, int y = 5, int z = 10) { std::cout << x + y + z << ' '; }
int main() {
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    std::cout << a << ' ' << b << ' ' << c << '\n';
    bigger(a, c) = 100;
    std::cout << a << ' ' << c << '\n';
    show(1);
    show(1, 2);
    show(1, 2, 3);
    std::cout << '\n';
}
```

### Prediction (Written Before Running)
```text
1 12 13
1 100
16 13 6 
```

### Actual Output (Observed Upon Execution)
```text
1 12 13
1 100
16 13 6 
```

### Differences & C++ Rules Explanation
- **Difference**: Exactly **0 differences**; the prediction matches the compiler output perfectly.
- **Rules Involved**:
  1. `change(a, b, &c)`:
     - `a` passed by value: local stack copy incremented to 11, discarded upon return. Caller `a` remains `1`.
     - `b` passed by reference: caller `b` incremented by 10 $\rightarrow$ `12`.
     - `c` passed by address (`&c`): pointer dereferenced `*c += 10`, modifying caller `c` $\rightarrow$ `13`.
     - Output: `1 12 13`.
  2. `bigger(a, c) = 100`:
     - `bigger(1, 13)` compares $1 > 13$ (false), returning a reference to `q` (which binds to `c`).
     - Because `bigger()` returns an lvalue reference (`int&`), the function call can appear on the **left side of an assignment operator** (`=`).
     - Assigning `100` writes directly into variable `c`. `a` remains `1`.
     - Output: `1 100`.
  3. `show(...)` with Default Arguments:
     - `show(1)`: explicit `x=1`, default `y=5`, default `z=10` $\rightarrow 1 + 5 + 10 = 16$.
     - `show(1, 2)`: explicit `x=1`, explicit `y=2`, default `z=10` $\rightarrow 1 + 2 + 10 = 13$.
     - `show(1, 2, 3)`: explicit `x=1`, explicit `y=2`, explicit `z=3` $\rightarrow 1 + 2 + 3 = 6$.
     - Output: `16 13 6 `.

---

## 4. Complete the Code Program

### Code Completed
```cpp
void applyConcession(long long& fee, int percent)
{
    // TODO 1: Reduce the caller's fee by percent using integer arithmetic (call by reference)
    fee -= fee * percent / 100;
}
```

### Execution Results
- Expected:
  ```text
  after call by value : 45000
  after call by reference: 40500
  ```
- Observed:
  ```text
  after call by value : 45000
  after call by reference: 40500
  ```

### Why Call by Value Leaves the Fee at 45000
`applyByValue(long long fee, int percent)` declares its parameter `fee` by value. When `applyByValue(hostelFee, 10)` is invoked, the 8-byte value `45000` is copied into the function's stack frame. The subtraction occurs entirely on this copy. When the function terminates, its activation record is deallocated. `hostelFee` in `main()` was never accessed.

---

## 5. Alternative Concept & Complexity Analysis

### Signature: `long long applyConcession(long long fee, int percent)`
- **Solution Design**: The function receives the current fee, computes the discount, and returns the modified fee. Caller updates via assignment: `fee = applyConcession(fee, 10);`.
- **Time Complexity**: $O(1)$ for all versions (arithmetic calculations take constant CPU cycles).
- **Space Copied Per Call**:
  | Data Type Passed | Pass by Value | Pass by Reference (`T&`) | Pass by Const Reference (`const T&`) |
  |---|---|---|---|
  | `long long` (primitive) | 8 bytes copied | 8 bytes (pointer/address) | 8 bytes (pointer/address) |
  | Large `Student` Object (e.g. 1024 bytes) | **1024 bytes** copied + copy constructor invoked | **8 bytes** (address alias, zero copying) | **8 bytes** (address alias, read-only safety, zero copying) |

**Conclusion**: For primitive data types like `long long`, pass-by-value and pass-by-reference have virtually identical space costs. For large class objects, passing by `const reference` saves orders of magnitude in both memory copy overhead and CPU cycles.

