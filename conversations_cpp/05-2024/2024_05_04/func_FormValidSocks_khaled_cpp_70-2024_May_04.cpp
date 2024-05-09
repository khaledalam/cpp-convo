/***
 * Prompt:


 khaled_cpp_70-2024_May_04: f5e68bb1-6333-4d9b-bb9f-5b69050a2b91

 func_FormValidSocks_khaled_cpp_70-2024_May_04


 Write me a C++ function called FormValidSocks, it will accept one input called socks_colors of type std::vector<int> which represent list of the color number of each sock. This function should return number of type int that represent how many socks that we can form from the input list. Please note that we can form socks using 2 sock of the same color. Please also note that socks_colors can't be empty so please throw invalid_argument with message "socks_colors can't be empty" if the input list is empty, last note is that sock color can be negative, zero or positive number.


 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>

int FormValidSocks(const std::vector<int> &socks_colors) {
    if (socks_colors.empty()) {
        throw std::invalid_argument("socks_colors can't be empty");
    }

    std::map<int, int> freq;

    for (const int &color : socks_colors) {
        freq[color]++;
    }

    int result = 0;
    for (const std::pair<int, int> color : freq) {
        result += color.second / 2;
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(FormValidSocks( { 1, 1, 2, 3 }) == 1);
    // TEST_END

    // TEST
    assert(FormValidSocks( { 1, 1, 1, 3 }) == 1);
    // TEST_END

    // TEST
    assert(FormValidSocks( { 1, 1, 1, 1 }) == 2);
    // TEST_END

    // TEST
    assert(FormValidSocks( { 1, 0, 0 }) == 1);
    // TEST_END

    // TEST
    assert(FormValidSocks( { -1, 1, -1, -1, -3, -3, -3, 0, -3 }) == 3);
    // TEST_END

    // TEST
    assert(FormValidSocks( { 1, 1, 2, 2 }) == 2);
    // TEST_END

    // TEST
    assert(FormValidSocks( { 1 }) == 0);
    // TEST_END

    // TEST
    assert(FormValidSocks( { 1, 1, 2, 2, 1, 1, 1 }) == 3);
    // TEST_END

    // TEST
    try {
        FormValidSocks( { });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(std::string(e.what()) == "socks_colors can't be empty");
    }
    // TEST_END
}

