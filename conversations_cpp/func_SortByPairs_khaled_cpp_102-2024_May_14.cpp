/***
 * Prompt:




 khaled_cpp_102-2024_May_14: 351a847e-3d71-4169-9d29-39dd6c7c637b

 func_SortByPairs_khaled_cpp_102-2024_May_14




Design a C++ function called SortByPairs which accepts an input called pairs of type std::vector<int>. This function should return another list of type std::vector<int> which has items in a specific order first highest item then first lowest item next to it, then second highest item then second lowest item next to it and so on, e.g. if list is 1,2,3,4 the the sorted list should be 4,1,3,2. Please note that items can be negative, zero or positive. Don't forget to validate input.



 */

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> SortByPairs(std::vector<int> pairs) {
    if (pairs.empty()) {
        throw std::invalid_argument("pairs can't be empty");
    }

    std::list<int> the_list;

    for (const int &pair : pairs) {
        the_list.push_back(pair);
    }

    the_list.sort([](const int &first, const int &second) { return first > second; });

    std::vector<int> sorted;

    while (the_list.size()) {
        sorted.push_back(the_list.front());
        the_list.pop_front();

        sorted.push_back(the_list.back());
        the_list.pop_back();
    }

    return sorted;
}

#include <cassert>
int main() {
    // TEST
    assert((SortByPairs({1, 0, 55, -4}) == std::vector<int>{55, -4, 1, 0}));
    // TEST_END

    // TEST
    assert((SortByPairs({1, 0}) == std::vector<int>{1, 0}));
    // TEST_END

    // TEST
    assert((SortByPairs({1, -3, 5}) == std::vector<int>{5, -3, 1}));
    // TEST_END

    // TEST
    try {
        SortByPairs({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
