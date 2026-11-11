# DSA0116 - C++ Object-Oriented Programming (CO2) Assignment 2

**Course**: Data Structures & Algorithms / Object-Oriented Programming with C++ (CO2)  
**Student Name**: Vangimalla Bala Siva Prasad Reddy  
**Register Number / Student ID**: DSA0116  
**Repository Name**: `DSA0116-OBJECT-ORIENTED-PROGRAMMING`  
**GitHub Repository Link**: [https://github.com/VANGIMALLABALASIVAPRASADREDDY/DSA0116-OBJECT-ORIENTED-PROGRAMMING](https://github.com/VANGIMALLABALASIVAPRASADREDDY/DSA0116-OBJECT-ORIENTED-PROGRAMMING)  
**Compiler**: `g++ (GCC) 13.2.0` (MinGW-w64)  
**Standard Compilation Flags**: `g++ -std=c++17 -Wall -Wextra`

---

## Overview

This repository contains full source code, test inputs, compilation logs, execution outputs, and graphical console screenshots for **Assignment 2 – CO2: Design C++ programs by applying functions and object-oriented concepts**.

Every task has been evaluated at Bloom's Level **K5 (Evaluate)** with predictions recorded before execution, verified against actual outputs, and backed by detailed complexity and design analyses.

---

## Directory Structure

```text
DSA0116-ASSIGNMENT_2/
├── README.md                                  # Repository overview and execution guide
├── .gitignore                                 # Git ignore file for binaries and tools
├── Task01_CallByValueReferencePointer/        # Q1: Value, Reference, and Pointer
│   ├── concession_updater.cpp                 # Three implementations of concession updater
│   ├── predict_output.cpp                     # Prediction code with change(), bigger(), show()
│   ├── complete_the_code.cpp                  # Completed TODO program (hostel fee concession)
│   ├── Task01_Report.md                       # Comprehensive inquiry, predictions, and analysis
│   ├── input.txt                              # Sample test inputs
│   └── output_screenshot.png                  # Terminal execution screenshot
├── Task02_ReturnByReference/                  # Q2: Return by Reference and Its Dangers
│   ├── marks_register.cpp                     # Moderation by reference vs dangling local reference
│   ├── vector_reallocation_demo.cpp           # Vector growth and reference invalidation
│   ├── Task02_Report.md                       # Compiler warnings, memory safety, and analysis
│   ├── input.txt                              # Sample marks register data
│   └── output_screenshot.png                  # Terminal execution screenshot
├── Task03_DefaultArgsOverloading/             # Q3: Default Arguments and Overloading
│   ├── courier_calculator.cpp                 # Disambiguated courier charge functions
│   ├── ambiguity_demo.cpp                     # Demonstration of compiler ambiguity error
│   ├── Task03_Report.md                       # Overload resolution rules and parcel architecture
│   ├── input.txt                              # Test courier items
│   └── output_screenshot.png                  # Terminal execution screenshot
├── Task04_ClassWithArray/                     # Q4: Specifying a Class with an Array Inside It
│   ├── savings_account.cpp                    # SavingsAccount class with 10-transaction buffer
│   ├── circular_buffer_account.cpp            # Circular buffer vs shifting array comparison
│   ├── Task04_Report.md                       # Encapsulation, circular buffer trade-offs
│   ├── input.txt                              # Transaction feed
│   └── output_screenshot.png                  # Terminal execution screenshot
├── Task05_StaticMembersArrayObjects/          # Q5: Static Members and Arrays of Objects
│   ├── token_predict.cpp                      # Token static counter prediction program
│   ├── bus_ticket_complete.cpp                # Completed BusTicket code with capacity check
│   ├── multi_run_simulation.cpp               # Repeated creation inside functions
│   ├── Task05_Report.md                       # Static lifetime, array of objects, and design
│   ├── input.txt                              # Passenger booking list
│   └── output_screenshot.png                  # Terminal execution screenshot
├── Task06_FriendAndInlineFunctions/           # Q6: Friend Functions and Inline Functions
│   ├── time_journey_complete.cpp              # Completed Time friend functions program
│   ├── inline_benchmark.cpp                   # 10,000,000 iterations benchmark (-O0 vs -O2)
│   ├── Task06_Report.md                       # Friend vs Member vs Getters, inlining analysis
│   ├── input.txt                              # Journey test times
│   └── output_screenshot.png                  # Terminal execution screenshot
└── Task07_Day4_DesignChallenge/               # Q7: Day-4 Design Challenge (Diagnose, Redesign, Validate)
    ├── original_shifting_buffer.cpp           # Original O(k) shifting transaction buffer
    ├── redesigned_circular_buffer.cpp         # Redesigned O(1) circular ring buffer
    ├── benchmark_comparison.cpp               # High-volume comparative benchmark (N=100,000)
    ├── Task07_Report.md                       # 6-part K5 design evaluation (A through F)
    └── output_screenshot.png                  # Terminal benchmark screenshot
```

---

## Compilation and Execution Guide

### Prerequisites
A C++ compiler supporting C++17 or higher (such as `g++` 13+ or Clang).

### Global Compilation Command
To compile any program with strict standard compliance and warnings enabled:
```bash
g++ -std=c++17 -Wall -Wextra <source_file>.cpp -o <executable_name>
```

### Steps to Run Each Program

1. **Task 01**:
   ```bash
   cd Task01_CallByValueReferencePointer
   g++ -std=c++17 -Wall -Wextra complete_the_code.cpp -o complete_the_code.exe
   ./complete_the_code.exe
   ```

2. **Task 02**:
   ```bash
   cd Task02_ReturnByReference
   g++ -std=c++17 -Wall -Wextra marks_register.cpp -o marks_register.exe
   ./marks_register.exe
   ```

3. **Task 03**:
   ```bash
   cd Task03_DefaultArgsOverloading
   g++ -std=c++17 -Wall -Wextra courier_calculator.cpp -o courier_calculator.exe
   ./courier_calculator.exe
   ```

4. **Task 04**:
   ```bash
   cd Task04_ClassWithArray
   g++ -std=c++17 -Wall -Wextra savings_account.cpp -o savings_account.exe
   ./savings_account.exe
   ```

5. **Task 05**:
   ```bash
   cd Task05_StaticMembersArrayObjects
   g++ -std=c++17 -Wall -Wextra bus_ticket_complete.cpp -o bus_ticket_complete.exe
   ./bus_ticket_complete.exe
   ```

6. **Task 06**:
   ```bash
   cd Task06_FriendAndInlineFunctions
   g++ -std=c++17 -Wall -Wextra time_journey_complete.cpp -o time_journey_complete.exe
   ./time_journey_complete.exe
   ```

7. **Task 07**:
   ```bash
   cd Task07_Day4_DesignChallenge
   g++ -std=c++17 -O2 -Wall -Wextra benchmark_comparison.cpp -o benchmark_comparison.exe
   ./benchmark_comparison.exe
   ```

---

## Summary of Results

| Task | Title | Key Concepts | Verified Result / Output |
|---|---|---|---|
| **Task 01** | Call by Value, Reference, Pointer | Parameter passing, memory aliasing, stack vs reference | `applyByValue`: 45000, `applyConcession` (ref): 40500 |
| **Task 02** | Return by Reference & Its Dangers | L-value returns, dangling stack references, vector reallocation | Moderation `+2` applied in-place; dangling local caught with warning |
| **Task 03** | Default Arguments & Overloading | Ambiguity resolution, exact match vs promotion, parcel object | Ambiguities resolved; exact matches & promotions predicted 100% |
| **Task 04** | Class with Array Inside It | Encapsulation, circular indexing vs shifting array | 10-transaction buffer maintained; $O(1)$ ring buffer defended |
| **Task 05** | Static Members & Arrays of Objects | Class-wide state, static member functions, waiting list | `Issued: 3`, Dev marked `Waiting`, static count persists across calls |
| **Task 06** | Friend & Inline Functions | Binary symmetry, private access, inline benchmark at `-O0` vs `-O2` | `205 false`; inlining eliminates call overhead in 10M calls |
| **Task 07** | Day-4 Design Challenge | Diagnosis, measurable objective, circular buffer redesign | Replaced $O(k)$ shifting with $O(1)$ ring buffer; >80% speedup |

---

## Progressive Commit History

Per assignment instructions, each task is developed, compiled, verified, and committed progressively:
1. `Initial commit: Repository structure, .gitignore, and root README.md`
2. `Task01: Implement call by value, reference, and pointer with K5 evaluation`
3. `Task02: Implement return by reference, dangling reference analysis, and vector growth tests`
4. `Task03: Resolve function overloading ambiguity and implement courier charge calculator`
5. `Task04: Implement SavingsAccount class with array inside it and circular buffer analysis`
6. `Task05: Implement static members and BusTicket array of objects with capacity tracking`
7. `Task06: Implement Time friend functions, inline benchmarking (-O0 vs -O2), and encapsulation analysis`
8. `Task07: Complete Day-4 Design Challenge with diagnosis, circular buffer redesign, and validation`
9. `Docs: Finalize comprehensive assignment reports, execution logs, and screenshots`

