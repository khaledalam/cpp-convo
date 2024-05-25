/***
 * Prompt:




 khaled_cpp_136-2024_May_19: 759ea970-b6e7-44e4-92b1-ac209315ab91

func_CarryOps_khaled_cpp_136-2024_May_19


Create a C++ function called CarryOps that takes two inputs of type int called num1 and num2, both of them should be greater than 0. This function should return another number of type int which represents the count of the number of carry operations of a sum of the two input integers. Note that each number is less than 10 digits. Please don't forget to validate the input.



 */

#include <iostream>
#include <stdexcept>
#include <string>

int CarryOps(int num1, int num2) {
    if (num1 <= 0 || num2 <= 0) {
        throw std::invalid_argument("both inputs must be greater than 0");
    }

    const int carry_limit = 10, size_limit = 9;

    std::string snum1 = std::to_string(num1), snum2 = std::to_string(num2);

    if (num1 < 0 || num2 < 0 || snum1.size() > size_limit || snum2.size() > size_limit) {
        throw std::invalid_argument("each number should be less than 10 digits");
    }

    snum1.insert(snum1.begin(), size_limit - snum1.length(), '0');

    snum2.insert(snum2.begin(), size_limit - snum2.length(), '0');

    int count = 0, past_carry = 0;

    for (int idx = snum1.size() - 1; idx >= 0; idx--) {
        int sum = (snum1[idx] - '0') + (snum2[idx] - '0') + past_carry;
        bool currentCarry = sum >= carry_limit;
        count += currentCarry ? 1 : 0;
        past_carry = currentCarry ? 1 : 0;
    }

    return count;
}

#include <cassert>
int main() {
    // TEST
    assert((CarryOps(123, 456) == 0));
    // TEST_END

    // TEST
    assert((CarryOps(594, 123) == 1));
    // TEST_END

    // TEST
    assert((CarryOps(555, 555) == 3));
    // TEST_END

    // TEST
    assert((CarryOps(1, 200) == 0));
    // TEST_END

    // TEST
    try {
        CarryOps(0, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CarryOps(-1, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CarryOps(1, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CarryOps(1, -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CarryOps(1234567891, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}