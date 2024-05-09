/***
 * Prompt:




 khaled_cpp_38_2024_24_04: 010bb3a5-13f2-4fdb-9613-1eccd5c77a18

 4 keys to left
 alarm turn off of the day


 Write a C++ class called Charging. This class contains a method named BudgetNeeded, it accepts 3 inputs. First input called drinks of type std::vector<int> which represent the calories of the current drinks that user has in his fridge. Second input called needs of type integer which represent the required calories that user need to get. Third input called drink_prices of type std::vector<std::pair<int, int>> which represent the drinks in the market, each pair represent the calories and the price. The method should return number of type integer which refers to the minimum required money that needed to buy the highest calories drinks to cover the user needs of calories. Please note that if we can't cover the required calories using the drink_prices list that means the inputs are invalid. Don't forget to validate that.


 */

#include <stdexcept>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

class Charging {
public:
    int BudgetNeeded(std::vector<int> drinks, int needs, std::vector<std::pair<int, int>> drink_prices) {

        int result = 0;

        int sum = std::accumulate(drinks.begin(), drinks.end(), 0);

        if (sum >= needs) {
            return result;
        }

        sort(drink_prices.begin(), drink_prices.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
            if (a.second != b.second) {
                return a.second < b.second;
            }

            return a.first > b.first;
        });

        for (const std::pair<int, int> &item : drink_prices) {
            result += item.second;
            sum += item.first;

            if (sum >= needs) {
                break;
            }
        }

        if (sum < needs) {
            throw std::invalid_argument("needs can't be covered");
        }

        return result;
    }
};

#include <cassert>
int main(int argc, const char *argv[]) {
    Charging charging;

    // TEST
    assert(charging.BudgetNeeded( { 1, 3 }, 5, { std::make_pair(1, 4), std::make_pair(1, 3) }) == 3);
    // TEST_END

    // TEST
    assert(charging.BudgetNeeded( { 1 }, 0, { std::make_pair(1, 4) }) == 0);
    // TEST_END

    // TEST
    assert(charging.BudgetNeeded( { 1 }, 2, { std::make_pair(5, 4), std::make_pair(5, 5), std::make_pair(1, 6) }) == 4);
    // TEST_END

    // TEST
    assert(charging.BudgetNeeded( { }, 1, { std::make_pair(5, 1), std::make_pair(5, 5) }) == 1);
    // TEST_END

    // TEST
    assert(charging.BudgetNeeded( { }, 0, { }) == 0);
    // TEST_END

    // TEST
    try {
        charging.BudgetNeeded( { 1 }, 20, { std::make_pair(5, 4), std::make_pair(5, 5), std::make_pair(1, 6) });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        assert(charging.BudgetNeeded( { 1 }, 2, { }) == 4);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

