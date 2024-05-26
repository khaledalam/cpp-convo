/***






 khaled_cpp_146_-2024_May_25: 93b57b4e-9162-4b8f-bdcf-df34886be4b7

 func_RollDice_khaled_cpp_146_-2024_May_25
 



Create a C++ function called RollDice that takes a non-empty array input called dices of type std::vector<std::string>,
where each string will be in the form of "NdM" for example ["3d6", "4d12", "1d10", "5d4"], the first number is the
number of dice to roll, the d just means "dice", it's just used to split up the two numbers, and the second number is
how many sides the dice have. So the above example of "3d6" means "roll 3 6-sided dice". Also, not all the dice we roll
are the normal cubes. A d6 is a cube, because it's a 6-sided die, but a d20 has twenty sides, so it looks a lot closer
to a ball than a cube. The first number, the number of dice to roll, can be any integer between 1 and 100, inclusive.
The second number, the number of sides of the dice, can be any integer between 2 and 100, inclusive.

This function should return the sum of all the rolls of that specified die, each on its own line. so if your input is
"3d6", the output should look something like 14: 6 3 5 You rolled 3 6-sided dice, and they added up to 14 and you print
out the result of each roll on the same line.

Please note that a dice roll is basically the same as picking a random number between 1 and 6 (or 12, or 20, or however
many sides the die has). You should use some way of randomly selecting a number within a range based on your input.
If you run your code 3+ times with the same inputs and it gives the same outputs, that wouldn't be super useful for a
game of D&D, would it? If that happens with your code, try to find a way around that. Please use regex in the solution
and some C++ random-number engine and don't forget to validate the input.


 */

#include <algorithm>
#include <iostream>
#include <random>
#include <regex>
#include <stdexcept>
#include <string>

std::string RollDice(std::vector<std::string> dices) {
    if (dices.empty()) {
        throw std::invalid_argument("dices can't be empty");
    }

    std::string result;

    const std::regex regex_dices("(([0-9]{1,3})(d)([0-9]{1,3}))");
    std::smatch matches;

    std::random_device rand;
    std::mt19937 rng(rand());

    for (auto &dice : dices) {
        if (!std::regex_search(dice, matches, regex_dices)) {
            throw std::invalid_argument("invalid dice(s)");
        }

        if (matches.size() != 5) {
            throw std::invalid_argument("invalid dice(s)");
        }

        int dices = atoi(matches[2].str().c_str());
        int sides = atoi(matches[4].str().c_str());

        std::uniform_int_distribution<int> uni(1, sides);

        int dice_sum = 0;
        std::string rolls;
        for (int ddx = 0; ddx < dices; ddx++) {
            auto roll = uni(rng);
            dice_sum += roll;
            rolls += rolls.size() > 0 ? " " + std::to_string(roll) : std::to_string(roll);
        }

        if (result.size() > 0) {
            result += '\n';
        }

        result += std::to_string(dice_sum) + ": " + rolls;
    }

    return result;
}

#include <cassert>
int main() {

    std::vector<std::string> dices = {"3d6", "1d10", "5d4", "100d100"};
    std::string result = RollDice(dices);

    int count = 0;
    for (int idx = 0; idx < result.size(); idx++) {
        if (result[idx] == ':') {
            count++;
        }
    }

    // TEST
    assert(count == dices.size());
    // TEST_END

    // TEST
    try {
        RollDice({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RollDice({""});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RollDice({"D12"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RollDice({"$#2"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}