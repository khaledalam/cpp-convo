/***






 khaled_cpp_183_2024_June_02: ab438f17-1298-4b3d-97f0-4de4bfa208eb


func_MinimizeTravelTime_khaled_cpp_183_2024_June_02

Create a C++ function called MinimizeTravelTime that takes two non-empty arrays of type std::vector<long long>, the length of
both of them should be the same and should be greater than 2.

There are n cities, and the i-th city has a distance given by distances-i. We want to travel through exactly three
cities such that their indices i < j < k and the distance increases at each step (i.e., distances-i < distances-j <
distances-k).

The travel time from one city to another is given by times-i.

This function should return a number of type int that represents the minimum travel time. Please don't forget to
validate the input.


*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const long long inf = 1e18;

int MinimizeTravelTime(std::vector<long long> distances, std::vector<long long> times) {
    if (distances.size() < 3 || times.size() < 3) {
        throw std::invalid_argument("distances and times sizes should be at least 3");
    }

    if (distances.size() != times.size()) {
        throw std::invalid_argument("distances and times sizes should be the same");
    }

    int n_size = distances.size();
    std::vector<long long> dynamic(n_size, inf);
    long long min_time = inf;

    for (int idx = 0; idx < n_size; ++idx) {
        for (int jdx = idx + 1; jdx < n_size; ++jdx) {
            if (distances[idx] < distances[jdx]) {
                dynamic[jdx] = std::min(dynamic[jdx], times[idx] + times[jdx]);
                min_time = std::min(min_time, dynamic[idx] + times[jdx]);
            }
        }
    }

    return min_time == inf ? -1 : min_time;
}

#include <cassert>
int main() {
    // TEST
    assert(MinimizeTravelTime({100, 200, 300, 400, 500}, {10, 20, 30, 40, 50}) == 60);
    // TEST_END

    // TEST
    assert(MinimizeTravelTime({500, 400, 300, 200, 100}, {10, 20, 30, 40, 50}) == -1);
    // TEST_END

    // TEST
    assert(MinimizeTravelTime({100, 200, 300, 400, 500, 600}, {10, 20, 30, 40, 50, 60}) == 60);
    // TEST_END

    // TEST
    try {
        MinimizeTravelTime({100, 200}, {10, 20});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinimizeTravelTime({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
