/***
 * Prompt:




 khaled_cpp_124-2024_May_18: b63c1659-521e-4418-ad96-c753c0d38510

 func_CandyKids_khaled_cpp_124-2024_May_18


Create a C++ function called CandyKids that takes one non-empty array input called marks of type std::vector<int>, each item should be either zero or positive number. This function should return a number of type int that represents the minimum number of candies required to distribute to kids such that each kid must have at least one candy and kids with higher marks get more candies than their neighbors. Please don't forget to validate the input.




 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

int CandyKids(const std::vector<int> &marks) {
    int n_size = marks.size();
    if (n_size == 0) {
        throw std::invalid_argument("marks can't be empty");
    }

    if (marks[0] < 0) {
        throw std::invalid_argument("mark can't be less than 0");
    }

    std::vector<int> candies(n_size, 1);

    for (int idx = 1; idx < n_size; ++idx) {
        if (marks[idx] < 0) {
            throw std::invalid_argument("mark can't be less than 0");
        }

        if (marks[idx] > marks[idx - 1]) {
            candies[idx] = candies[idx - 1] + 1;
        }
    }

    for (int idx = n_size - 2; idx >= 0; --idx) {
        if (marks[idx] > marks[idx + 1]) {
            candies[idx] = std::max(candies[idx], candies[idx + 1] + 1);
        }
    }

    return std::accumulate(candies.begin(), candies.end(), 0);
}

#include <cassert>
int main() {
    // TEST
    assert(CandyKids({1, 0, 3}) == 5);
    // TEST_END

    // TEST
    assert(CandyKids({0}) == 1);
    // TEST_END

    // TEST
    assert(CandyKids({0, 1, 0}) == 4);
    // TEST_END

    // TEST
    assert(CandyKids({0, 1, 0, 1}) == 6);
    // TEST_END

    // TEST
    try {
        CandyKids({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CandyKids({-1});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CandyKids({1, -5});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
