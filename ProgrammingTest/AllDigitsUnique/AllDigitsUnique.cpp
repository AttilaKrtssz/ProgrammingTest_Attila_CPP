#include <iostream>
#include "AllDigitsUnique.h"

using namespace std;

bool IsAllDigitsUnique(unsigned int value)
{
    bool seen[10] = {false}; // Array to track digits

    while (value > 0) {
        unsigned int digit = value % 10;
        if (seen[digit]) {
            return false; // Duplicate digit found
        }
        seen[digit] = true;
        value /= 10; // Remove the last digit
    }
    return true; // No duplicate digits
}

void RunAllDigitsUnique() {
    cout << "\n=== All Digits Unique ===\n";
    cout << "Enter numbers to check if all digits are unique.\n";
    cout << "Type -1 to return to the main menu.\n\n";

    while (true) {
        cout << "Enter a number: ";
        unsigned long long value;
        cin >> value;

        // Check for invalid input
        if (!cin) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        // Check for exit condition
        if (value == static_cast<unsigned long long>(-1)) {
            cout << "Returning to main menu...\n\n";
            break;
        }

        // Call the function and display the result
        bool result = IsAllDigitsUnique(value);
        cout << "AllDigitsUnique(" << value << ") = " << (result ? "true" : "false") << "\n\n";
    }
}