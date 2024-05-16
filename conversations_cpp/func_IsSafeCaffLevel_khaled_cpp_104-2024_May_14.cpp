/***
 * Prompt:




 khaled_cpp_104-2024_May_14: 44567d72-7eac-4c1a-96c8-3d1bf644d6d8


func_IsSafeCaffLevel_khaled_cpp_104-2024_May_14

Write a C++ function called IsSafeCaffLevel that accepts two inputs, first one non-empty list called levels of type std::vector<int> which
represents the caffeine levels during continuous days and it should be between 0 and 100, second input is called max_weekly_level which
should be zero or positive number. This function should return a Boolean true if the sum of levels per each week is less than or equal to
max_weekly_level otherwise return false. Please validate the inputs.

 */

#include <algorithm>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool IsSafeCaffLevel(std::vector<int> levels, int max_weekly_level) {
    if (levels.empty()) {
        throw std::invalid_argument("levels can't be empty");
    }

    if (max_weekly_level < 0) {
        throw std::invalid_argument("max_weekly_level can't be less than zero");
    }

    int sum = 0, week = 0;

    for (const int &level : levels) {
        if (level < 0) {
            throw std::invalid_argument("level can't be less than zero");
        }

        if (level > 100) {
            throw std::invalid_argument("level can't be higher than hundred");
        }

        sum += level;
        week++;

        if (sum > max_weekly_level) {
            return false;
        }

        if (week == 7) {
            week = sum = 0;
        }
    }

    return true;
}

#include <cassert>
int main() {
    // TEST
    assert(IsSafeCaffLevel({1, 2, 3}, 3) == false);
    // TEST_END

    // TEST
    assert(IsSafeCaffLevel({1, 2, 3}, 7) == true);
    // TEST_END

    // TEST
    assert(IsSafeCaffLevel({1, 1, 1, 1, 1, 1, 1, 1, 1}, 7) == true);
    // TEST_END

    // TEST
    assert(IsSafeCaffLevel({1, 1, 1, 1, 1, 1, 1, 1, 6}, 7) == true);
    // TEST_END

    // TEST
    assert(IsSafeCaffLevel({2, 1, 1, 1, 1, 1, 1, 1, 6}, 7) == false);
    // TEST_END

    // TEST
    assert(IsSafeCaffLevel({0, 6}, 8) == true);
    // TEST_END

    // TEST
    try {
        IsSafeCaffLevel({}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IsSafeCaffLevel({-1}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IsSafeCaffLevel({101}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IsSafeCaffLevel({1}, -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
