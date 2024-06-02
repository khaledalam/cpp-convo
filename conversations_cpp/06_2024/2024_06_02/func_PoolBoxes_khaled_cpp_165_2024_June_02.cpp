/***






 khaled_cpp_165_2024_June_02: 8bb5257a-2cd3-4663-bd83-6d6b94665c04


func_PoolBoxes_khaled_cpp_165_2024_June_02



Write me a C++ function called PoolBoxes that takes two inputs of type int called number and count.

A certain pool has number + 2 boxes in a single row; the boxes on the left and right ends are permanently occupied by the
pool guards. The other number of boxes are for users.

Whenever someone enters the pool, they try to choose a box that is as far from other people as possible. To avoid
confusion, they follow deterministic rules: For each empty box S, they compute two values LS and RS, each of which is
the number of empty boxes between S and the closest occupied box to the left or right, respectively. Then they
consider the set of boxes with the farthest closest neighbor, that is, those S for which min(LS, RS) is maximal. If
there is only one such box, they choose it; otherwise, they choose the one among those where max(LS, RS) is maximal.
If there are still multiple tied boxes, they choose the leftmost box among those.

count people are about to enter the pool; each one will choose their box before the next arrives. Nobody will ever
leave.

This function should return two values of type std::array<int, 2> which represent when the last person chooses their
box S, what will the values of max(LS, RS) and min(LS, RS) be? Please don't forget to validate the inputs.





*/

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

std::array<int, 2> PoolBoxes(int number, int count) {
    if (number <= 0 || count <= 0 || count > number) {
        throw std::invalid_argument("invalid number and/or count");
    }

    std::vector<std::tuple<bool, int, int>> boxes;
    for (int idx = 0; idx < number; idx++) {
        boxes.push_back(std::make_tuple(true, idx, number - idx - 1));
    }

    int odx;
    for (int pdx = 0; pdx < count; pdx++) {
        odx = -1;
        for (int idx = 0; idx < number; idx++) {
            if (std::get<0>(boxes[idx])) {
                const auto o_min = (odx != -1) ? std::min(std::get<1>(boxes[odx]), std::get<2>(boxes[odx])) : -1;
                const auto s_min = std::min(std::get<1>(boxes[idx]), std::get<2>(boxes[idx]));
                
                if (s_min > o_min || (s_min == o_min && (std::max(std::get<1>(boxes[idx]), std::get<2>(boxes[idx])) >
                                                         std::max(std::get<1>(boxes[odx]), std::get<2>(boxes[odx]))))) {
                    odx = idx;
                }
            }
        }

        std::get<0>(boxes[odx]) = false;
        for (int idx = 0; idx < number; idx++) {
            std::array<int, 2> empties = {0, 0};
            for (int jdx = idx - 1; jdx >= 0 && std::get<0>(boxes[jdx]); jdx--) {
                empties[0]++;
            }
            for (int jdx = idx + 1; jdx < number && std::get<0>(boxes[jdx]); jdx++) {
                empties[1]++;
            }

            std::get<1>(boxes[idx]) = empties[0];
            std::get<2>(boxes[idx]) = empties[1];
        }
    }

    return std::array<int, 2>{std::max(std::get<1>(boxes[odx]), std::get<2>(boxes[odx])),
                              std::min(std::get<1>(boxes[odx]), std::get<2>(boxes[odx]))};
}

#include <cassert>
int main() {
    // TEST
    assert((PoolBoxes(4, 2) == std::array<int, 2>{1, 0}));
    // TEST_END

    // TEST
    assert((PoolBoxes(5, 2) == std::array<int, 2>{1, 0}));
    // TEST_END

    // TEST
    assert((PoolBoxes(6, 2) == std::array<int, 2>{1, 1}));
    // TEST_END

    // TEST
    assert((PoolBoxes(1000, 1000) == std::array<int, 2>{0, 0}));
    // TEST_END

    // TEST
    assert((PoolBoxes(1000, 1) == std::array<int, 2>{500, 499}));
    // TEST_END

    // TEST
    try {
        PoolBoxes(0, 7);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PoolBoxes(6, 0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PoolBoxes(6, 7);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PoolBoxes(-6, 7);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}