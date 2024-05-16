/***
 * Prompt:




 khaled_cpp_106-2024_May_14: 26a3e639-275c-4c18-b6da-ac947f83d32a


func_NumberSpeller_khaled_cpp_106-2024_May_14


Write a C++ function called NumberSpeller that accepts a number input called number of type int, this number should be between zero and 15.
this function should return a text of type std::string which represents the integer in English words. Please validate the inputs.

 */

#include <algorithm>

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

std::string NumberSpeller(int number) {
    if (number < 0) {
        throw std::invalid_argument("number can't be negative");
    }

    if (number > 15) {
        throw std::invalid_argument("number can't be greater than 15");
    }

    std::map<int, std::string> reader = {{0, "zero"},    {1, "one"},       {2, "two"},       {3, "three"},   {4, "four"}, {5, "five"},
                                         {6, "six"},     {7, "seven"},     {8, "eight"},     {9, "nine"},    {10, "ten"}, {11, "eleven"},
                                         {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"}};

    return reader[number];
}

#include <cassert>
int main() {
    // TEST
    assert(NumberSpeller(0) == std::string("zero"));
    // TEST_END

    // TEST
    assert(NumberSpeller(4) == std::string("four"));
    // TEST_END

    // TEST
    assert(NumberSpeller(13) == std::string("thirteen"));
    // TEST_END

    // TEST
    try {
        NumberSpeller(-1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        NumberSpeller(16);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
