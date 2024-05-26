/***






 khaled_cpp_157_2024_May_26: 2dc276a8-fb5b-4de3-8618-954f94a31309

 func_BeautifulPath_khaled_cpp_157_2024_May_26




Create a C++ function called BeautifulPath that takes a non-empty array of type std::vector<int> called paintings,
each element should be between 1 and 1000.

There are n pictures delivered for the new exhibition. The i-th painting has beauty ai. We know that a visitor becomes
happy every time he passes from a painting to a more beautiful one.

We are allowed to arrange pictures in any order.

This function should return a number of type int that answer this question:
What is the maximum possible number of times the visitor may become happy while passing all pictures from first to last?
In other words, we are allowed to rearrange elements of a in any order. What is the maximum possible number of indices i
(1 ≤ i ≤ n - 1), such that ai + 1 > ai.

Please don't forget to validate the input.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int BeautifulPath(std::vector<int> paintings) {
    if (paintings.empty()) {
        throw std::invalid_argument("paintings can't be empty");
    }

    for (auto item : paintings) {
        if (item < 1 || item > 1000) {
            throw std::invalid_argument("paintings' items should be between 1 and 1000");
        }
    }

    std::sort(paintings.begin(), paintings.end());

    int lastPaint = paintings[0];
    int result = 0;

    for (size_t idx = 1; idx < paintings.size(); idx++) {
        bool found = paintings[idx] > lastPaint;

        if (!found) {
            for (size_t jdx = idx; jdx < paintings.size() && !found; jdx++) {
                if (paintings[jdx] > lastPaint) {
                    lastPaint = paintings[jdx];
                    found = true;
                    result++;
                }
            }
        }

        if (!found) {
            lastPaint = paintings[idx];
        } else {
            result++;
        }
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(BeautifulPath({20, 30, 10, 50, 40}) == 4);
    // TEST_END

    // TEST
    assert(BeautifulPath({200, 100, 100, 200}) == 2);
    // TEST_END

    // TEST
    try {
        BeautifulPath({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        BeautifulPath({0, 1});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        BeautifulPath({-4, 10});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        BeautifulPath({19, 1001});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}