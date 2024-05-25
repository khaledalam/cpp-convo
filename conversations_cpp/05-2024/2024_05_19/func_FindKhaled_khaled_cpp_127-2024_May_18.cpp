/***
 * Prompt:




 khaled_cpp_127-2024_May_18: a4e3039a-044c-440c-9cac-45456e29ac8e

 func_FindKhaled_khaled_cpp_127-2024_May_18


Create a C++ function called FindKhaled that takes one non-empty string called str that contains only spaces or alphabetic characters. This function should
search for "Khaled" word in the input str and return another string that mentions the position of the word "Khaled" in the str in this format: "I
found Khaled at X" where X is the 0-based location number, otherwise if didn't find the word "Khaled" return "I can't find Khaled :(". Please
note if the word "Khaled" existed more than once consider the first position of the word "Khaled". Don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

std::string FindKhaled(std::string str) {
    if (str.empty()) {
        throw std::invalid_argument("str can't be empty");
    }

    for (const char &character : str) {
        if (!std::isalpha(character) && character != ' ') {
            throw std::invalid_argument("str should contains only alphabetic characters");
        }
    }

    size_t find_loc = str.find("Khaled");

    if (find_loc != std::string::npos) {
        return "I found Khaled at " + std::to_string(find_loc) + "!";
    }

    return "I can't find Khaled :(";
}

#include <cassert>
int main() {
    // TEST
    assert(FindKhaled("This is Khaled") == "I found Khaled at 8!");
    // TEST_END

    // TEST
    assert(FindKhaled("This is khaled") == "I can't find Khaled :(");
    // TEST_END

    // TEST
    assert(FindKhaled("Khaled") == "I found Khaled at 0!");
    // TEST_END

    // TEST
    try {
        FindKhaled("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FindKhaled("Khaled!");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
