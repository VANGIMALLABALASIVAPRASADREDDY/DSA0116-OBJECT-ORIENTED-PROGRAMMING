#include <iostream>
#include <iomanip>

// 1. Returning non-const reference: allows reading AND in-place modification
int& getHighestMark(int marks[], int size)
{
    int maxIdx = 0;
    for (int i = 1; i < size; ++i)
    {
        if (marks[i] > marks[maxIdx])
        {
            maxIdx = i;
        }
    }
    return marks[maxIdx]; // Returns lvalue reference to the array element
}

// 2. Returning const reference: read-only access, prevents accidental mutation
const int& getHighestMarkReadOnly(const int marks[], int size)
{
    int maxIdx = 0;
    for (int i = 1; i < size; ++i)
    {
        if (marks[i] > marks[maxIdx])
        {
            maxIdx = i;
        }
    }
    return marks[maxIdx]; // Returns read-only reference
}

// 3. Returning by copy: safe against external changes, but creates a duplicate value
int getHighestMarkCopy(const int marks[], int size)
{
    int maxIdx = 0;
    for (int i = 1; i < size; ++i)
    {
        if (marks[i] > marks[maxIdx])
        {
            maxIdx = i;
        }
    }
    return marks[maxIdx]; // Returns prvalue copy
}

void printMarks(const int marks[], int size, const std::string& label)
{
    std::cout << std::left << std::setw(28) << label << ": [ ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << marks[i] << (i + 1 < size ? ", " : " ");
    }
    std::cout << "]\n";
}

int main()
{
    std::cout << "========================================================\n";
    std::cout << "  Q2: EXAMINATION MARKS REGISTER - RETURN BY REFERENCE  \n";
    std::cout << "========================================================\n\n";

    const int CLASS_SIZE = 5;
    int marks[CLASS_SIZE] = {78, 85, 92, 64, 89};

    printMarks(marks, CLASS_SIZE, "Initial Marks Register");

    // Inspection
    std::cout << "\nCurrent Highest Mark (via Read-Only): "
              << getHighestMarkReadOnly(marks, CLASS_SIZE) << '\n';

    // DEMONSTRATION 1: Direct in-place moderation of +2 using returned reference
    std::cout << "\n--> Applying Moderation (+2) directly to returned reference:\n";
    std::cout << "    Code executed: getHighestMark(marks, CLASS_SIZE) += 2;\n";
    getHighestMark(marks, CLASS_SIZE) += 2;
    printMarks(marks, CLASS_SIZE, "After Moderation (+2)");

    // DEMONSTRATION 2: Using the function call on the LEFT side of assignment operator (=)
    std::cout << "\n--> Using function call on the LEFT of assignment (=):\n";
    std::cout << "    Code executed: getHighestMark(marks, CLASS_SIZE) = 99;\n";
    getHighestMark(marks, CLASS_SIZE) = 99;
    printMarks(marks, CLASS_SIZE, "After Direct Assignment (= 99)");

    // DEMONSTRATION 3: Copy vs Reference semantics
    std::cout << "\n--> Testing Return by Copy:\n";
    int copyVal = getHighestMarkCopy(marks, CLASS_SIZE);
    copyVal = 50; // Modifies only local copy
    std::cout << "    Modified copy to " << copyVal << ", but marks in array remain: ";
    printMarks(marks, CLASS_SIZE, "Current Array");

    std::cout << "\nSummary: Returning a reference creates a valid lvalue, allowing\n"
              << "direct mutation of the target container element.\n";

    return 0;
}
