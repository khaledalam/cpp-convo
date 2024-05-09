/***
 * Prompt:




 khaled_cpp_25_2024_21_04: 96ab3aa0-cdd0-42cf-940b-04a2afaa12d1


 func_VerifyTransactions_khaled_cpp_25_2024_21_04



 Design me a C++ function named VerifyTransactions that accepts two inputs called translations and bankbook. First input of type std::vector<int> which represents the numerical values of transactions and second input of type std::vector<std::string> which represents the value of transactions with suffix of the currency. Please note that currency is always 3 characters and there is space between number and currency. The function should return a boolean true if both inputs are equal otherwise return false. Please consider that the amount can be negative and don't forget to validate inputs.



 */

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool VerifyTransactions(std::vector<int> translations, std::vector<std::string> bankbook) {
    std::vector<int> bankbook_int;

    for (std::string &transaction : bankbook) {
        if (transaction.length() < 5) {
            throw std::invalid_argument("Invalid transaction length");
        }

        std::stringstream stringstreamer;
        std::string tmp;

        stringstreamer << transaction;
        stringstreamer >> tmp;

        if (std::to_string(stoi(tmp)).length() != tmp.length()) {
            throw std::invalid_argument("Invalid amount");

        }

        bankbook_int.push_back(stoi(tmp));

        stringstreamer >> tmp;

        if (tmp.length() != 3) {
            throw std::invalid_argument("Invalid currency");

        }

    }

    sort(bankbook_int.begin(), bankbook_int.end());
    sort(translations.begin(), translations.end());

    return bankbook_int == translations;
}

#include <cassert>
int main() {
    // TEST
    std::vector<int> input1 = { 100, 250 };
    std::vector<std::string> input2 = { "100 USD", "250 SAR" };
    bool output = true;
    assert(VerifyTransactions(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 100, 250 };
    input2 = { "100 USD", "250 sar" };
    output = true;
    assert(VerifyTransactions(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 100, 250 };
    input2 = { "100 USD", "250 sar" };
    output = true;
    assert(VerifyTransactions(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 100 };
    input2 = { "100 AED" };
    output = true;
    assert(VerifyTransactions(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { };
    input2 = { };
    output = true;
    assert(VerifyTransactions(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { };
    input2 = { "200 SAR" };
    output = false;
    assert(VerifyTransactions(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { -100, 200 };
    input2 = { "-100 USD", "200 SAR" };
    output = true;
    assert(VerifyTransactions(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = { 100, 200 };
    input2 = { "100USD", "250 SAR" };
    try {
        VerifyTransactions(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = { 100, 200 };
    input2 = { "100U D", "250 SAR" };
    try {
        VerifyTransactions(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = { 100, 200 };
    input2 = { "USD", "250 SAR" };
    try {
        VerifyTransactions(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = { 100, 200 };
    input2 = { "100US", "250 SAR" };
    try {
        VerifyTransactions(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
