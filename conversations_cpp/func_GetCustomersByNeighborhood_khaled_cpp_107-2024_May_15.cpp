/***
 * Prompt:




 khaled_cpp_107-2024_May_15: 775641ac-24fa-45e1-8f8e-108bbde4f841

 func_GetCustomersByNeighborhood_khaled_cpp_107-2024_May_15


Write a C++ function called GetCustomersByNeighborhood that accepts two inputs, first one is a non-empty list of type std::vector<Customer>
where Customer is a struct that contains neighborhood_cities member of type std::vector<std::string>, each city in this neighborhood_cities
list should be a non-empty case-sensitive string and can contains any kind of character including spaces and special characters, second input is a
non-empty text of type std::string called city. This function should return a number of type int which represent how many customers in the
customers input list that has the input city in its neighborhood_cities list. Please don't forget to validate the input.

 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Customer {
    std::vector<std::string> neighborhood_cities;
};

int GetCustomersByNeighborhood(std::vector<Customer> customers, std::string city) {
    if (customers.empty()) {
        throw std::invalid_argument("customers list can't be empty");
    }

    int result = 0;

    for (const Customer &customer : customers) {
        if (customer.neighborhood_cities.empty()) {
            throw std::invalid_argument("customer's neighborhood_cities can't be empty");
        }

        for (const std::string city : customer.neighborhood_cities) {
            if (city.empty()) {
                throw std::invalid_argument("customer's city can't be empty");
            }
        }

        if (std::find(customer.neighborhood_cities.begin(), customer.neighborhood_cities.end(), city) !=
            customer.neighborhood_cities.end()) {
            result++;
        }
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(GetCustomersByNeighborhood(
               {Customer{.neighborhood_cities = {"cairo", "alexandria"}}, Customer{.neighborhood_cities = {"cairo"}}}, "cairo") == 2);
    // TEST_END

    // TEST
    assert(GetCustomersByNeighborhood({Customer{.neighborhood_cities = {"#12%&", "test"}}, Customer{.neighborhood_cities = {"2@"}}},
                                      "#12%&") == 1);
    // TEST_END

    // TEST
    assert(GetCustomersByNeighborhood({Customer{.neighborhood_cities = {"test"}}, Customer{.neighborhood_cities = {"123"}}}, "Test") == 0);
    // TEST_END

    // TEST
    assert(GetCustomersByNeighborhood({Customer{.neighborhood_cities = {"  "}}, Customer{.neighborhood_cities = {" "}}}, " ") == 1);
    // TEST_END

    // TEST
    try {
        GetCustomersByNeighborhood({}, "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        GetCustomersByNeighborhood({Customer{.neighborhood_cities = {}}}, "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        GetCustomersByNeighborhood({Customer{.neighborhood_cities = {""}}}, "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
