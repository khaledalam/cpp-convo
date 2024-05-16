/***
 * Prompt:




 khaled_cpp_108-2024_May_15: 89c39cbf-6c31-4503-9fa6-5e0ecde950b6


 func_PricePerEgg_khaled_cpp_108-2024_May_15
 
 

Make me a C++ function called PricePerEgg, it will accept 4 inputs, first one called eggs_per_month of type int, the second one of type
double called feed_cost_per_month, the third one called profit_needed of type double, the last one called suggested_sell_price_per_egg of
type double. This function should return a Boolean true if the suggested_sell_price_per_egg is greater than or equal to the exact selling
price per egg after adding the profit_needed otherwise return false. Please note that we should calculate the exact selling price per egg as
follows: Add the multiplication of the feed_cost_per_month and (profit_needed / 100) to the feed_cost_per_month then divide the output by
eggs_per_month to get the exact selling price that can match the needed profit. Please note that eggs_per_month, feed_cost_per_month and
can't be below 0, profit_needed should be between 0 and 100. Don't forget to validate the inputs.




 */

#include <iostream>
#include <stdexcept>
#include <string>

bool PricePerEgg(int eggs_per_month, double feed_cost_per_month, double profit_needed, double suggested_sell_price_per_egg) {
    if (eggs_per_month < 0) {
        throw std::invalid_argument("eggs_per_month can't be negative");
    }

    if (feed_cost_per_month < 0) {
        throw std::invalid_argument("feed_cost_per_month should never be negative");
    }

    if (profit_needed < 0 || profit_needed > 100) {
        throw std::invalid_argument("profit_needed should be between 0 and 100");
    }

    if (suggested_sell_price_per_egg < 0) {
        throw std::invalid_argument("suggested_sell_price_per_egg should never be negative");
    }

    double profit_amount = (profit_needed / 100) * feed_cost_per_month;

    double total_after_profit = profit_amount + feed_cost_per_month;

    double price_per_egg_after_profit = (total_after_profit / eggs_per_month);

    if (suggested_sell_price_per_egg >= price_per_egg_after_profit) {
        return true;
    }

    return false;
}

#include <cassert>
int main() {
    // TEST
    assert(PricePerEgg(5, 10, 10, 2.2) == true);
    // TEST_END

    // TEST
    assert(PricePerEgg(5, 10, 10, 2.5) == true);
    // TEST_END

    // TEST
    assert(PricePerEgg(5, 10, 10, 2.1) == false);
    // TEST_END

    // TEST
    assert(PricePerEgg(5, 10, 0, 2) == true);
    // TEST_END

    // TEST
    try {
        PricePerEgg(-5, 10, 10, 2.2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PricePerEgg(5, -10, 10, 2.2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PricePerEgg(5, 10, -10, 2.2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PricePerEgg(5, 10, 101, 2.2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PricePerEgg(5, 10, 100, -2.2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
