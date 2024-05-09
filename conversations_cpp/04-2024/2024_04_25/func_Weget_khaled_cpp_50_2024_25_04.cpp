/***
 * Prompt:




 khaled_cpp_50_2024_25_04: d20d5993-f8f7-42a3-bd5f-010668696dfd

 func_Weget_khaled_cpp_50_2024_25_04

 Write a C++ function called Weget, it will accept one input called commands of type std::vector<Command> where Command is a struct type that contains url member of type std::string, params member of type std::string and percentage_to_perform member of type int. This function should return integer number that represent how many url downloads will complete. Note that when pass "-c" in Command params it allow to resume the download on the next time when you try to perform another command of same url again otherwise it start the download from 0%. Also note that percentage_to_perform can't be negative, don't forget to validate that.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

struct Command {
    std::string url, params;
    int percentage_to_perform;
};

int Weget(const std::vector<Command> &commands) {
    std::map<std::string, int> marker;

    std::set<std::string> completed;

    for (const Command &command : commands) {
        if (command.percentage_to_perform < 0) {
            throw std::invalid_argument("percentage_to_perform can't be negative");
        }

        if (command.params.find("-c") != std::string::npos) {
            marker[command.url] += command.percentage_to_perform;
        } else {
            marker[command.url] = command.percentage_to_perform;
        }

        if (marker[command.url] >= 100) {
            completed.insert(command.url);
        }
    }

    return completed.size();
}

#include <cassert>
int main() {
    // TEST
    assert(Weget( { Command { .url = "google.com", .params = "-c -f", .percentage_to_perform = 50 } }) == 0);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "", .params = "-c -f", .percentage_to_perform = 50 } }) == 0);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "", .params = "-c -f", .percentage_to_perform = 100 }, { Command { .url = "", .params = "-c -f", .percentage_to_perform = 50 } } }) == 1);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "", .params = "", .percentage_to_perform = 90 }, { Command { .url = "", .params = "-c -f", .percentage_to_perform = 10 } } }) == 1);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "google.com", .params = "-c -f", .percentage_to_perform = 50 }, Command { .url = "google.com", .params = "-c -f", .percentage_to_perform = 50 } }) == 1);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "google.com", .params = "-f", .percentage_to_perform = 50 }, Command { .url = "google.com", .params = "-c -f", .percentage_to_perform = 50 } }) == 1);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "google.com", .params = "-f -c", .percentage_to_perform = 50 }, Command { .url = "google.com", .params = "-f", .percentage_to_perform = 50 } }) == 0);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "google.com", .params = "-c -f", .percentage_to_perform = 50 }, Command { .url = "yahoo.com", .params = "-c -f", .percentage_to_perform = 50 } }) == 0);
    // TEST_END

    // TEST
    assert(Weget( { Command { .url = "google.com", .params = "-c -f", .percentage_to_perform = 50 }, Command { .url = "yahoo.com", .params = "-c -f", .percentage_to_perform = 50 }, Command { .url = "google.com", .params = "-c", .percentage_to_perform = 40 }, Command { .url = "google.com", .params =
            "-c -a", .percentage_to_perform = 10 } }) == 1);
    // TEST_END

    // TEST
    try {
        Weget( { Command { .url = "google.com", .params = "-c -f", .percentage_to_perform = -50 } });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

