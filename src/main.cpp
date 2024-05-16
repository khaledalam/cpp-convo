/***
 * Prompt:




 khaled_cpp_112-2024_May_15:


Make me a C++ function called FirstUnseenPositiveNumber that takes a non-empty array input of type std::vector<int> which represent decimal digits representing a
non-negative integer. This function should adds one to this number and return another array of type std::vector<int> which represent the number
after adding 1 to it. Please don't forget to validate the inputs.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int FirstMissingPositive(std::vector<int>& nums) {
    int size = nums.size();

    for (int idx = 0; idx < size; ++idx) {
        while (nums[idx] > 0 && nums[idx] <= size && nums[nums[idx] - 1] != nums[idx]) {
            std::swap(nums[idx], nums[nums[idx] - 1]);
        }
    }

    for (int idx = 0; idx < size; ++idx) {
        if (nums[idx] != idx + 1) {
            return idx + 1;
        }
    }

    return size + 1;
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
