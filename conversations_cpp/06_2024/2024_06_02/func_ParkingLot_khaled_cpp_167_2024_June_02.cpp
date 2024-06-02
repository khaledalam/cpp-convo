/***






 khaled_cpp_167_2024_June_02: 9750ead3-cb4d-4377-b91f-b62faf6dcaaa

 func_ParkingLot_khaled_cpp_167_2024_June_02



Write me a C++ function called ParkingLot that takes two inputs of type int called spots and cars.

A certain parking lot has spots parking spots in a single row. Initially, all spots are empty. Each car entering the lot
tries to park as far from other cars as possible. If multiple spots have the same distance, they choose the leftmost
spot among those.

cars cars are about to enter the parking lot; each one will choose their spot following the aforementioned rules.

This function should return a vector of integers, where each integer represents the spot number (1-indexed) chosen by
each car, in the order they enter. Please don't forget to validate the inputs.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> ParkingLot(int spots, int cars) {
    if (spots <= 0 || cars <= 0 || cars > spots) {
        throw std::invalid_argument("Invalid number of spots and/or cars");
    }

    std::vector<bool> parking_spots(spots, true);
    std::vector<int> chosen_spots;

    for (int car = 0; car < cars; ++car) {
        int best_spot = -1, max_dist = -1;

        for (int sss = 0; sss < spots; ++sss) {
            if (parking_spots[sss]) {
                int left_dist = 0, right_dist = 0;

                for (int lss = sss - 1; lss >= 0 && parking_spots[lss]; --lss)
                    left_dist++;
                for (int rss = sss + 1; rss < spots && parking_spots[rss]; ++rss)
                    right_dist++;

                int min_dist = std::min(left_dist, right_dist);

                if (min_dist > max_dist) {
                    max_dist = min_dist;
                    best_spot = sss;
                }
            }
        }

        if (best_spot == -1) {
            throw std::runtime_error("No available spot found");
        }

        parking_spots[best_spot] = false;
        chosen_spots.push_back(best_spot + 1);
    }

    return chosen_spots;
}

#include <cassert>
int main() {
    // TEST
    assert((ParkingLot(10, 5) == std::vector<int>{5, 8, 2, 1, 3}));
    // TEST_END

    // TEST
    assert((ParkingLot(20, 5) == std::vector<int>{10, 5, 15, 18, 2}));
    // TEST_END

    // TEST
    assert((ParkingLot(9, 3) == std::vector<int>{5, 2, 7}));
    // TEST_END

    // TEST
    try {
        ParkingLot(-1, 5);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ParkingLot(10, -5);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ParkingLot(10, 0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ParkingLot(10, 11);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ParkingLot(1, 5);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
