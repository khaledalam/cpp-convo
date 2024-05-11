/***
 * Prompt:




 khaled_cpp_90-2024_May_10: 28eefcf8-1f19-424f-b299-0d3fbd903514

func_AlamTimes_khaled_cpp_90-2024_May_10

 Create me a C++ function called AlamTimes which accepts two inputs, the first input is a non-empty list called times of type std::vector<int> all its values should be greater than zero and should be unique, and the second input is called wakeup of type int which represents when the person will wakeup, its value should be greater than zero too. Please make this function return a number of type int that represent how many alarms in the list which are useful. Please consider that the alarm is useful if it runs before the person wakes up or exactly during the person's wake up. Use lambda function in the solution.



 */

#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

int AlamTimes(std::vector<int> times, int wakeup) {
    if (times.empty()) {
        throw std::invalid_argument("times list can't be empty");
    }

    if (wakeup < 1) {
        throw std::invalid_argument("wakeup can't be less than 1");
    }

    std::set<int> set_con;

    std::sort(times.begin(), times.end(), [](const int &time_a, const int &time_b) { return time_a < time_b; });

    int result = 0;
    for (const int &time : times) {
        if (time < 1) {
            throw std::invalid_argument("time can't be less than 1");
        }
        set_con.insert(time);
        if (time <= wakeup) {
            result++;
        } else {
            break;
        }
    }

    if (set_con.size() != times.size()) {
        throw std::invalid_argument("times list should be unique");
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(AlamTimes({1, 3}, 2) == 1);
    // TEST_END

    // TEST
    assert(AlamTimes({1, 3}, 3) == 2);
    // TEST_END

    // TEST
    assert(AlamTimes({1}, 1) == 1);
    // TEST_END

    // TEST
    assert(AlamTimes({2}, 1) == 0);
    // TEST_END

    // TEST
    try {
        AlamTimes({0}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AlamTimes({-1}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AlamTimes({1}, -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AlamTimes({1}, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AlamTimes({}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AlamTimes({1, 1}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
