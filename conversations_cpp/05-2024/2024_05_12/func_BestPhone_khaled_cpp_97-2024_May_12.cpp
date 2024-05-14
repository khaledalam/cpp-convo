/***
 * Prompt:




 khaled_cpp_97-2024_May_12: cd1c4f3d-3c90-4353-97ee-a930d3705be4


func_BestPhone_khaled_cpp_97-2024_May_12


 Design a C++ function called BestPhone which accepts an input called phones of type (std::vector<std::pair<int, int>> each element
 represents a pair of phone weight and price. Please note that phone weight and price can't be less than 1. This function should return
 another pair of type std::pair<int, int> which represent best phone that we can buy. Consider that best phone is the lower in the price and
 if there are 2 phones with same price then the lowest in the weight is the best of them. Please don't forget to validate the inputs and use lambda function in the solution.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::pair<int, int> BestPhone(std::vector<std::pair<int, int>> phones) {
    if (phones.empty()) {
        throw std::invalid_argument("phones can't be empty");
    }

    for (const std::pair<int, int> &phone : phones) {
        if (phone.first < 1 || phone.second < 1) {
            throw std::invalid_argument("phone data is invalid");
        }
    }

    std::sort(phones.begin(), phones.end(), [](const std::pair<int, int> &phone_1, const std::pair<int, int> &phone_2) {
        if (phone_1.second != phone_2.second) {
            return phone_1.second < phone_2.second;
        }

        return phone_1.first < phone_2.first;
    });

    return phones[0];
}

#include <cassert>
int main() {
    // TEST
    assert((BestPhone({{1, 2}, {1, 4}, {1, 1}}) == std::pair<int, int>{1, 1}));
    // TEST_END

    // TEST
    assert((BestPhone({{1, 2}, {3, 1}, {5, 1}}) == std::pair<int, int>{3, 1}));
    // TEST_END

    // TEST
    assert((BestPhone({{1, 2}}) == std::pair<int, int>{1, 2}));
    // TEST_END

    // TEST
    try {
        BestPhone({{0, 2}, {1, 4}, {1, 1}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        BestPhone({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        BestPhone({{-4, 2}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        BestPhone({{4, -2}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        BestPhone({{3, 0}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
