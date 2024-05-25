/***
 * Prompt:




 khaled_cpp_112-2024_May_15: 702a7727-4095-4b5b-9323-9024d7b62a20

 func_ItemsDuplicates_khaled_cpp_112-2024_May_15



Make me a C++ function called ItemsDuplicates that takes a non-empty negative, zero, or positive numbers array called nums of type
std::vector<int>. This function should return another sorted array of type std::vector<int> that contains the duplicate items in the input array.
Please note that the return array should be sorted in ascending order and please don't forget to validate the input.




 */

#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> ItemsDuplicates(std::vector<int> nums) {
    if (nums.empty()) {
        throw std::invalid_argument("nums can't be empty");
    }

    std::vector<int> result;
    std::set<int> sot;

    for (int item : nums) {
        int sot_size = sot.size();
        sot.insert(item);
        if (sot_size == sot.size()) {
            if (std::find(result.begin(), result.end(), item) == result.end()) {
                result.push_back(item);
            }
        }
    }
    std::sort(result.begin(), result.end());

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((ItemsDuplicates({1, 2, 5, 5}) == std::vector<int> {5}));
    // TEST_END

    // TEST
    assert((ItemsDuplicates({-1, 0, 0, -2, -1}) == std::vector<int>{-1, 0}));
    // TEST_END

    // TEST
    assert((ItemsDuplicates({5, 5, 0, 0}) == std::vector<int>{0, 5}));
    // TEST_END

    // TEST
    assert((ItemsDuplicates({-4}) == std::vector<int>{}));
    // TEST_END

    // TEST
    try {
        ItemsDuplicates({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
