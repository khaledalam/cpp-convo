/***






 khaled_cpp_184_2024_June_02: ec25a98a-593b-403b-9d99-768406a18ee1
 

 func_MaximizeWorkshops_khaled_cpp_184_2024_June_02


Create me a C++ function called MaximizeWorkshops that takes two non-empty arrays of type std::vector<int>, the length
of both of them should be the same and should be greater than 2.

There are n workshops, and the i-th workshop has a starting time given by start_times-i and an ending time given by
end_times-i. We want to attend exactly three workshops such that their indices i < j < k and the workshops do not
overlap (i.e., end_times-i < start_times-j < end_times-j < start_times-k < end_times-k).

This function should return a number of type int that represents the maximum number of workshops attended. Please don't
forget to validate the input.


*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int MaximizeWorkshops(std::vector<int> start_times, std::vector<int> end_times) {
    if (start_times.size() < 3 || end_times.size() < 3) {
        throw std::invalid_argument("start_times and end_times sizes should be at least 3");
    }

    if (start_times.size() != end_times.size()) {
        throw std::invalid_argument("start_times and end_times sizes should be the same");
    }

    int n_size = start_times.size();
    std::vector<int> dynamic(n_size, 1);

    for (int idx = 0; idx < n_size; ++idx) {
        for (int jdx = 0; jdx < idx; ++jdx) {
            if (end_times[jdx] < start_times[idx]) {
                dynamic[idx] = std::max(dynamic[idx], dynamic[jdx] + 1);
            }
        }
    }

    return *std::max_element(dynamic.begin(), dynamic.end());
}

#include <cassert>
int main() {
    // TEST
    assert(MaximizeWorkshops({1, 3, 6, 2, 8}, {2, 5, 7, 4, 9}) == 4);
    // TEST_END

    // TEST
    assert(MaximizeWorkshops({1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}) == 3);
    // TEST_END

    // TEST
    assert(MaximizeWorkshops({1, 3, 6, 2, 8, 5}, {2, 5, 7, 4, 9, 6}) == 4);
    // TEST_END

    // TEST
    try {
        MaximizeWorkshops({1, 2}, {2, 3});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeWorkshops({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
