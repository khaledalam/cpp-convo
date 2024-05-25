/***
 * Prompt:




 khaled_cpp_110-2024_May_15: 4fbed584-608c-4937-bc89-a3784288e68b

 func_FindMaxConsecutiveSoldiers_khaled_cpp_110-2024_May_15

 

Make me a C++ function called FindMaxConsecutiveSoldiers, it will accept a non-empty string called soldiers of type std::string, and each character
in this string should be "1" or "0". This function should return a number of type int that represent the maximum number of consecutive 1's in the
input string of 0's and 1's. Please don't forget to validate the inputs.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

int FindMaxConsecutiveSoldiers(std::string soldiers) {
    if (soldiers.empty()) {
        throw std::invalid_argument("soldiers can't be empty");
    }

    for (const char soldier : soldiers) {
        if (soldier != '0' && soldier != '1') {
            throw std::invalid_argument("soldier value should be 0 or 1");
        }
    }

    int max_count = 0;
    int current_count = 0;

    for (const char num : soldiers) {
        if (num == '1') {
            current_count++;
            max_count = std::max(max_count, current_count);
        } else {
            current_count = 0;
        }
    }

    return max_count;
}

#include <cassert>
int main() {
    // TEST
    assert(FindMaxConsecutiveSoldiers("101100101") == 2);
    // TEST_END

    // TEST
    assert(FindMaxConsecutiveSoldiers("11111") == 5);
    // TEST_END

    // TEST
    assert(FindMaxConsecutiveSoldiers("00") == 0);
    // TEST_END

    // TEST
    assert(FindMaxConsecutiveSoldiers("10101010001") == 1);
    // TEST_END

    // TEST
    try {
        FindMaxConsecutiveSoldiers("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FindMaxConsecutiveSoldiers("4");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FindMaxConsecutiveSoldiers("@");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
