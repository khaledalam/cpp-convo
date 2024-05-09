/***
 * Prompt:




 khaled_cpp_86-2024_May_09: 6041c2fa-5041-4b63-b3a1-38fe319b2ecc

 func_TwinZeroInBinary_khaled_cpp_86-2024_May_09


 Create me a C++ function called TwinZeroInBinary that takes an input called number of type integer that can be zero or positive only. Please make this function return a boolean try if the input in its binary representation has 2 continuous zeros "00" otherwise return false.


 */

#include <stdexcept>
#include <iostream>
#include <string>

std::string DecimalToBinary(int n) {
    std::string binary;
    while (n > 0) {
        binary = (n % 2 == 0 ? "0" : "1") + binary;
        n /= 2;
    }
    return binary.empty() ? "0" : binary;
}

bool TwinZeroInBinary(int number) {
    if (number < 0) {
        throw std::invalid_argument("input can be zero or positive only");
    }

    std::string binary = DecimalToBinary(number);

    if (binary.length() < 2) {
        return false;
    }

    for (int idx = 1; idx < binary.length(); idx++) {
        if (binary[idx - 1] == '0' && binary[idx] == '0') {
            return true;
        }
    }

    return false;
}

#include <cassert>
int main() {
    // TEST
    assert(TwinZeroInBinary(0) == false);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(1) == false);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(2) == false);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(3) == false);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(4) == true);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(5) == false);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(10) == false);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(8) == true);
    // TEST_END

    // TEST
    assert(TwinZeroInBinary(16) == true);
    // TEST_END

    // TEST
    try {
        TwinZeroInBinary(-2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
