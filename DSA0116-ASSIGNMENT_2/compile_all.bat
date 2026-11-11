@echo off
echo ========================================================
echo   COMPILING ALL ASSIGNMENT 2 TASKS (Q1 - Q7)
echo   Compiler: g++ (GCC) 13.2.0 -std=c++17 -Wall -Wextra
echo ========================================================

rem Add local compiler toolchain to path if present
if exist "%~dp0.tools\w64devkit\bin" set "PATH=%~dp0.tools\w64devkit\bin;%PATH%"

echo.
echo [1/7] Compiling Task 01...
g++ -std=c++17 -Wall -Wextra Task01_CallByValueReferencePointer\complete_the_code.cpp -o Task01_CallByValueReferencePointer\complete_the_code.exe
g++ -std=c++17 -Wall -Wextra Task01_CallByValueReferencePointer\concession_updater.cpp -o Task01_CallByValueReferencePointer\concession_updater.exe
g++ -std=c++17 -Wall -Wextra Task01_CallByValueReferencePointer\predict_output.cpp -o Task01_CallByValueReferencePointer\predict_output.exe

echo [2/7] Compiling Task 02...
g++ -std=c++17 -Wall -Wextra Task02_ReturnByReference\marks_register.cpp -o Task02_ReturnByReference\marks_register.exe
g++ -std=c++17 -Wall -Wextra Task02_ReturnByReference\dangling_reference_demo.cpp -o Task02_ReturnByReference\dangling_reference_demo.exe
g++ -std=c++17 -Wall -Wextra Task02_ReturnByReference\vector_reallocation_demo.cpp -o Task02_ReturnByReference\vector_reallocation_demo.exe

echo [3/7] Compiling Task 03...
g++ -std=c++17 -Wall -Wextra Task03_DefaultArgsOverloading\courier_calculator.cpp -o Task03_DefaultArgsOverloading\courier_calculator.exe

echo [4/7] Compiling Task 04...
g++ -std=c++17 -Wall -Wextra Task04_ClassWithArray\savings_account.cpp -o Task04_ClassWithArray\savings_account.exe
g++ -std=c++17 -Wall -Wextra Task04_ClassWithArray\circular_buffer_account.cpp -o Task04_ClassWithArray\circular_buffer_account.exe

echo [5/7] Compiling Task 05...
g++ -std=c++17 -Wall -Wextra Task05_StaticMembersArrayObjects\token_predict.cpp -o Task05_StaticMembersArrayObjects\token_predict.exe
g++ -std=c++17 -Wall -Wextra Task05_StaticMembersArrayObjects\bus_ticket_complete.cpp -o Task05_StaticMembersArrayObjects\bus_ticket_complete.exe
g++ -std=c++17 -Wall -Wextra Task05_StaticMembersArrayObjects\multi_run_simulation.cpp -o Task05_StaticMembersArrayObjects\multi_run_simulation.exe

echo [6/7] Compiling Task 06...
g++ -std=c++17 -Wall -Wextra Task06_FriendAndInlineFunctions\time_journey_complete.cpp -o Task06_FriendAndInlineFunctions\time_journey_complete.exe
g++ -std=c++17 -O2 -Wall -Wextra Task06_FriendAndInlineFunctions\inline_benchmark.cpp -o Task06_FriendAndInlineFunctions\inline_benchmark.exe

echo [7/7] Compiling Task 07...
g++ -std=c++17 -Wall -Wextra Task07_Day4_DesignChallenge\original_shifting_buffer.cpp -o Task07_Day4_DesignChallenge\original_shifting_buffer.exe
g++ -std=c++17 -Wall -Wextra Task07_Day4_DesignChallenge\redesigned_circular_buffer.cpp -o Task07_Day4_DesignChallenge\redesigned_circular_buffer.exe
g++ -std=c++17 -O2 -Wall -Wextra Task07_Day4_DesignChallenge\benchmark_comparison.cpp -o Task07_Day4_DesignChallenge\benchmark_comparison.exe

echo.
echo ========================================================
echo   ALL PROGRAMS COMPILED SUCCESSFULLY!
echo ========================================================

