/***
 * Prompt:




 khaled_cpp_98-2024_May_12: c7d06712-e7c7-4053-b4c1-45bf0ddc047a

func_DiffLaptops_khaled_cpp_98-2024_May_12

 Design a C++ function called DiffLaptops which accepts a non-empty input called laptops_prices of type std::vector<int>. Please note that
 laptop price can be zero or positive numbers only and input should contain at least 2 prices. This function should return a number of type
 int that represent the difference between the highest and the lowest laptop prices in the list. Please don't forget to validate the
 inputs.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int DiffLaptops(std::vector<int> laptops_prices) {
    if (laptops_prices.empty()) {
        throw std::invalid_argument("laptops can't be empty");
    }

    if (laptops_prices.size() < 2) {
        throw std::invalid_argument("laptops list can't be less than 2");
    }

    int min_price = 1e9, max_price = 0;

    for (const int &laptop_price : laptops_prices) {
        if (laptop_price < 0) {
            throw std::invalid_argument("laptop price is invalid");
        }

        min_price = std::min(min_price, laptop_price);
        max_price = std::max(max_price, laptop_price);
    }

    return std::abs(min_price - max_price);
}

#include <cassert>
int main() {
    // TEST
    assert((DiffLaptops({{1, 0, 10}}) == 10));
    // TEST_END

    // TEST
    assert((DiffLaptops({{1, 2, 10}}) == 9));
    // TEST_END

    // TEST
    try {
        DiffLaptops({{}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        DiffLaptops({{-1}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
