/***






 khaled_cpp_181_2024_June_02: 5f001a1a-8461-4f35-8bf2-36ef7974c798

 func_MaximizeProduct_khaled_cpp_181_2024_June_02


Create a C++ function called MaximizeProduct that takes two non-empty arrays of type std::vector<int>, the length of
both of them should be the same and should be greater than 2.

There are n items, and the i-th item has a value given by values-i and a weight given by weights-i. We want to select
exactly three items such that their indices i < j < k and the value increases at each step (i.e., values-i < values-j <
values-k).

The total product of the selected items is given by multiplying their weights. If there is no results return -1.

This function should return a number of type int that represents the maximum product. Please don't forget to validate
the input.


*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const long long inf = -1e18;

int MaximizeProduct(std::vector<int> values, std::vector<int> weights) {
    if (values.size() < 3 || weights.size() < 3) {
        throw std::invalid_argument("values and weights sizes should be at least 3");
    }

    if (values.size() != weights.size()) {
        throw std::invalid_argument("values and weights sizes should be the same");
    }

    int n_size = values.size();
    std::vector<long long> dynamic(n_size, inf);
    long long max_product = inf;

    for (int idx = 0; idx < n_size; ++idx) {
        for (int jdx = idx + 1; jdx < n_size; ++jdx) {
            if (values[idx] < values[jdx]) {
                dynamic[jdx] = std::max(dynamic[jdx], static_cast<long long>(weights[idx] * weights[jdx]));
                max_product = std::max(max_product, dynamic[idx] * weights[jdx]);
            }
        }
    }

    return max_product == inf ? -1 : max_product;
}

#include <cassert>
int main() {
    // TEST
    assert(MaximizeProduct({1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}) == 60);
    // TEST_END

    // TEST
    assert(MaximizeProduct({5, 4, 3, 2, 1}, {1, 2, 3, 4, 5}) == -1);
    // TEST_END

    // TEST
    assert(MaximizeProduct({1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}) == 120);
    // TEST_END

    // TEST
    try {
        MaximizeProduct({1, 2}, {1, 2});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeProduct({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
