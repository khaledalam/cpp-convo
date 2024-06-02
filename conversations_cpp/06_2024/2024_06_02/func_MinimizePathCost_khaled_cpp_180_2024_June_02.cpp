/***






 khaled_cpp_180_2024_June_02: 1fbe5f9e-cb3b-4287-a9ca-064b63ae89ae

 func_MinimizePathCost_khaled_cpp_180_2024_June_02


Create a C++ function called MinimizePathCost that takes two non-empty arrays of type std::vector<long long>, the length of
both of them should be the same and should be greater than 2.

There are n points along a path, and the i-th point has a height given by heights-i. We want to travel from the first
point to the last point by visiting exactly three points in total, such that the height increases at each step (i.e.,
heights-i < heights-j < heights-k for i < j < k).

The cost to travel from one point to another is given by costs-i.

This function should return a number of type int that represents the smallest travel cost. Note that return -1 if no result. Please don't forget to
validate the input.


*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const long long inf = 1e18;

int MinimizePathCost(std::vector<long long> heights, std::vector<long long> costs) {
    if (heights.size() < 3 || costs.size() < 3) {
        throw std::invalid_argument("heights and costs sizes should be at least 3");
    }

    if (heights.size() != costs.size()) {
        throw std::invalid_argument("heights and costs sizes should be the same");
    }

    int n_size = heights.size();
    std::vector<long long> dynamic(n_size, inf);
    long long ans = inf;

    for (int idx = 0; idx < n_size; ++idx) {
        for (int jdx = idx + 1; jdx < n_size; ++jdx) {
            if (heights[idx] < heights[jdx]) {
                dynamic[jdx] = std::min(dynamic[jdx], costs[idx] + costs[jdx]);
                ans = std::min(ans, dynamic[idx] + costs[jdx]);
            }
        }
    }

    return ans == inf ? -1 : ans;
}

#include <cassert>
int main() {
    // TEST
    assert(MinimizePathCost({1, 3, 5, 7, 9}, {10, 20, 30, 40, 50}) == 60);
    // TEST_END

    // TEST
    assert(MinimizePathCost({5, 4, 3, 2, 1}, {10, 20, 30, 40, 50}) == -1);
    // TEST_END

    // TEST
    assert(MinimizePathCost({1, 2, 3, 4, 5, 6, 7}, {10, 20, 30, 40, 50, 60, 70}) == 60);
    // TEST_END

    // TEST
    try {
        MinimizePathCost({1, 2}, {1, 2});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinimizePathCost({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
