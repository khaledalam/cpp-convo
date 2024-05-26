/***






 khaled_cpp_153_2024_May_26: d625acae-8a78-4a35-8e07-a97e4e445dd2

 func_KitchenStalls_khaled_cpp_153_2024_May_26





Create a C++ function called KitchenStalls that takes two inputs of type const int called num and cnt.

A certain kitchen has num + 2 stalls in a single row; the stalls on the left and right ends are permanently occupied by the kitchen guards. The other number of stalls are for users.

Whenever someone enters the kitchen, they try to choose a stall that is as far from other people as possible. To avoid confusion, they follow deterministic rules: For each empty stall S, they compute two values LS and RS, each of which is the number of empty stalls between S and the closest occupied stall to the left or right, respectively. Then they consider the set of stalls with the farthest closest neighbor, that is, those S for which min(LS, RS) is maximal. If there is only one such stall, they choose it; otherwise, they choose the one among those where max(LS, RS) is maximal. If there are still multiple tied stalls, they choose the leftmost stall among those.

cnt people are about to enter the kitchen; each one will choose their stall before the next arrives. Nobody will ever leave.

This function should return two values of type std::array<int, 2> which represent when the last person chooses their stall S, what will the values of max(LS, RS) and min(LS, RS) be? Please use a tuple in the solution and don't forget to validate the inputs.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <array>
#include <tuple>
#include <vector>

std::array<int, 2> KitchenStalls(const int num, const int cnt) {
    if (num <= 0 || cnt <= 0 || cnt > num) {
        throw std::invalid_argument("inputs are invalid");
    }

    std::vector<std::tuple<bool, int, int>> stalls;
    for (int idx = 0; idx < num; idx++) {
        stalls.push_back(std::make_tuple(true, idx, num - idx - 1));
    }

    int odx;
    for (int pdx = 0; pdx < cnt; pdx++) {
        odx = -1;
        for (int idx = 0; idx < num; idx++) {
            if (std::get<0>(stalls[idx])) {
                const auto o_min = (odx != -1) ? std::min(std::get<1>(stalls[odx]), std::get<2>(stalls[odx])) : -1;
                const auto s_min = std::min(std::get<1>(stalls[idx]), std::get<2>(stalls[idx]));
                if (s_min > o_min || (s_min == o_min && (std::max(std::get<1>(stalls[idx]), std::get<2>(stalls[idx])) >
                                                     std::max(std::get<1>(stalls[odx]), std::get<2>(stalls[odx]))))) {
                    odx = idx;
                }
            }
        }

        std::get<0>(stalls[odx]) = false;
        for (int idx = 0; idx < num; idx++) {
            std::array<int, 2> empties = {0, 0};
            for (int jdx = idx - 1; jdx >= 0 && std::get<0>(stalls[jdx]); jdx--) {
                empties[0]++;
            }
            for (int jdx = idx + 1; jdx < num && std::get<0>(stalls[jdx]); jdx++) {
                empties[1]++;
            }

            std::get<1>(stalls[idx]) = empties[0];
            std::get<2>(stalls[idx]) = empties[1];
        }
    }

    return std::array<int, 2>{std::max(std::get<1>(stalls[odx]), std::get<2>(stalls[odx])),
            std::min(std::get<1>(stalls[odx]), std::get<2>(stalls[odx]))};
}

#include <cassert>
int main() {
    // TEST
    assert((KitchenStalls(4, 2) == std::array<int, 2>{1, 0}));
    // TEST_END

    // TEST
    assert((KitchenStalls(5, 2) == std::array<int, 2>{1, 0}));
    // TEST_END

    // TEST
    assert((KitchenStalls(6, 2) == std::array<int, 2>{1, 1}));
    // TEST_END

    // TEST
    assert((KitchenStalls(1000, 1000) == std::array<int, 2>{0, 0}));
    // TEST_END

    // TEST
    assert((KitchenStalls(1000, 1) == std::array<int, 2>{500, 499}));
    // TEST_END

    // TEST
    try {
        KitchenStalls(0, 7);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        KitchenStalls(6, 0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        KitchenStalls(6, 7);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        KitchenStalls(-6, 7);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}