/***


 khaled_cpp_mil_217_2024_June_16: a2d1a4b4-06ea-4874-934a-51d3dc9ec283

 func_MaxReward_khaled_cpp_mil_217_2024_June_16

*/

/*


Create a C++ function called MaxReward that takes two non-empty arrays of type std::vector<int>, the length of both
of them should be the same and should be greater than 2.

There are n tasks, and the i-th task has a difficulty level given by difficulties-i. We want to complete exactly three
tasks such that their indices i < j < k and the difficulty increases at each step (i.e., difficulties-i < difficulties-j
< difficulties-k).

The reward for completing the i-th task is given by rewards-i.

This function should return a number of type int that represents the maximum total reward, if there is no result return
-1. Please don't forget to validate the input.



*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const long long neg_inf = -1 * INT_MAX;

int MaxReward(std::vector<int> difficulties, std::vector<int> rewards) {
    if (difficulties.size() < 3 || rewards.size() < 3) {
        throw std::invalid_argument("difficulties and rewards sizes should be at least 3");
    }

    if (difficulties.size() != rewards.size()) {
        throw std::invalid_argument("difficulties and rewards sizes should be the same");
    }

    int n_size = difficulties.size();
    std::vector<long long> dynamic(n_size, neg_inf);
    long long max_reward = neg_inf;

    for (int idx = 0; idx < n_size; ++idx) {
        for (int jdx = idx + 1; jdx < n_size; ++jdx) {
            if (difficulties[idx] < difficulties[jdx]) {
                dynamic[jdx] = std::max(dynamic[jdx], static_cast<long long>(rewards[idx] + rewards[jdx]));
                max_reward = std::max(max_reward, dynamic[idx] + rewards[jdx]);
            }
        }
    }

    return max_reward == neg_inf ? -1 : max_reward;
}

#include <cassert>
int main() {
    // TEST
    assert(MaxReward({1, 3, 5, 7, 9}, {10, 20, 30, 40, 50}) == 120);
    // TEST_END

    // TEST
    assert(MaxReward({5, 4, 3, 2, 1}, {10, 20, 30, 40, 50}) == -1);
    // TEST_END

    // TEST
    assert(MaxReward({1, 2, 3, 4, 5, 6, 7}, {10, 20, 30, 40, 50, 60, 70}) == 180);
    // TEST_END

    // TEST
    try {
        MaxReward({1, 2}, {1, 2});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxReward({}, {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
