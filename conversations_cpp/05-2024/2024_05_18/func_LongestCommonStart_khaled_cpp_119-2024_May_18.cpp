/***
 * Prompt:




 khaled_cpp_119-2024_May_18: e35f969d-256c-445d-96ab-74962c25c4c0

func_LongestCommonStart_khaled_cpp_119-2024_May_18


Design a C++ function called LongestCommonStart that takes one non-empty array of strings called strs of type std::vector<std::string>, each string in the list should be non-empty and it can contain any kind of character including spaces and special characters. This function should return another string that represents the longest common prefix of the list. Please note that there is no common prefix to raise an exception, and don't forget to validate the input.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string LongestCommonStart(std::vector<std::string> strs) {
    if (strs.empty()) {
        throw std::invalid_argument("strs can't be empty");
    }

    std::string prefix = strs[0];

    for (size_t idx = 1; idx < strs.size(); ++idx) {
        if (strs[idx].length() < 1) {
            throw std::invalid_argument("string can't be empty");
        }

        while (strs[idx].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.length() - 1);
        }
    }

    if (prefix.empty()) {
        throw std::invalid_argument("there is no common prefix");
    }

    return prefix;
}

#include <cassert>
int main() {
    // TEST
    assert(LongestCommonStart({"abb", "abc"}) == std::string("ab"));
    // TEST_END

    // TEST
    assert(LongestCommonStart({"abcv", "abc"}) == std::string("abc"));
    // TEST_END

    // TEST
    assert(LongestCommonStart({"aBcv", "abcvv"}) == std::string("a"));
    // TEST_END

    // TEST
    assert(LongestCommonStart({" aB@", " B"}) == std::string(" "));
    // TEST_END

    // TEST
    try {
        LongestCommonStart({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LongestCommonStart({"test", "@ga"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
