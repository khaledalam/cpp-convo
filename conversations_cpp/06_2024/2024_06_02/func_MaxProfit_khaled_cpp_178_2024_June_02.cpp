/***






 khaled_cpp_178_2024_June_02: 63ccccdd-ac0f-48fb-a004-cd3f7ab916cd

 func_MaxProfit_khaled_cpp_178_2024_June_02


Create a C++ function called MaxProfit that takes 2 non-empty arrays of type std::vector<int>, the length of both of
them should be the same and should be greater than 2.

There are n days, and the i-th day has a certain price of a stock given by prices-i. We want to determine the maximum
profit that can be achieved by buying and then selling the stock exactly twice. Namely, you must buy first, sell, then
buy again and sell. The second buy must happen after the first sell.

The function should return a number of type int that represents the maximum profit. Please don't forget to validate the
input.


*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int MaxProfit(std::vector<int> prices) {
    if (prices.size() < 3) {
        throw std::invalid_argument("prices size should be at least 3");
    }

    int nnn = prices.size();
    std::vector<int> max_profit_first_transaction(nnn, 0);
    std::vector<int> max_profit_second_transaction(nnn, 0);

    int min_price = prices[0];
    for (int iii = 1; iii < nnn; ++iii) {
        min_price = std::min(min_price, prices[iii]);
        max_profit_first_transaction[iii] = std::max(max_profit_first_transaction[iii - 1], prices[iii] - min_price);
    }

    int max_price = prices[nnn - 1];
    for (int iii = nnn - 2; iii >= 0; --iii) {
        max_price = std::max(max_price, prices[iii]);
        max_profit_second_transaction[iii] = std::max(max_profit_second_transaction[iii + 1], max_price - prices[iii]);
    }

    int max_profit = 0;
    for (int iii = 0; iii < nnn; ++iii) {
        max_profit = std::max(max_profit, max_profit_first_transaction[iii] + max_profit_second_transaction[iii]);
    }

    return max_profit;
}

#include <cassert>
int main() {
    // TEST
    assert(MaxProfit({3, 3, 5, 0, 0, 3, 1, 4}) == 6);
    // TEST_END

    // TEST
    assert(MaxProfit({1, 2, 3, 4, 5}) == 4);
    // TEST_END

    // TEST
    assert(MaxProfit({7, 6, 4, 3, 1}) == 0);
    // TEST_END

    // TEST
    try {
        MaxProfit({1, 2});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxProfit({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
