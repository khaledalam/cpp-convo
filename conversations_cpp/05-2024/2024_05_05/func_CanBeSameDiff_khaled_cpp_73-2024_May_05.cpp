/***
 * Prompt:

 khaled_cpp_73-2024_May_05: 4e150a17-86fd-4696-a2f4-4fcba4d826bf

 func_CanBeSameDiff_khaled_cpp_73-2024_May_05

 Design a C++ function called CanBeSameDiff, it will accept empty or non-empty input called text of type std::string. Please make this function to return a boolean true if we can switch case sensitivity of the text input to any case and/or sort text input in any order so that the difference between each 2 characters always be the same otherwise return false. Please also note that difference between 2 characters is the difference between their ascii value.


 */

#include <stdexcept>

#include <iostream>
#include <algorithm>
#include <string>

bool CanBeSameDiff(std::string text) {

    if (text.length() < 2) {
        return true;
    }

    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    std::sort(text.begin(), text.end());

    int diff = (text[1] - text[0]);

    for (int idx = 1; idx < text.length(); idx++) {
        if (text[idx] - text[idx - 1] != diff) {
            return false;
        }
    }

    return true;
}

#include <cassert>
int main() {
    // TEST
    assert(CanBeSameDiff("abc") == true);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("abC") == true);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("abd") == false);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("abcde") == true);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("A!") == true);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("147") == true);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("ab") == true);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("ab.") == false);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("") == true);
    // TEST_END

    // TEST
    assert(CanBeSameDiff("a") == true);
    // TEST_END
}

