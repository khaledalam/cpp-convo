/***






 khaled_cpp_189_2024_June_02: d7e4eaef-b860-4ecf-b186-bb0798b81f85

func_FindMedian_khaled_cpp_189_2024_June_02


Design me a C++ function called FindMedian that takes one input: a non-empty vector of integers called nums of type
const std::vector<int>. This function should return the median of the array of type double. If the array length is even, it should
return the average of the two middle elements. Use two heaps (a max-heap and a min-heap) to implement the solution.
Please don't forget to validate the input.


*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

double FindMedian(const std::vector<int> &nums) {
    if (nums.empty()) {
        throw std::invalid_argument("nums cannot be empty");
    }

    std::priority_queue<int> max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    for (const int &num : nums) {
        max_heap.push(num);
        min_heap.push(max_heap.top());
        max_heap.pop();

        if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    if (max_heap.size() > min_heap.size()) {
        return max_heap.top();
    } else {
        return (max_heap.top() + min_heap.top()) / 2.0;
    }
}

#include <cassert>
int main() {
    // TEST
    assert(FindMedian({1, 2, 3}) == 2.0);
    // TEST_END

    // TEST
    assert(FindMedian({1, 2, 3, 4}) == 2.5);
    // TEST_END

    // TEST
    assert(FindMedian({7, 1, 3, 4, 5, 6, 2}) == 4.0);
    // TEST_END

    // TEST
    try {
        FindMedian({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
