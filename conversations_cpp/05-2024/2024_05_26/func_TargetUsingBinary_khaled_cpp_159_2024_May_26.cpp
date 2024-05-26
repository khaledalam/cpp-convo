/***






 khaled_cpp_159_2024_May_26: d430beff-c10b-4958-94c8-64cd5fe619de

 func_TargetUsingBinary_khaled_cpp_159_2024_May_26




Create a C++ function called TargetUsingBinary that takes two inputs of type std::vector<int> called numbers and
targets, both arrays can contain any negative, zero, or positive numbers.


This function should return another array of type std::vector<int> that represents the 0-based indexes of the targets
each index represents the location of the target number in the numbers array. Please use the binary search algorithm in
the solution and if some target does not exist in the numbers array consider its index as -1, don't forget to validate
the input.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> TargetUsingBinary(const std::vector<int> &numbers, const std::vector<int> &targets) {
    if (numbers.empty() || targets.empty()) {
        throw std::invalid_argument("numbers and target should not be empty");
    }

    std::vector<std::pair<int, int>> indexed_numbers;

    for (size_t idx = 0; idx < numbers.size(); ++idx) {
        indexed_numbers.push_back(std::make_pair(numbers[idx], idx));
    }

    std::sort(indexed_numbers.begin(), indexed_numbers.end());

    auto BinarySearch = [](const std::vector<std::pair<int, int>> &sorted_nums, int target) -> int {
        int left = 0;
        int right = sorted_nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (sorted_nums[mid].first == target) {
                return sorted_nums[mid].second;
            } else if (sorted_nums[mid].first < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    };

    std::vector<int> result;
    result.reserve(targets.size());

    for (const int &target : targets) {
        result.push_back(BinarySearch(indexed_numbers, target));
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((TargetUsingBinary({1, 5, -4, 0, 6}, {5, -3}) == std::vector<int>{1, -1}));
    // TEST_END

    // TEST
    assert((TargetUsingBinary({1, 5}, {5, 5, 5, 1}) == std::vector<int>{1, 1, 1, 0}));
    // TEST_END

    // TEST
    assert((TargetUsingBinary({1, 5}, {-6}) == std::vector<int>{-1}));
    // TEST_END

    // TEST
    try {
        TargetUsingBinary({}, {1});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TargetUsingBinary({-2}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TargetUsingBinary({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}