/***
 * Prompt:

 khaled_cpp_76-2024_May_05: 100e1f3d-5a95-4ba7-8152-8cfe47307c1b

 func_SortByCaseSensitivity_khaled_cpp_76-2024_May_05

 Design a C++ function called SortByCaseSensitivity, it should accept a non-empty input called text of type std::string. The function should return another sorted by case sensitivity text of type std::string. Sort by case sensitivity means that characters are sorted based on their case sensitivity, so lowercase letters should come first then uppercase letters, if we have 2 lowercase letters or 2 uppercase letters we sort them based on their alphabetic order. Please don't forget to validate non-alphabetic letters.

 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

std::string SortByCaseSensitivity(std::string text) {

    if (text.empty()) {
        throw std::invalid_argument("input can't be empty");
    }

    std::string upper = "", lower = "";

    for (const char character : text) {
        if (!isalpha(character)) {
            throw std::invalid_argument("characters should be alphabetic only");
        }

        if (isupper(character)) {
            upper += character;
        } else {
            lower += character;
        }
    }

    std::sort(lower.begin(), lower.end());

    std::sort(upper.begin(), upper.end());

    lower += upper;

    return lower;
}

#include <cassert>
int main() {
    // TEST
    assert(SortByCaseSensitivity("ABc") == std::string("cAB"));
    // TEST_END

    // TEST
    assert(SortByCaseSensitivity("AcB") == std::string("cAB"));
    // TEST_END

    // TEST
    assert(SortByCaseSensitivity("abc") == std::string("abc"));
    // TEST_END

    // TEST
    assert(SortByCaseSensitivity("caBA") == std::string("acAB"));
    // TEST_END

    // TEST
    assert(SortByCaseSensitivity("za") == std::string("az"));
    // TEST_END

    // TEST
    try {
        SortByCaseSensitivity("");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SortByCaseSensitivity("15vbA");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SortByCaseSensitivity("a b");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SortByCaseSensitivity("@");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

