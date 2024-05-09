/***
 * Prompt:




 khaled_cpp_15_2024_18_04: d634ad5b-32da-4678-974d-312754b1a877










 Give me a C++ function named ColorMe that accepts two inputs first one non-empty list called indexes of type std::vector<int> and second one called colors of type std::string. The first input is a list of numbers minimum 0 and maximum 1000 and it represents the index that need to be colored using the color character of same index from second input. The second input is string represents the colors which each character can be lowercase or uppercase of R, G, and B. Please note that both inputs should be with the same size. The function should returns the final colored uppercase string of type std::string. Please note that if you try to color some index with same color twice the the output color of this index will be "_" which means no color and the initial value of non-colored indexes is "_" as well. Last note don't forget to validate the inputs.



 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string ColorMe(std::vector<int> indexes, std::string colors) {

    if (indexes.empty()) {
        throw std::invalid_argument("indexes can't be empty");
    }

    int max_index = *std::max_element(indexes.begin(), indexes.end());
    int min_index = *std::min_element(indexes.begin(), indexes.end());

    if (min_index < 0 || max_index > 1000 || indexes.size() != colors.length()) {
        throw std::invalid_argument("Invalid range");
    }

    for (char &ch : colors) {
        ch = toupper(ch);

        if (ch != 'R' && ch != 'G' && ch != 'B') {
            throw std::invalid_argument("Invalid color");
        }
    }

    std::string colored_output(max_index + 1, '_');

    int index_color = 0;
    for (const int &index : indexes) {

        if (colored_output[index] == colors[index_color]) {
            colored_output[index] = '_';
        } else {
            colored_output[index] = colors[index_color];
        }

        index_color++;
    }

    return colored_output;
}

#include <cassert>
int main() {
    // TEST
    std::vector<int> input1 = { 0, 1, 2 };
    std::string input2 = "rBg";
    std::string output = std::string("RBG");
    assert(ColorMe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 0, 0, 2 };
    input2 = "RRG";
    output = std::string("__G");
    assert(ColorMe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 0, 0 };
    input2 = "BB";
    output = std::string("_");
    assert(ColorMe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 0, 0 };
    input2 = "BG";
    output = std::string("G");
    assert(ColorMe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 0, 1, -1 };
    input2 = "rBg";
    try {
        ColorMe(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = { 0, 1, 1001 };
    input2 = "rBg";
    try {
        ColorMe(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = { };
    input2 = "rBH";
    try {
        ColorMe(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = { 0, 1, 2 };
    input2 = "rBH";
    try {
        ColorMe(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = { 0, 1, 2 };
    input2 = "rB";
    try {
        assert(ColorMe(input1, input2) == output);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
