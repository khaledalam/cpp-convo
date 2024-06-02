/***






 khaled_cpp_186_2024_June_02: edb7e413-8783-4604-ae5f-314891e74341

 func_MaximizeDistanceWithStops_khaled_cpp_186_2024_June_02


Create a C++ function called MaximizeDistanceWithStops that takes three parameters: an array of type std::vector<int>
called distances representing the distance of each city from the start, another array of type std::vector<int> called
costs representing the travel cost to each city, and an integer stops that represents the number of cities to visit of type int. The
length of both arrays should be the same and should be greater than the value of stops.

We want to visit exactly stops cities such that the distances increase at each step.

This function should return a number of type int that represents the maximum distance traveled with the minimum cost.
Please don't forget to validate the input.


*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const long long inf = 1e18;

int MaximizeDistanceWithStops(const std::vector<int> &distances, const std::vector<int> &costs, int stops) {
    if (distances.size() < stops || costs.size() < stops) {
        throw std::invalid_argument("distances and costs sizes should be greater than the number of stops");
    }

    if (distances.size() != costs.size()) {
        throw std::invalid_argument("distances and costs sizes should be the same");
    }

    int n_size = distances.size();
    std::vector<long long> dynamic(n_size, inf);
    long long min_cost = inf;
    long long max_distance = -inf;

    for (int idx = 0; idx < n_size; ++idx) {
        for (int jdx = idx + 1; jdx < n_size; ++jdx) {
            for (int kdx = jdx + 1; kdx < n_size; ++kdx) {
                if (distances[idx] < distances[jdx] && distances[jdx] < distances[kdx]) {
                    long long cost = costs[idx] + costs[jdx] + costs[kdx];
                    if (cost < min_cost) {
                        min_cost = cost;
                        max_distance = std::max(max_distance, static_cast<long long>(distances[kdx]));
                    }
                }
            }
        }
    }

    return max_distance == -inf ? -1 : max_distance;
}

#include <cassert>
int main() {
    // TEST
    assert(MaximizeDistanceWithStops({1, 3, 5, 7, 9}, {10, 20, 30, 40, 50}, 3) == 5);
    // TEST_END

    // TEST
    assert(MaximizeDistanceWithStops({5, 4, 3, 2, 1}, {10, 20, 30, 40, 50}, 3) == -1);
    // TEST_END

    // TEST
    assert(MaximizeDistanceWithStops({1, 2, 3, 4, 5, 6, 7}, {10, 20, 30, 40, 50, 60, 70}, 3) == 3);
    // TEST_END

    // TEST
    try {
        MaximizeDistanceWithStops({1, 2}, {1, 2}, 3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeDistanceWithStops({}, {}, 3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
