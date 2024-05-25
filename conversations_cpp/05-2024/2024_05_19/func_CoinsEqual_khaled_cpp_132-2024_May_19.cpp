/***
 * Prompt:




 khaled_cpp_132-2024_May_19: e4d2ab99-8197-4434-a627-8975cd1e1ece

 func_CoinsEqual_khaled_cpp_132-2024_May_19


Create a C++ function called CoinsEqual that takes two inputs, the first input non-empty array called coins of type std::vector<int>, and each coin value should be greater than 0. The second input is called divide_by of type int, and it should be less than or equal to the size of the coins input. This function should return a boolean try if we can divide the coins by divide_by parts, where all parts are equal, otherwise return false. Please don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

bool CoinsEqual(std::vector<int> coins, int divide_by) {
    if (coins.empty()) {
        throw std::invalid_argument("coins cannot be empty");
    }

    if (divide_by < 1) {
        throw std::invalid_argument("divide_by cannot be less than 1");
    }

    if (divide_by > coins.size()) {
        throw std::invalid_argument("divide_by cannot be greater than size of coins");
    }

    for (const int &coin : coins) {
        if (coin < 1) {
            throw std::invalid_argument("coin cannot be less than 1");
        }
    }

    auto total = std::accumulate(coins.begin(), coins.end(), decltype(coins)::value_type(0));

    if (total % divide_by != 0) {
        return false;
    }

    auto target = (total / divide_by);

    for (int div_count = 0; div_count < divide_by; div_count++) {
        std::vector<int> options;

        for (int idx = 0; idx < coins.size(); idx++) {
            if (coins[idx] <= target) {
                options.push_back(coins[idx]);
            }
        }

        std::sort(options.begin(), options.end());

        int sum = 0;
        for (int odx = options.size() - 1; odx >= 0; odx--) {
            if ((options[odx] + sum) <= target) {
                sum += options[odx];
                auto item = std::find(coins.begin(), coins.end(), options[odx]);

                if (item != coins.end()) {
                    coins.erase(item);
                }
            }
        }

        if (sum != target) {
            return false;
        }
    }

    return true;
}

#include <cassert>
int main() {
    // TEST
    assert((CoinsEqual({1, 2, 3, 2, 1, 3, 3}, 3) == true));
    // TEST_END

    // TEST
    assert((CoinsEqual({1, 2, 1}, 2) == true));
    // TEST_END

    // TEST
    assert((CoinsEqual({5, 2, 10, 1, 2}, 3) == false));
    // TEST_END

    // TEST
    assert((CoinsEqual({2, 4, 3, 2, 4, 9, 7, 7, 7, 9}, 3) == true));
    // TEST_END

    // TEST
    assert((CoinsEqual({1, 1, 1}, 3) == true));
    // TEST_END

    // TEST
    try {
        CoinsEqual({}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CoinsEqual({1}, 2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CoinsEqual({-1}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CoinsEqual({2}, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CoinsEqual({4}, -21);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}