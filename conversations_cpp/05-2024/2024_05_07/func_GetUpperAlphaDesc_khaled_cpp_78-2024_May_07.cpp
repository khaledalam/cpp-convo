/***
 * Prompt:

 khaled_cpp_78-2024_May_07: d9e63432-5219-4162-b8d8-911d53a50980


 func_GetUpperAlphaDesc_khaled_cpp_78-2024_May_07


 Create a C++ function called GetUpperAlphaDesc, it will accept a non-empty input called text of type std::string. Please make this function return another text of type std::string that contains only the uppercase letters that appear in the input and sort them in descending order. Please use lambda function in the solution.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>

std::string GetUpperAlphaDesc(std::string text) {
    if (text.empty()) {
        throw std::invalid_argument("text can't be empty");
    }

    std::string result = "";

    for (const char &character : text) {

        if (std::isalpha(character) && std::isupper(character)) {
            result += character;
        }
    }

    std::sort(result.begin(), result.end(), [](const char &first, const char &second) {
        return first > second;
    });

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(GetUpperAlphaDesc("ZaA") == std::string("ZA"));
    // TEST_END

    // TEST
    assert(GetUpperAlphaDesc("abC") == std::string("C"));
    // TEST_END

    // TEST
    assert(GetUpperAlphaDesc("ABc") == std::string("BA"));
    // TEST_END

    // TEST
    assert(GetUpperAlphaDesc("ABcCcVv") == std::string("VCBA"));
    // TEST_END

    // TEST
    assert(GetUpperAlphaDesc("ABC") == std::string("CBA"));
    // TEST_END

    // TEST
    assert(GetUpperAlphaDesc("12@") == std::string(""));
    // TEST_END

    // TEST
    assert(GetUpperAlphaDesc("1 G") == std::string("G"));
    // TEST_END

    // TEST
    try {
        GetUpperAlphaDesc("");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

