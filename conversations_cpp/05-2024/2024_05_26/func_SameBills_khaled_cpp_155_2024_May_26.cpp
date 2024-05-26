/***






 khaled_cpp_155_2024_May_26: fb478523-f47e-4bfb-b403-01d6814e7e33

 func_SameBills_khaled_cpp_155_2024_May_26





Create a C++ function called SameBills that takes 2 inputs of type const int called balance_person_1 and
balance_person_2 which both should be greater than 0.

This function should return a Boolean true if both persons can withdraw their money using the same minimum number of
bills otherwise return false.

Note that the denominations for money bills are 1, 5, 10, 20, 100. Please don't forget to
validate the input.





*/

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>

int WithdrawMoney(const int balance) {
    const std::array<int, 5> bills = {100, 20, 10, 5, 1};

    int need = 0;
    int value = 0;
    while (value < balance) {
        for (size_t idx = 0; idx < bills.size(); idx++) {

            int tmp = (value + bills[idx]);

            if (tmp <= balance) {
                value += bills[idx];
                need++;
                break;
            }
        }
    }

    return need;
}

bool SameBills(const int balance_person_1, const int balance_person_2) {
    if (balance_person_1 < 1) {
        throw std::invalid_argument("balance_person_1 can't be less than 1");
    }

    if (balance_person_2 < 1) {
        throw std::invalid_argument("balance_person_2 can't be less than 1");
    }

    return WithdrawMoney(balance_person_1) == WithdrawMoney(balance_person_2);
}

#include <cassert>
int main() {
    // TEST
    assert(SameBills(5, 10) == true);
    // TEST_END

    // TEST
    assert(SameBills(20, 10) == true);
    // TEST_END

    // TEST
    assert(SameBills(25, 10) == false);
    // TEST_END

    // TEST
    assert(SameBills(2, 40) == true);
    // TEST_END

    // TEST
    assert(SameBills(8, 6) == false);
    // TEST_END

    // TEST
    assert(SameBills(25, 30) == true);
    // TEST_END

    // TEST
    try {
        SameBills(0, 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SameBills(1, 0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SameBills(-4, 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SameBills(6, -1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}