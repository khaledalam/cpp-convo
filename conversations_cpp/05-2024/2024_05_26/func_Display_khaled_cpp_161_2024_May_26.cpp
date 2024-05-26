/***






 khaled_cpp_161_2024_May_26: 3e257aa0-9c2b-44ee-a1ac-c970396b5160

 func_Display_khaled_cpp_161_2024_May_26


Create a C++ function called Display that takes 2 non-empty arrays of type std::vector<int>, the length of both of them
should be the same and should be greater than 2.

There are n displays placed along a road, and the i-th of them can display text with font size fonts-i only. We want to
rent such three displays with indices i<j<k that the font size increases if you move along the road in a particular
direction. Namely, the condition si<sj<sk should be held.

The rent cost for the i-th display is rents-i

This function should return a number of type int that represent the smallest cost that we should pay. Please don't
forget to validate the input.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const long long inf = 1e18;

int Display(std::vector<int> fonts, std::vector<int> rents) {
    if (fonts.size() < 3 || rents.size() < 3) {
        throw std::invalid_argument("fonts and rents sizes should be with at least 3");
    }

    if (fonts.size() != rents.size()) {
        throw std::invalid_argument("fonts and rents sizes should be the same");
    }

    int n_size = fonts.size();

    std::vector<long long> dynamic(n_size + 1);

    for (int idx = 0; idx < n_size; ++idx) {
        dynamic[idx] = inf;
    }

    long long ans = inf;
    for (int idx = 0; idx < n_size; ++idx) {
        for (int jdx = idx + 1; jdx < n_size; ++jdx) {
            if (fonts[idx] < fonts[jdx]) {

                if (rents[idx] + rents[jdx] < dynamic[jdx]) {
                    dynamic[jdx] = rents[idx] + rents[jdx];
                }

                if (dynamic[idx] + rents[jdx] < ans) {
                    ans = dynamic[idx] + rents[jdx];
                }
            }
        }
    }

    if (ans != inf) {
        return ans;
    } else {
        return -1;
    }
}

#include <cassert>
int main() {
    // TEST
    assert(Display({2, 4, 5, 4, 10}, {40, 30, 20, 10, 40}) == 90);
    // TEST_END

    // TEST
    assert(Display({100, 101, 100}, {2, 4, 5}) == -1);
    // TEST_END

    // TEST
    assert(Display({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {10, 13, 11, 14, 15, 12, 13, 13, 18, 13}) == 33);
    // TEST_END

    // TEST
    try {
        Display({1, 2}, {1, 2});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Display({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Display({1, 2, 3, 4}, {1, 4, 5, 6, 7, 8});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}