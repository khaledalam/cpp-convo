/***
 * Prompt:




 khaled_cpp_96-2024_May_12: c535913b-ec11-46e0-9091-d4088fab391a

func_FridgeHander_khaled_cpp_96-2024_May_12


 Create me a C++ function called FridgeHander which accepts two inputs, the first input is a non-empty list called products of type
 std::vector<std::string> each string in the list represents some product name in the fridge that can contains any kind of characters
 including spaces and special characters, second input called product_needed of type std::pair<std::string, int>> which first arguemtn
 represent the name pf the product that we needc from the fridge and second argument represent the count that we need of this product name.
 This function should return a Boolean true if our firdge contain the required quantity of the product name of the second input otherwise
 return false. Please don't forget to validate the inputs.




 */

#include <algorithm>

#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

bool FridgeHander(const std::vector<std::string> &products, const std::pair<std::string, int> &product_needed) {
    if (products.empty()) {
        throw std::invalid_argument("products can't be empty");
    }

    if (product_needed.first.empty()) {
        throw std::invalid_argument("product_needed name can't be empty");
    }

    if (product_needed.second < 1) {
        throw std::invalid_argument("product_needed quantity can't be less than 1");
    }

    std::map<std::string, int> freq;

    for (const std::string &product : products) {

        if (product.empty()) {
            throw std::invalid_argument("product name can't be empty");
        }

        freq[product]++;
    }

    return freq[product_needed.first] >= product_needed.second;
}

#include <cassert>
int main() {
    // TEST
    assert(FridgeHander({"bread", "bread", "ice cream"}, {"bread", 2}) == true);
    // TEST_END

    // TEST
    assert(FridgeHander({"br#", "bread", "ice cream"}, {"br#", 1}) == true);
    // TEST_END

    // TEST
    assert(FridgeHander({"br #", "bread", "ice cream"}, {"br  #", 1}) == false);
    // TEST_END

    // TEST
    assert(FridgeHander({"bread", "bread", "ice cream"}, {"ice cream", 1}) == true);
    // TEST_END

    // TEST
    assert(FridgeHander({"bread", "bread", "ice cream"}, {"bread", 3}) == false);
    // TEST_END

    // TEST
    assert(FridgeHander({"bread", "bread", "ice cream"}, {"water", 1}) == false);
    // TEST_END

    // TEST
    try {
        FridgeHander({"bread", "bread", "ice cream"}, {"", 3});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FridgeHander({"bread", "bread", ""}, {"test", 3});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FridgeHander({}, {"test", 3});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FridgeHander({"bread", "bread"}, {"bread", 0});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FridgeHander({"bread", "bread"}, {"bread", -1});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
