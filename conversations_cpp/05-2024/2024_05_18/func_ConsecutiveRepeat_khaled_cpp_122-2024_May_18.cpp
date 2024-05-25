/***
 * Prompt:




 khaled_cpp_122-2024_May_18: dd79fdbb-a5f3-46c1-bce0-d01c5518e2cb

 func_ConsecutiveRepeat_khaled_cpp_122-2024_May_18
 

Create a C++ function called ConsecutiveRepeat that takes one non-empty case-sensitive input called str of type std::string, it should contain any kind of characters including spaces and special characters. This function should return another string of type std::string that represents the maximum number of consecutive repeating characters in the input string. Please don't forget to validate the input.




 */

#include <iostream>
#include <stdexcept>
#include <string>

int ConsecutiveRepeat(const std::string &str) {
    if (str.empty()) {
        throw std::invalid_argument("str can't be empty");
    }

    int max_power = 1, curr_power = 1;

    for (int idx = 1; idx < str.size(); ++idx) {
        if (str[idx] == str[idx - 1]) {
            curr_power++;
            max_power = std::max(max_power, curr_power);
        } else {
            curr_power = 1;
        }
    }

    return max_power;
}

#include <cassert>
int main() {
    // TEST
    assert(ConsecutiveRepeat("1221") == 2);
    // TEST_END

    // TEST
    assert(ConsecutiveRepeat("122111") == 3);
    // TEST_END

    // TEST 
    assert(ConsecutiveRepeat("   5G#") == 3);
    // TEST_END

    // TEST
    try {
        ConsecutiveRepeat("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
