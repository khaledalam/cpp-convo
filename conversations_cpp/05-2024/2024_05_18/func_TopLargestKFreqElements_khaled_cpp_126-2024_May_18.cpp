/***
 * Prompt:




 khaled_cpp_126-2024_May_18: 00a43cc5-0688-4a26-b470-2c0f631a5b62

func_TopLargestKFreqElements_khaled_cpp_126-2024_May_18


Create a C++ function called TopLargestKFreqElements that takes two inputs, the first input is a non-empty array input called nums of type std::vector<int> that can contain negative, zero, or positive integers, and the second input is a number of type int called top_k. Please note that top_k can't be greater than the count of unique numbers in the input. This function should return a sorted array in ascending order of the k_top largest most frequent elements in the input list. Don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<int> TopLargestKFreqElements(std::vector<int> nums, int top_k) {
    if (nums.empty()) {
        throw std::invalid_argument("nums can't be empty");
    }

    if (top_k < 1) {
        throw std::invalid_argument("top_k can't be less than 1");
    }

    std::unordered_map<int, int> freq_map;
    std::set<int> sot;
    for (int num : nums) {
        freq_map[num]++;
        sot.insert(num);
    }

    if (sot.size() < top_k) {
        throw std::invalid_argument("top_k can't be greater than the count of unique numbers in the input");
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> min_heap;
    for (const auto &entry : freq_map) {
        min_heap.push({entry.second, entry.first});
        if (min_heap.size() > top_k) {
            min_heap.pop();
        }
    }

    std::vector<int> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top().second);
        min_heap.pop();
    }

    std::sort(result.begin(), result.end());

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((TopLargestKFreqElements({1, 2, 2, 3, 1, -1}, 1) == std::vector<int>{2}));
    // TEST_END

    // TEST
    assert((TopLargestKFreqElements({1, 2, 2, 3, 1}, 2) == std::vector<int>{1, 2}));
    // TEST_END

    // TEST
    assert((TopLargestKFreqElements({1, 1, 5, 5}, 1) == std::vector<int>{5}));
    // TEST_END

    // TEST
    assert((TopLargestKFreqElements({-50}, 1) == std::vector<int>{-50}));
    // TEST_END

    // TEST
    try {
        TopLargestKFreqElements({}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TopLargestKFreqElements({1}, -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TopLargestKFreqElements({1}, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TopLargestKFreqElements({1, 1, 5, 5}, 3);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
