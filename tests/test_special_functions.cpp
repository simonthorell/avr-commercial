#include "special_functions.h"
#include <cassert>
#include <iostream>

// Mock HD44780 object
class MockHD44780 {
public:
    void displayText(const char* message) {
        std::cout << "LCD Display: " << message << std::endl;
    }
};

// Test for specialFunctions
void test_specialFunctions() {
    MockHD44780 mockLcd;
    specialFunctionsFlags = FIRE_ALARM; // Set the flag for fire alarm

    int result = specialFunctions(&mockLcd);
    assert(result == 1); // Expecting 1 as return value when FIRE_ALARM is set

    // Reset the flag
    specialFunctionsFlags = 0;
    std::cout << "Test for specialFunctions passed." << std::endl;
}

int main() {
    std::cout << "Running tests...\n";
    test_specialFunctions();
    // Add more tests as needed
    return 0;
}
