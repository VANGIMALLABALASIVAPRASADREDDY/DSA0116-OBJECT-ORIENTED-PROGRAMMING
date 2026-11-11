# Task 03: Default Arguments and Function Overloading (Q3)

**Bloom's Level**: K5 (Evaluate)  
**Problem Context**: Courier Charge Calculator

---

## 1. Diagnosis of the Original Compiler Error (Ambiguity)

### The Developer's Original Code
```cpp
double charge(double weight);
double charge(double weight, bool express);
double charge(double weight, bool express = false, bool insured = false);
```

### Why the Program Fails to Compile
When the program invokes `charge(10.5)` with one argument:
1. Candidate 1: `charge(double weight)` is viable (exact match with 1 argument).
2. Candidate 3: `charge(double weight, bool express = false, bool insured = false)` is ALSO viable because parameters 2 and 3 have default arguments provided.
3. **Ambiguity Rule (§16.3 / ISO C++)**: When overload resolution finds two viable candidates where neither is more specialized and neither requires a better conversion sequence, the compiler issues an `error: call of overloaded 'charge(double)' is ambiguous`.
4. Similarly, calling `charge(10.5, true)` creates ambiguity between Candidate 2 and Candidate 3.

---

## 2. Redesigned Interface

To satisfy all requirements:
1. **Remove redundant overloads**: A single function with default arguments covers 1-argument, 2-argument, and 3-argument calls cleanly.
2. **Support multiple input representations**:
   - `double charge(double weightKg, bool express = false, bool insured = false);` (Kilograms)
   - `double charge(int weightGrams, bool express = false, bool insured = false);` (Grams)
   - `double charge(const Parcel& p);` (User-defined Parcel object)
3. **Zero Ambiguity**: Calls with `int`, `double`, and `Parcel` map to distinct, unambiguous conversion ranks.

---

## 3. Predicted vs. Observed Overload Selection

| Call | Invocation Expression | Predicted Overload | C++ Overload Resolution Rule | Observed Overload | Verification Status |
|---|---|---|---|---|---|
| **1** | `charge(2)` | `charge(int, bool, bool)` | **Exact Match**: Literal `2` is of type `int`. Exact match beats conversion to `double`. | `charge(int, bool, bool)` | **CONFIRMED** |
| **2** | `charge(2.0f)` | `charge(double, bool, bool)` | **Promotion vs Conversion**: `float -> double` is a standard **Promotion** (Rank 2), whereas `float -> int` is a **Conversion** (Rank 3). Promotion wins! | `charge(double, bool, bool)` | **CONFIRMED** |
| **3** | `charge(5.5)` | `charge(double, bool, bool)` | **Exact Match**: Floating literal `5.5` is type `double`. | `charge(double, bool, bool)` | **CONFIRMED** |
| **4** | `charge(500, true)` | `charge(int, bool, bool)` | **Exact Match**: `500` matches `int`; default `insured=false` applied. | `charge(int, bool, bool)` | **CONFIRMED** |
| **5** | `charge(12.5, false, true)` | `charge(double, bool, bool)` | **Exact Match**: All 3 arguments explicitly supplied. | `charge(double, bool, bool)` | **CONFIRMED** |
| **6** | `charge(p1)` | `charge(const Parcel&)` | **Exact Match**: Argument is of type `Parcel`. | `charge(const Parcel&)` | **CONFIRMED** |

---

## 4. Inquiry: C++ Overload Resolution & Default Arguments

### How the Compiler Chooses Among Overloaded Functions
When a call `f(a1, a2, ...)` is evaluated, the C++ compiler performs:
1. **Candidate Function Identification**: Looks up all functions named `f` visible in the scope.
2. **Viable Function Filtering**: Keeps candidates whose parameter counts match the arguments (accounting for default parameters) and for which implicit conversion sequences exist for each argument.
3. **Ranking of Conversion Sequences** (Best to Worst):
   - **Rank 1: Exact Match**: Identity, lvalue-to-rvalue, array-to-pointer, qualification conversions (e.g. `T` to `const T`).
   - **Rank 2: Promotion**: Integral promotions (e.g., `bool`, `char`, `short` $\rightarrow$ `int`) and floating-point promotion (`float` $\rightarrow$ `double`).
   - **Rank 3: Standard Conversion**: Integral-to-floating (`int` $\rightarrow$ `double`), floating-to-integral (`double` $\rightarrow$ `int`), pointer conversions, boolean conversions.
   - **Rank 4: User-Defined Conversion**: Constructors or conversion operators.
   - **Rank 5: Ellipsis (`...`)**: Variadic catch-all.
4. **Tie-Breaking**: If one candidate is strictly better in at least one parameter and no worse in any other, it is selected. Otherwise, compilation halts with an ambiguous call error.

### Why Default Arguments Must Be Given From the Right
In C++, function call arguments are mapped to parameters **positionally from left to right**:
- If a function was declared as `void f(int a = 1, int b);`, a call `f(5)` would be syntactically ambiguous: does `5` bind to `a` (leaving `b` without an argument), or does `5` bind to `b`?
- By requiring default arguments strictly on trailing (rightmost) parameters (`void f(int a, int b = 2);`), any omitted arguments correspond unambiguously to the trailing parameters.

---

## 5. Alternative Concept & Complexity Analysis

### Single `Parcel` Struct with Defaults vs. Overloaded Functions
```cpp
struct ParcelOptions {
    double weightKg = 0.0;
    int weightGrams = 0;
    bool express = false;
    bool insured = false;
    bool fragile = false; // Easily extensible!
};
double calculateCharge(const ParcelOptions& opts);
```

### Analysis
1. **Time Complexity of Overload Resolution**:
   - Overload resolution takes **0 runtime cycles** ($O(1)$ runtime). All candidate matching and ranking occurs strictly at **compile time**.
2. **Space Copied Per Call**:
   - Overloaded primitive functions: passes values via CPU registers (`xmm0`, `rcx`, `rdx` under x86-64 ABI) $\rightarrow$ **0 memory stack allocations**.
   - `const Parcel&`: passes an 8-byte reference/address $\rightarrow$ **0 struct copying overhead**.
3. **Handling a New Option (e.g. `fragile` or `oversized`)**:
   - **Overloaded Functions**: Adding a new parameter triggers combinatorial explosion. Existing callers may need recompilation, and adding more overloads increases code bloat and risk of ambiguity.
   - **Parcel Struct / Parameter Object Pattern**: Strongly conforms to the **Open/Closed Principle**. Adding `bool fragile = false` to the struct does not break or alter any existing call sites. New options can be initialized via designated initializers (`ParcelOptions{.weightKg = 5.0, .fragile = true}`).

