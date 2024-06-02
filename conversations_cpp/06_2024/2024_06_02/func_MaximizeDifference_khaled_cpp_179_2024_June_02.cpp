/***






 khaled_cpp_179_2024_June_02: cebed619-babf-4a17-979b-941e694ca04b

 func_MaximizeDifference_khaled_cpp_179_2024_June_02


Design me a C++ function called MaximizeDifference that takes 2 non-empty arrays of type std::vector<int>, the length of
both of them should be the same and should be greater than 2.

There are n elements, and the i-th element has a value given by values-i and a cost given by costs-i. We want to select
exactly three elements such that their indices i < j < k and the sum of their values minus the sum of their costs is
maximized.

The function should return a number of type int that represents the maximum difference. Please don't forget to validate
the input.


*/

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <string>
#include <vector>

int MaximizeDifference(std::vector<int> values, std::vector<int> costs) {
    if (values.size() < 3 || costs.size() < 3) {
        throw std::invalid_argument("values and costs sizes should be at least 3");
    }

    if (values.size() != costs.size()) {
        throw std::invalid_argument("values and costs sizes should be the same");
    }

    int nnn = values.size();
    int max_diff = INT_MIN;

    for (int iii = 0; iii < nnn - 2; ++iii) {
        for (int jjj = iii + 1; jjj < nnn - 1; ++jjj) {
            for (int kkk = jjj + 1; kkk < nnn; ++kkk) {
                int diff = (values[iii] + values[jjj] + values[kkk]) - (costs[iii] + costs[jjj] + costs[kkk]);
                max_diff = std::max(max_diff, diff);
            }
        }
    }

    return max_diff;
}

#include <cassert>
int main() {
    // TEST
    assert(MaximizeDifference({1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}) == 6);
    // TEST_END

    // TEST
    assert(MaximizeDifference({10, 20, 30, 40, 50}, {1, 2, 3, 4, 5}) == 108);
    // TEST_END

    // TEST
    assert(MaximizeDifference({5, 5, 5}, {5, 5, 5}) == 0);
    // TEST_END

    // TEST
    try {
        MaximizeDifference({1, 2}, {1, 2});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeDifference({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeDifference({1, 2, 3, 4}, {1, 4, 5, 6, 7, 8});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
