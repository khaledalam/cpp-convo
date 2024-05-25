/***
 * Prompt:




 khaled_cpp_144_-2024_May_24: e9b44256-2e78-4620-8645-23b85681d8c5

 func_IdenticalFuncStrings_khaled_cpp_144_-2024_May_24


Create a C++ function called IdenticalFuncStrings that takes 2 inputs, the first input is a non-empty list called words
of type of type std::vector<std::string> and the second input is called atleast_identical_chars_needed of type int that
should be greater than zero. This function should return another list of type std::vector<std::string> that represents
the strings that have at least atleast_identical_chars_needed identical characters. Please don't forget to validate the
inputs.


 */

#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> IdenticalFuncStrings(std::vector<std::string> words, int atleast_identical_chars_needed) {

    if (words.empty()) {
        throw std::invalid_argument("words can't be empty");
    }

    if (atleast_identical_chars_needed <= 0) {
        throw std::invalid_argument("atleast_identical_chars_needed should be be grater than 0");
    }

    std::vector<std::string> result;

    for (int idx = 0; idx < words.size(); idx++) {

        std::map<char, int> freq;

        for (const char &character : words[idx]) {
            freq[character]++;

            if (freq[character] >= atleast_identical_chars_needed) {
                result.push_back(words[idx]);
                break;
            }
        }
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((IdenticalFuncStrings({"testtest", "abc"}, 4) == std::vector<std::string>{"testtest"}));
    // TEST_END

    // TEST
    assert((IdenticalFuncStrings({"abc", "abc"}, 1) == std::vector<std::string>{"abc", "abc"}));
    // TEST_END

    // TEST
    assert((IdenticalFuncStrings({"$$", "@", "abcc"}, 2) == std::vector<std::string>{
                                                                "$$",
                                                                "abcc",
                                                            }));
    // TEST_END

    // TEST
    try {
        IdenticalFuncStrings({}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IdenticalFuncStrings({"abc"}, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IdenticalFuncStrings({"abc"}, -2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}