/***
 * Prompt:




 khaled_cpp_114-2024_May_17: c51cf74d-aaca-4629-9849-d3d9c41dca49

 func_SortByAbsolute_khaled_cpp_114-2024_May_17



Design a C++ function called SortByAbsolute that takes a non-empty numbers array between a range of -100 and 100, this input is called nums of type std::vector<int>. This function should return another sorted array of type std::vector<int>, this array should be sorted by their absolute values using a lambda function. Please don't forget to validate the input.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> SortByAbsoluteValues(const std::vector<int> nums) {
    if (nums.empty()) {
        throw std::invalid_argument("nums array should not be empty");
    }

    for (int num : nums) {
        if (num < -100 || num > 100) {
            throw std::invalid_argument("num should be between range -100 and 100");
        }
    }
    std::vector<int> sorted_nums = nums;

    std::sort(sorted_nums.begin(), sorted_nums.end(), [](int first, int second) { return std::abs(first) < std::abs(second); });

    return sorted_nums;
}

#include <cassert>
int main() {
    // TEST
    assert((SortByAbsoluteValues({-1, 2, -5}) == std::vector<int>{-1, 2, -5}));
    // TEST_END

    // TEST
    assert((SortByAbsoluteValues({1, 0, -4}) == std::vector<int>{0, 1, -4}));
    // TEST_END

    // TEST
    assert((SortByAbsoluteValues({-4}) == std::vector<int>{-4}));
    // TEST_END

    // TEST
    try {
        SortByAbsoluteValues({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SortByAbsoluteValues({-102});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SortByAbsoluteValues({105});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
