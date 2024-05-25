/***
 * Prompt:




 khaled_cpp_137-2024_May_19: e3937e2c-d0a3-4a70-b9d9-4aeac9927e51
 

 func_CountGames_khaled_cpp_137-2024_May_19


Create a C++ function called CountGames that takes 4 inputs of type int called price, discount, minimum, and budget. All inputs are greater than zero and discount input value input should be between 0 and 100. There are a lot of games in store and all of them are sold at the same price "price" input. However, next Friday is black Friday and prices will be lower. The first game you buy during black Friday will be sold at "price" input cost, but every subsequent game you buy will be sold at exactly a "discount" input cost less than the cost of the previous one you bought. This will continue until the cost becomes less than or equal to the "minimum" input cost, after which every game you buy will cost the "minimum" input. the function should return another number of type int which represents How many games you can buy during black Friday if you have "budget" input in your wallet.


 */

#include <iostream>
#include <stdexcept>
#include <string>

int CountGames(int price, int discount, int minimum, int budget) {
    if (price <= 0) {
        throw std::invalid_argument("price can't be less than 0");
    }

    if (discount < 0 || discount > 100) {
        throw std::invalid_argument("discount should be between 0 and 100");
    }

    if (minimum <= 0) {
        throw std::invalid_argument("minimum can't be less than 0");
    }

    if (budget <= 0) {
        throw std::invalid_argument("budget can't be less than 0");
    }

    int sum = 0;

    for (int count = 0;; count++) {
        int ccc = (count * discount);

        int the_price = price - ccc;

        if (the_price < minimum) {
            the_price = minimum;
        }

        sum += the_price;

        if (sum > budget) {
            return count;
        }
    }

    return 0;
}

#include <cassert>
int main() {
    // TEST
    assert((CountGames(1, 1, 1, 1) == 1));
    // TEST_END

    // TEST
    assert((CountGames(20, 3, 6, 89) == 8));
    // TEST_END

    // TEST
    assert((CountGames(20, 3, 6, 2) == 0));
    // TEST_END

    // TEST
    assert((CountGames(10, 3, 6, 10) == 1));
    // TEST_END

    // TEST
    assert((CountGames(4, 1, 5, 70) == 14));
    // TEST_END

    // TEST
    try {
        CountGames(0, 1, 1, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CountGames(1, 103, 1, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CountGames(1, 1, 0, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CountGames(1, 5, -2, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CountGames(1, 1, 1, -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CountGames(1, 1, 1, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}