/***
 * Prompt:




 khaled_cpp_83-2024_May_08: 4dec156c-6caf-43b7-b1f8-716633f74850


 func_SortByFractionValue_khaled_cpp_83-2024_May_08


 Design me a C++ method called SortByFractionValue, this method will take an input called fractions of type std::vector<FractionNumber> which represents a list of fraction numbers where FractionNumber is a struct that containers 2 members, The first one is called numerator of type double, the second one called denominator of type double both of members can be any negative zero or positive except for denominator can't be zero. The method should sort the list of fractions in descending order based on their decimal values. Please note that zero as a denominator is not allowed, don't forget to validate this note and please use lambda function in the solution.


 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

struct FractionNumber {
    double numerator;
    double denominator;

    bool operator==(const FractionNumber &another) const {
        return (numerator == another.numerator && denominator == another.denominator);
    }

    bool operator>(const FractionNumber &another) const {
        return (numerator / denominator) > (another.numerator / another.denominator);
    }
};

std::vector<FractionNumber> SortByFractionValue(std::vector<FractionNumber> fractions) {

    for (const FractionNumber &fraction : fractions) {
        if (fraction.denominator == 0) {
            throw std::invalid_argument("zero as denominator is not allowed");
        }
    }
    std::sort(fractions.begin(), fractions.end(), [](const FractionNumber &first_number, const FractionNumber &second_number) {
        return first_number > second_number;
    });

    return fractions;
}

#include <cassert>
int main() {
    // TEST
    std::vector<FractionNumber> input { { 1, 2 }, { 3, 4 }, { 2, 5 }, { 1, 3 } };
    std::vector<FractionNumber> output { { 3, 4 }, { 1, 2 }, { 2, 5 }, { 1, 3 } };
    assert(SortByFractionValue(input) == output);
    // TEST_END

    // TEST
    input = { { 1, 2 }, { 3, 4 } };
    output = { { 3, 4 }, { 1, 2 } };
    assert(SortByFractionValue(input) == output);
    // TEST_END

    // TEST
    input = { { 1, 2 } };
    output = { { 1, 2 } };
    assert(SortByFractionValue(input) == output);
    // TEST_END

    // TEST
    input = { { -1, 2 }, { -4, 4 } };
    output = { { -1, 2 }, { -4, 4 } };
    assert(SortByFractionValue(input) == output);
    // TEST_END

    // TEST
    input = { { 5, 8 }, { 2, 3 }, { 7, 9 }, { 3, 10 } };
    output = { { 7, 9 }, { 2, 3 }, { 5, 8 }, { 3, 10 } };
    assert(SortByFractionValue(input) == output);
    // TEST_END

    // TEST
    input = { { 4, 9 }, { 6, 11 }, { 2, 5 } };
    output = { { 6, 11 }, { 4, 9 }, { 2, 5 } };
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

