/***
 * Prompt:




 khaled_cpp_118-2024_May_18: 95c354ac-ed85-4319-a071-a272f5df2a71

 func_DistinctSubstrings_khaled_cpp_118-2024_May_18


Design a C++ function called DistinctSubstrings that takes one non-empty string input called str of type std::string, this string can contain any type of characters including spaces and special characters. This function should return a number of type int that represents the count of distinct substrings in the input str. Please don't forget to validate the inputs.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

int DistinctSubstrings(const std::string &str) {
    if (str.empty()) {
        throw std::invalid_argument("str can't be empty");
    }

    std::unordered_set<std::string> substrings;

    for (size_t idx = 0; idx < str.length(); ++idx) {
        std::string substring = "";

        for (size_t jdx = idx; jdx < str.length(); ++jdx) {
            substring += str[jdx];
            substrings.insert(substring);
        }
    }

    return substrings.size();
}

#include <cassert>
int main() {
    // TEST
    assert(DistinctSubstrings("ab") == 3);
    // TEST_END

    // TEST
    assert(DistinctSubstrings("#") == 1);
    // TEST_END

    // TEST
    assert(DistinctSubstrings("11") == 2);
    // TEST_END

    // TEST
    assert(DistinctSubstrings("abc") == 6);
    // TEST_END

    // TEST
    assert(DistinctSubstrings("@ fH#@") == 20);
    // TEST_END

    // TEST
    try {
        DistinctSubstrings("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
