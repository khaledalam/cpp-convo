/***
 * Prompt:




 khaled_cpp_115-2024_May_17: 8e54ef5f-f3cc-47c3-b910-39aa6b0ce822

func_LengthOfLongestNonRepeatingSubstring_khaled_cpp_115-2024_May_17

Design a C++ function called LengthOfLongestNonRepeatingSubstring that takes a non-empty string of type std::string that can contain any kind of characters including spaces and special characters. This function should return a number of type int that represents the length of the longest substring without repeating characters in a given input string. Please don't forget to validate the input.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

int LengthOfLongestNonRepeatingSubstring(std::string str) {
    if (str.empty()) {
        throw std::invalid_argument("str can't be empty");
    }

    std::unordered_set<char> char_set;

    int max_length = 0, left = 0, right = 0;

    while (right < str.size()) {
        if (char_set.find(str[right]) == char_set.end()) {
            char_set.insert(str[right++]);
            max_length = std::max(max_length, right - left);
        } else {
            char_set.erase(str[left++]);
        }
    }

    return max_length;
}

#include <cassert>
int main() {
    // TEST
    assert(LengthOfLongestNonRepeatingSubstring("testt") == 3);
    // TEST_END

     // TEST
    assert(LengthOfLongestNonRepeatingSubstring("abcd") == 4);
    // TEST_END

     // TEST
    assert(LengthOfLongestNonRepeatingSubstring("aaaa") == 1);
    // TEST_END

    // TEST
    assert(LengthOfLongestNonRepeatingSubstring("1") == 1);
    // TEST_END

    // TEST
    assert(LengthOfLongestNonRepeatingSubstring("@@#@##$#!") == 3);
    // TEST_END

    // TEST
    assert(LengthOfLongestNonRepeatingSubstring("a R T  YRz") == 4);
    // TEST_END

    // TEST
    try {
        LengthOfLongestNonRepeatingSubstring("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
