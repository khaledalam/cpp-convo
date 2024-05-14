/***
 * Prompt:




 khaled_cpp_92-2024_May_11: e31b10a7-d371-44b1-9882-3b0b417ea475


func_EncodeStringUsingRunLengthTechnique_khaled_cpp_92-2024_May_11


 Create me a C++ function called EncodeStringUsingRunLengthTechnique which accepts one non-empty input string called input of type std::string which can contain any type of characters including spaces and special characters. Please make this function return another string of type std::string that represents the encoded input using the run-length encoding technique RLE. Consider that RTL operates on the principle of identifying consecutive occurrences of the same data value and replacing them with a single value and a count of how many times it repeats, so for example "AAAbbc" will be "3A2b1c". Please Don't forget to validate the input.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

std::string EncodeStringUsingRunLengthTechnique(const std::string &input) {
    if (input.empty()) {
        throw std::invalid_argument("input can't be empty");
    }

    std::string encoded;
    char current_char = input[0];
    int count = 1;
    for (size_t idx = 1; idx < input.size(); idx++) {
        if (input[idx] == current_char) {
            count++;
        } else {
            encoded += std::to_string(count) + current_char;
            current_char = input[idx];
            count = 1;
        }
    }
    encoded += std::to_string(count) + current_char;

    return encoded;
}

#include <cassert>
int main() {
    // TEST
    assert(EncodeStringUsingRunLengthTechnique("AAAbbc") == std::string("3A2b1c"));
    // TEST_END

    // TEST
    assert(EncodeStringUsingRunLengthTechnique("AAZbbxc") == std::string("2A1Z2b1x1c"));
    // TEST_END

    // TEST
    assert(EncodeStringUsingRunLengthTechnique("aaaaaaaaaaaa") == std::string("12a"));
    // TEST_END

    // TEST
    assert(EncodeStringUsingRunLengthTechnique("@@###") == std::string("2@3#"));
    // TEST_END

    // TEST
    assert(EncodeStringUsingRunLengthTechnique("AA   B") == std::string("2A3 1B"));
    // TEST_END

    // TEST
    try {
        EncodeStringUsingRunLengthTechnique("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
