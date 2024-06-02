/***






 khaled_cpp_182_2024_June_02: 6b74f4c3-aed2-451c-88ed-1eaae11d5db6

func_MaximizeTripleProduct_khaled_cpp_182_2024_June_02



Create a C++ function called MaximizeTripleProduct that takes a non-empty array of type std::vector<int>. The length of
the array should be greater than 2.

The function should return the maximum product of any three numbers in the array. Please don't forget to validate the
input.


*/

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <string>
#include <vector>

int MaximizeTripleProduct(std::vector<int> arr) {
    if (arr.size() < 3) {
        throw std::invalid_argument("array size should be at least 3");
    }

    int n_size = arr.size();
    int max_product = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;

    for (int idx = 0; idx < n_size; ++idx) {
        if (arr[idx] <= min1) {
            min2 = min1;
            min1 = arr[idx];
        } else if (arr[idx] <= min2) {
            min2 = arr[idx];
        }

        if (arr[idx] >= max1) {
            max3 = max2;
            max2 = max1;
            max1 = arr[idx];
        } else if (arr[idx] >= max2) {
            max3 = max2;
            max2 = arr[idx];
        } else if (arr[idx] >= max3) {
            max3 = arr[idx];
        }
    }

    max_product = std::max(max1 * max2 * max3, min1 * min2 * max1);

    return max_product;
}

#include <cassert>
int main() {
    // TEST
    assert(MaximizeTripleProduct({1, 2, 3, 4}) == 24);
    // TEST_END

    // TEST
    assert(MaximizeTripleProduct({-10, -10, 5, 2}) == 500);
    // TEST_END

    // TEST
    assert(MaximizeTripleProduct({-1, -2, -3, -4}) == -6);
    // TEST_END

    // TEST
    try {
        MaximizeTripleProduct({1, 2});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeTripleProduct({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
