/***
 * Prompt:

 khaled_cpp_59_2024_28_04:



 khaled_cpp_58_2024_28_04: 6e14046f-58d5-409f-b2a6-6f053e00ae5b


 func_CacheAnalysis_khaled_cpp_58_2024_28_04

 Design me a C++ function named CacheAnalysis, this function will accept one parameter called visitors of type std::vector<std::pair<int, int>>, each pair of the input represents a visitor, the first argument in the pair is the visitor id and the second argument is the time taken to fully load the page for the visitor. Please note that we are using a caching layer so that each time the same user visits the web page the time of loading the page should be equal to or less than all the times that this visitor takes on his/her past visits. This function should return a boolean true if caching is working correctly otherwise return false. We determine that caching is working correctly based on the previously mentioned condition of page loading time for visitors. Please note that visitor id and loading page time can't be negative.



 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

bool CacheAnalysis(std::vector<std::pair<int, int>> visitors) {
    std::map<int, int> visit_min;

    for (const std::pair<int, int> &visitor : visitors) {
        if (visitor.first < 0 || visitor.second < 0) {
            throw std::invalid_argument("Invalid input");
        }

        if (visit_min.find(visitor.first) != visit_min.end() && visit_min[visitor.first] < visitor.second) {
            return false;
        }

        visit_min[visitor.first] = visitor.second;
    }

    return true;
}

#include <cassert>
int main(int argc, const char *argv[]) {
    // TEST
    assert((CacheAnalysis(std::vector<std::pair<int, int>> { { 1, 100 }, { 2, 100 }, { 5, 101 } }) == true));
    // TEST_END

    // TEST
    assert((CacheAnalysis(std::vector<std::pair<int, int>> { { 1, 100 }, { 2, 100 }, { 1, 99 } }) == true));
    // TEST_END

    // TEST
    assert((CacheAnalysis(std::vector<std::pair<int, int>> { { 1, 100 }, { 2, 100 }, { 1, 101 } }) == false));
    // TEST_END

    // TEST
    assert((CacheAnalysis(std::vector<std::pair<int, int>> { { 1, 100 }, { 2, 100 }, { 1, 99 }, { 1, 111 } }) == false));
    // TEST_END

    // TEST
    try {
        CacheAnalysis(std::vector<std::pair<int, int>> { { -1, 100 } });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CacheAnalysis(std::vector<std::pair<int, int>> { { 1, -100 } });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
