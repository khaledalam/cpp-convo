/***






 khaled_cpp_152_2024_May_26: 8d4eaaf2-96f2-4eda-829c-379360c465bf

 func_LastTidy_khaled_cpp_152_2024_May_26





Create a C++ function called LastTidy that takes an input called num of type unsigned long long that should be greater
than zero.

We noticed that some integers, when written in base 10 with no leading zeroes, have their digits sorted in
non-decreasing order. Some examples of this are 8, 123, 555, and 224488. We will call these numbers tidy. Numbers that
do not have this property, like 20, 321, 495 and 999990, are not tidy.

We need to count all positive integers in ascending order from 1 to num. This function should return number of type
unsigned long long that represent the last counted tidy number. Please don't forget to validate input.





*/

#include <iostream>
#include <stdexcept>
#include <string>

unsigned long long LastTidy(unsigned long long num) {
    if (!num) {
        throw std::invalid_argument("num should be greater than zero");
    }

    std::string num_s = std::to_string(num);
    const size_t num_z = num_s.size();
    char character = '0';
    bool is_tidy = true;
    for (size_t idx = 0; idx < num_z; idx++) {
        if (num_s[idx] >= character) {
            character = num_s[idx];
        } else {
            num_s = std::to_string(atol(num_s.substr(0, idx).c_str()) - 1) + std::string(num_z - idx, '9');
            is_tidy = false;
            break;
        }
    }

    const unsigned long long result = atol(num_s.c_str());

    if (is_tidy) {
        return result;
    } else {
        return LastTidy(result);
    }
}

#include <cassert>
int main() {
    // TEST
    assert(LastTidy(2020) == 1999);
    // TEST_END

    // TEST
    assert(LastTidy(391458956) == 389999999);
    // TEST_END

    // TEST
    assert(LastTidy(132) == 129);
    // TEST_END

    // TEST
    assert(LastTidy(1000) == 999);
    // TEST_END

    // TEST
    assert(LastTidy(7) == 7);
    // TEST_END

    // TEST
    assert(LastTidy(1111111110) == 999999999);
    // TEST_END

    // TEST
    try {
        LastTidy(0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}