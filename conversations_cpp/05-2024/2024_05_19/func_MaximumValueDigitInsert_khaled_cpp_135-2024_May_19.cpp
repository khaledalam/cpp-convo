/***
 * Prompt:




 khaled_cpp_135-2024_May_19: 3b3bd3f2-697a-428c-86df-3a867759a964

func_MaximumValueDigitInsert_khaled_cpp_135-2024_May_19

Create a C++ function called MaximumValueDigitInsert that takes two inputs, the first input is called num of type int which can be negative, zero, or positive, the second input is called digit of type char, which contains only digits. This function should return another number of type int which represents the maximum possible value obtained by inserting one single digit inside the decimal representation of integer num, for example, if num = 5 and digit = '2' the output should be 52. Please don't forget to validate the input.



 */

#include <iostream>
#include <stdexcept>
#include <string>

int MaximumValueDigitInsert(int num, char digit) {
    if (!isdigit(digit)) {
        throw std::invalid_argument("digit must be a valid digit");
    }

    std::string nst = std::to_string(num);

    if (num < 0) {
        num = (digit < nst[1]) ? (std::stoi(nst[0] + std::to_string(digit - '0') + nst.substr(1, std::string::npos)))
                               : std::stoi(nst.substr(0) + digit);
        return num;
    }

    for (int idx = 0; idx < nst.size(); idx++) {
        if (digit > nst[idx]) {
            return std::stoi(nst.substr(0, idx) + digit + nst.substr(idx));
        }
    }

    return std::stoi(nst + digit);
}

#include <cassert>
int main() {
    // TEST
    assert((MaximumValueDigitInsert(1, '4') == 41));
    // TEST_END

    // TEST
    assert((MaximumValueDigitInsert(5, '2') == 52));
    // TEST_END

    // TEST
    assert((MaximumValueDigitInsert(0, '2') == 20));
    // TEST_END

    // TEST
    assert((MaximumValueDigitInsert(-3, '6') == -36));
    // TEST_END

    // TEST
    assert((MaximumValueDigitInsert(9, '0') == 90));
    // TEST_END

    // TEST
    try {
        MaximumValueDigitInsert(1, '@');
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}