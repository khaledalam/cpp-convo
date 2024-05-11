/***
 * Prompt:




 khaled_cpp_89-2024_May_10: b60035b7-f3bc-407d-aec6-0cd7881f5da2


 Create me a C++ function called _ which accepts two inputs, the first input is non-empty list called animals_foods_levels of type std::vector<int> all its values should be greater than or equal to zero, and the second input called travel_days which represent how many days the person will travel and leave his animals alone in the home, and travel_days' values should also greater than zero. Please note that each 1 food level can make the animal survive for 1 day, also note that if some animal has more food levels than the required level that can make this animal survive then this animal can support other animals by giving them from his food level. Please make this function return another number of type int, this number should represent the minimum number of food levels needed to make all animals survive during the travel.



 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

int _(const std::vector<int> &animals_foods_levels, int travel_days) {
    if (animals_foods_levels.empty()) {
        throw std::invalid_argument("animals list can't be empty");
    }

    if (travel_days < 1) {
        throw std::invalid_argument("travel_days can't be less than 1");
    }

    int food_needed = 0, support_from_other_animals = 0;
    for (const int &food_level : animals_foods_levels) {
        if (food_level < 0) {
            throw std::invalid_argument("food_level can't be less than 0");
        }

        if (food_level > travel_days) {
            support_from_other_animals += (food_level - travel_days);
        }
    }

    for (int food_level : animals_foods_levels) {
        while (support_from_other_animals > 0 && food_level < travel_days) {
            support_from_other_animals--, food_level++;
        }

        if (food_level < travel_days) {
            food_needed += (travel_days - food_level);
        }
    }

    return food_needed;
}

#include <cassert>
int main() {
    // TEST
    assert(TravelPreparation({1, 1, 3}, 2) == 1);
    // TEST_END

    // TEST
    assert(TravelPreparation({1, 3}, 2) == 0);
    // TEST_END

    // TEST
    assert(TravelPreparation({1, 1}, 1) == 0);
    // TEST_END

    // TEST
    assert(TravelPreparation({3, 3}, 4) == 2);
    // TEST_END

    // TEST
    assert(TravelPreparation({0}, 5) == 5);
    // TEST_END

    // TEST
    try {
        TravelPreparation({-1}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TravelPreparation({1}, -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TravelPreparation({1}, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        TravelPreparation({}, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
