/***
 * Prompt:




 khaled_cpp_111-2024_May_15: a8badebb-d8bf-4133-88dc-83030d0344e6


func_AddOne_khaled_cpp_111-2024_May_15


Make me a C++ function called AddOne that takes a non-empty array input of type std::vector<int> which represent decimal digits representing a
non-negative integer. This function should adds one to this number and return another array of type std::vector<int> which represent the number
after adding 1 to it. Please don't forget to validate the inputs.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> AddOne(const std::vector<int> &digits) {
    if (digits.empty()) {
        throw std::invalid_argument("digits can't be empty");
    }

    for (const int &digit : digits) {
        if (digit < 0) {
            throw std::invalid_argument("digit can't be below 0");
        }
    }
    std::vector<int> result(digits);

    int size = digits.size();

    for (int idx = size - 1; idx >= 0; --idx) {
        if (result[idx] < 9) {
            result[idx]++;
            return result;
        } else {
            result[idx] = 0;
        }
    }

    result.insert(result.begin(), 1);

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((AddOne({1, 2}) == std::vector<int>{1, 3}));
    // TEST_END

    // TEST
    assert((AddOne({9, 9}) == std::vector<int>{1, 0, 0}));
    // TEST_END

    // TEST
    assert((AddOne({0}) == std::vector<int>{1}));
    // TEST_END

    // TEST
    assert((AddOne({8,9}) == std::vector<int>{9, 0}));
    // TEST_END

    // TEST
    try {
        AddOne({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AddOne({-1});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
