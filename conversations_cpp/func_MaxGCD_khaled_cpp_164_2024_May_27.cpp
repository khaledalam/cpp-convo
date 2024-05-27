/***






 khaled_cpp_164_2024_May_27: 0acb4154-465b-4d28-86fd-be0f7aafc15f

 func_MaxGCD_khaled_cpp_164_2024_May_27



Create a C++ function called MaxGCD that takes a number of type int called num, where this num should be greater than 0.

This function should return another number of type int y (1 ≤ y < num) such that gcd(num, y) + y is maximum possible. Please make the code as short as possible.




*/

#include <iostream>
#include <stdexcept>
#include <string>

int MaxGCD(int num) {
    if (num < 1) {
        throw std::invalid_argument("num should be greater than 0");
    }

    return num - 1;
}

#include <cassert>
int main() {
    // TEST
    assert(MaxGCD(10) == 9);
    // TEST_END

    // TEST
    assert(MaxGCD(1) == 0);
    // TEST_END

    // TEST
    try {
        MaxGCD(0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxGCD(-1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}