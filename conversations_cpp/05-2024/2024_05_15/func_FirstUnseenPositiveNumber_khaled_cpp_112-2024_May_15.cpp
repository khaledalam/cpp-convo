/***
 * Prompt:




 khaled_cpp_112-2024_May_15: 8f3a5e85-0b95-4bc9-8e24-480d3dceabdc

func_FirstUnseenPositiveNumber_khaled_cpp_112-2024_May_15

Make me a C++ function called FirstUnseenPositiveNumber that takes a non-empty negative, zero, or positive numbers array called nums of type std::vector<int>. This function should return a number of type int that represents the first missing positive integer in an unsorted integer array. Please don't forget to validate the input.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int FirstMissingPositive(std::vector<int> nums) {
    int size = nums.size();

    if (size < 1) {
        throw std::invalid_argument("nums can't be empty");
    }

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
    assert(FirstMissingPositive({1, 2, 5}) == 3);
    // TEST_END

    // TEST
    assert(FirstMissingPositive({3, 4, -1, 1}) == 2);
    // TEST_END

     // TEST
    assert(FirstMissingPositive({0, -4, 2}) == 1);
    // TEST_END

    // TEST
    assert(FirstMissingPositive({-4}) == 1);
    // TEST_END

    // TEST
    try {
        FirstMissingPositive({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
