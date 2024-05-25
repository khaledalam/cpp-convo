/***
 * Prompt:




 khaled_cpp_109-2024_May_15: d38877f4-5937-411e-b005-25b18737c22c

func_MajorityElement_khaled_cpp_109-2024_May_15

Make me a C++ function called MajorityElement, it will accept a non-empty list of type std::vector<int> called numbers, each number in the list should be greater than or equal to zero. This function should return number of type int which represents the majority number from the input list. Please note that the majority number is a number that appears in the input list more than n/2 where n is the size of the input list. If there is no majority number then return -1e9. Don't forget to validate the inputs.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

int MajorityElement(std::vector<int> numbers) {
    if (numbers.empty()) {
        throw std::invalid_argument("numbers can't be empty");
    }

    std::unordered_map<int, int> count;

    int majority_threshold = numbers.size() / 2;

    for (const int &num : numbers) {
        if (num < 0) {
            throw std::invalid_argument("number can't be below 0");
        }

        count[num]++;

        if (count[num] > majority_threshold) {
            return num;
        }
    }

    return -1e9;
}

#include <cassert>
int main() {
    // TEST
    assert(MajorityElement({1, 2, 1}) == 1);
    // TEST_END

    // TEST
    assert(MajorityElement({1, 2, 3}) == -1e9);
    // TEST_END

    // TEST
    assert(MajorityElement({1, 0, 0}) == 0);
    // TEST_END

    // TEST
    assert(MajorityElement({1, 0, 0, 1, 4, 5, 4, 5, 4, 4, 4, 4, 4, 4}) == 4);
    // TEST_END

    // TEST
    assert(MajorityElement({1, 1, 2, 2}) == -1e9);
    // TEST_END

    // TEST
    try {
        MajorityElement({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MajorityElement({-1});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
