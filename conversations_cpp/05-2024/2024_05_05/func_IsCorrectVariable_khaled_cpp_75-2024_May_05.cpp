/***
 * Prompt:

 khaled_cpp_75-2024_May_05: 1d8331ef-f83a-4757-a3b9-03fa3deb846f


 func_IsCorrectVariable_khaled_cpp_75-2024_May_05


 Design a C++ function called IsCorrectVariable, it will 2 inputs, first one will be an empty or non-empty input called variable_name of type std::string, second one will be a number of type int called variable_min_length its value should be greater than or equal to 2. Please make this function return a boolean true if the variable name is greater than or equal variable_min_length in length, all its characters are alphabetic and lowercase only otherwise return false. Please note that underscore, digits, and special characters are not allowed.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>

bool IsCorrectVariable(std::string variable_name, int variable_min_length) {
    if (variable_min_length < 2) {
        throw std::invalid_argument("variable_min_length should be greater than or equal to 2");
    }

    if (variable_name.length() < variable_min_length) {
        return false;
    }

    std::string another_var = variable_name;

    std::transform(another_var.begin(), another_var.end(), another_var.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    if (another_var != variable_name) {
        return false;
    }

    for (const char &character : variable_name) {
        if (!std::isalpha(character)) {
            return false;
        }
    }

    return true;
}

#include <cassert>
int main() {
    // TEST
    assert(IsCorrectVariable("test", 3) == true);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("it", 3) == false);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("it", 2) == true);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("oka", 3) == true);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("", 3) == false);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("thisistest", 3) == true);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("tr t", 3) == false);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("itebsd", 5) == true);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("test_", 3) == false);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("A", 3) == false);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("abc@", 3) == false);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("aaa4", 3) == false);
    // TEST_END

    // TEST
    assert(IsCorrectVariable("aw", 2) == true);
    // TEST_END

    // TEST
    try {
        IsCorrectVariable("fas", 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

