/***
 * Prompt:




 khaled_cpp_82-2024_May_08: 78f64f60-8ff9-4371-b117-076f88563943


 Design me a C++ method called SortByFractionValue, this method will takes an input called fractions of type std::vector<FractionNumber> which representing list of fraction numbers where FractionNumber is a struct that containers 2 members, first one called numerator of type int, second one called  denominator of type int. The method should sort the list of fractions in a descending order based on their decimal values. Please note that it's not allow to divide by zero, don't forget to validate this note.


 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

struct FractionNumber {
    int numerator;
    int denominator;
};

double decimalValue(const FractionNumber &fraction) {
    return static_cast<double>(fraction.numerator) / static_cast<double>(fraction.denominator);
}

bool compareByFractionValue(const FractionNumber &a, const FractionNumber &b) {
    return decimalValue(a) < decimalValue(b);
}

std::vector<FractionNumber> SortByFractionValue(std::vector<FractionNumber> fractions) {

    for (const FractionNumber &fraction : fractions) {
        if (fraction.denominator == 0) {
            throw std::invalid_argument("not allow to divide by zero");
        }
    }
    std::sort(fractions.begin(), fractions.end(), compareByFractionValue);
    return fractions;
}

#include <cassert>

int main() {
    // TEST
    std::vector<FractionNumber> input { { 1, 2 }, { 3, 4 }, { 2, 5 }, { 1, 3 } };
    std::vector<FractionNumber> output { { 3, 4 }, { 2, 5 }, { 1, 2 }, { 1, 3 } };
    assert((SortByFractionValue(input) == output));
    // TEST_END

    // TEST
    input = { { 5, 8 }, { 2, 3 }, { 7, 9 }, { 3, 10 } };
    output = { { 7, 9 }, { 5, 8 }, { 2, 3 }, { 3, 10 } };
    assert(SortByFractionValue(input) == output);
    // TEST_END

    // TEST
    input = { { 1, 7 }, { 4, 9 }, { 6, 11 }, { 2, 5 } };
    output = { { 6, 11 }, { 4, 9 }, { 2, 5 }, { 1, 7 } };
    assert(SortByFractionValue(input) == output);
    // TEST_END

    // TEST
    try {
        input = { { 1, 0 }, { 1, 7 } };
        SortByFractionValue(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

}

