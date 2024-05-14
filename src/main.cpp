/***
 * Prompt:




 khaled_cpp_102-2024_May_14:




Design a C++ function called SortByPairs which accepts two inputs, The first input is a non-empty list of intervals called slots of type
std::vector<std::pair<int, int>>, each pair represents an interval where the first argument should be less than or equal to the second
argument, second input called suggestion of type int. This function should return a number of type int which represents how many intervals
suit the suggestion. Please note that interval is suitable if the suggestion intersects it(between or equal first and second arguments of
the interval). please also don't forget to validate the inputs.



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
    try {
        SortByPairs({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
