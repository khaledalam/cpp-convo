/***






 khaled_cpp_160_2024_May_26: 18667205-3414-492f-8567-a0060b40d19d

 func_FirstAndLastPosition_khaled_cpp_160_2024_May_26




Create a C++ function called FirstAndLastPosition that takes two inputs, first input called nums of type
std::vector<int>, and the second input called target of type int.

This function should return another array of type std::vector<int> with only 2 elements that represents the 0-based
indexes of the first and last position of the target input and if the target does not exist in the numbers array
consider its index as -1. Please use the binary search algorithm in the solution, and don't forget to validate the
input.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> FirstAndLastPosition(const std::vector<int> &nums, int target) {
    if (nums.empty()) {
        throw std::invalid_argument("nums should not be empty");
    }

    for (int idx = 1; idx < nums.size(); idx++) {
        if (nums[idx] < nums[idx - 1]) {
            throw std::invalid_argument("nums should be sorted");
        }
    }

    auto FindPosition = [](const std::vector<int> &nums, int target, bool first) -> int {
        int left = 0, right = nums.size() - 1, result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                result = mid;
                if (first) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    };

    return {FindPosition(nums, target, true), FindPosition(nums, target, false)};
}

#include <cassert>
int main() {
    // TEST
    assert((FirstAndLastPosition({1, 2, 2, 4, 6}, 2) == std::vector<int>{1, 2}));
    // TEST_END

    // TEST
    assert((FirstAndLastPosition({1, 2, 4, 6}, 2) == std::vector<int>{1, 1}));
    // TEST_END

    // TEST
    assert((FirstAndLastPosition({1, 2, 4, 6}, -5) == std::vector<int>{-1, -1}));
    // TEST_END

    // TEST
    try {
        FirstAndLastPosition({}, 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FirstAndLastPosition({2, 4, 1}, 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}