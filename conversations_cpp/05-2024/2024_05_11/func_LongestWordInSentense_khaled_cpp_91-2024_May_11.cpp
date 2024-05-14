/***
 * Prompt:




 khaled_cpp_91-2024_May_11: b08d7927-1905-44f8-844c-93b805fc5159

func_LongestWordInSentense_khaled_cpp_91-2024_May_11

 Create me a C++ function called LongestWordInSentense which accepts one non-empty input string called text of type std::string. Please make
 this function return a number of type int that represent the length of the longest word in the text. Consider that the word can consist of
 any alphabetic, digit or special character, the distance between the word and another is a single or multiple spaces. Please Don't forget
 to validate the input.




 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

int LongestWordInSentense(const std::string &text) {
    if (text.empty()) {
        throw std::invalid_argument("text can't be empty");
    }

    std::stringstream stringstreamer;
    std::string word;

    stringstreamer << text;

    int longest_length = 0;

    while (stringstreamer >> word) {
        longest_length = std::max(longest_length, (int)word.length());
    }

    return longest_length;
}

#include <cassert>
int main() {
    // TEST
    assert(LongestWordInSentense("Test word.") == 5);
    // TEST_END

    // TEST
    assert(LongestWordInSentense("Test word and LongABC") == 7);
    // TEST_END

    // TEST
    assert(LongestWordInSentense("## @@@ *$") == 3);
    // TEST_END

    // TEST
    assert(LongestWordInSentense("A") == 1);
    // TEST_END

    // TEST
    try {
        LongestWordInSentense("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
