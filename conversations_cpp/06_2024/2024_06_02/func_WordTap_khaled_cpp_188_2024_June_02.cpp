/***






 khaled_cpp_188_2024_June_02: 40c484d8-f0fc-49d7-b8e5-ed29fcedf56f

func_WordTap_khaled_cpp_188_2024_June_02

Design a C++ function called WordTap that takes three inputs: a string begin_word, a string end_word, and a non-empty
vector of strings called word_list of type const std::vector<std::string>. All input string should not be empty. This
function should return an integer representing the length of the shortest transformation sequence from begin_word to
end_word, where each transformed word must exist in word_list. Use BFS to find the shortest path. Please don't forget to
validate the input.


*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

int WordTap(const std::string &begin_word, const std::string &end_word, const std::vector<std::string> &word_list) {
    if (begin_word.empty()) {
        throw std::invalid_argument("begin_word can't be empty");
    }

    if (end_word.empty()) {
        throw std::invalid_argument("end_word can't be empty");
    }

    if (word_list.empty()) {
        throw std::invalid_argument("word_list can't be empty");
    }

    for (const std::string &word : word_list) {
        if (word.empty()) {
            throw std::invalid_argument("word can't be empty");
        }
    }

    std::unordered_set<std::string> word_set(word_list.begin(), word_list.end());
    if (word_set.find(end_word) == word_set.end()) {
        return 0;
    }

    std::queue<std::pair<std::string, int>> qqq;
    qqq.push({begin_word, 1});

    while (!qqq.empty()) {
        auto [current_word, level] = qqq.front();
        qqq.pop();

        if (current_word == end_word) {
            return level;
        }

        for (int iii = 0; iii < current_word.size(); ++iii) {
            std::string temp = current_word;
            for (char ccc = 'a'; ccc <= 'z'; ++ccc) {
                temp[iii] = ccc;
                if (word_set.find(temp) != word_set.end()) {
                    qqq.push({temp, level + 1});
                    word_set.erase(temp);
                }
            }
        }
    }

    return 0;
}

#include <cassert>
int main() {
    // TEST
    assert(WordTap("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}) == 5);
    // TEST_END

    // TEST
    assert(WordTap("hit", "cog", {"hot", "dot", "dog", "lot", "log"}) == 0);
    // TEST_END

    // TEST
    assert(WordTap("a", "c", {"a", "b", "c"}) == 2);
    // TEST_END

    // TEST
    try {
        WordTap("", "cog", {"hot", "dot", "dog", "lot", "log", "cog"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        WordTap("test", "cog", {});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        WordTap("test", "", {"test"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
