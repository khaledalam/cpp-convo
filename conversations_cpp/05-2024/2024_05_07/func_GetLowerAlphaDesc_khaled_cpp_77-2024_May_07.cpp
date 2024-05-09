/***
 * Prompt:

 khaled_cpp_77-2024_May_07: c89225c2-6279-4ea2-92b9-73bc14d7e5e5

 func_GetLowerAlphaDesc_khaled_cpp_77-2024_May_07

 Design me a C++ function called GetLowerAlphaDesc, it will accept a non-empty input called text of type std::string. Please make this function return another text of type std::string that contains only the lowercase letters that appear in the input and sort them in descending order. Please use lambda function in the solution.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>

std::string GetLowerAlphaDesc(std::string text) {
    if (text.empty()) {
        throw std::invalid_argument("text can't be empty");
    }

    std::string result = "";

    for (const char &character : text) {

        if (std::isalpha(character) && std::islower(character)) {
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
    assert(GetLowerAlphaDesc("Zabc") == std::string("cba"));
    // TEST_END

    // TEST
    assert(GetLowerAlphaDesc("abC") == std::string("ba"));
    // TEST_END

    // TEST
    assert(GetLowerAlphaDesc("ABc") == std::string("c"));
    // TEST_END

    // TEST
    assert(GetLowerAlphaDesc("ABcCcVv") == std::string("vcc"));
    // TEST_END

    // TEST
    assert(GetLowerAlphaDesc("ABC") == std::string(""));
    // TEST_END

    // TEST
    assert(GetLowerAlphaDesc("12@") == std::string(""));
    // TEST_END

    // TEST
    assert(GetLowerAlphaDesc("1 c") == std::string("c"));
    // TEST_END

    // TEST
    try {
        GetLowerAlphaDesc("");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

