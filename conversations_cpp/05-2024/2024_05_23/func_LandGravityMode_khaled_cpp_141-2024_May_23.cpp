/***
 * Prompt:




 khaled_cpp_141-2024_May_23: 1b16014e-6c7e-43e4-a39a-aa962254175b

 func_LandGravityMode_khaled_cpp_141-2024_May_23

Create a C++ function called LandGravityMode that takes a non-empty input called blocks of type std::vector<std::vector<char>> that represent some suspended blocks (represented as hashtags), each character can be a hashtag or dot. This function should return another 2d array of type std::vector<std::vector<char>> which shows the end result once gravity is switched on. Please note that when gravity is switched on all hashtags cells should go down in their columns. Don't forget to validate the inputs.

 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::vector<char>> LandGravityMode(std::vector<std::vector<char>> blocks) {
    if (blocks.empty()) {
        throw std::invalid_argument("blocks can't be empty");
    }

    int len_first_row = blocks[0].size();

    for (const std::vector<char> row : blocks) {
        if (row.size() != len_first_row) {
            throw std::invalid_argument("all rows should be with the same size");
        }

        for (const char &character : row) {
            if (character != '.' && character != '#') {
                throw std::invalid_argument("only dot and hashtag characters are allowed");
            }
        }
    }

    for (int ydx = blocks.size() - 2; ydx >= 0; ydx--) {

        for (int xdx = 0; xdx < blocks[0].size(); xdx++) {

            for (int drop = ydx; drop < (blocks.size() - 1) && blocks[drop][xdx] == '#' && blocks[drop + 1][xdx] == '.';
                 drop++) {
                blocks[drop + 1][xdx] = '#';
                blocks[drop][xdx] = '.';
            }
        }
    }

    return blocks;
}

#include <cassert>
int main() {
    // TEST
    assert((LandGravityMode({{'.', '#', '#', '.'}, {'.', '.', '.', '.'}, {'.', '.', '.', '.'}, {'.', '.', '.', '.'}}) ==
            std::vector<std::vector<char>>{
                {'.', '.', '.', '.'}, {'.', '.', '.', '.'}, {'.', '.', '.', '.'}, {'.', '#', '#', '.'}}));
    // TEST_END

    // TEST
    assert((LandGravityMode({{'.', '#', '#', '.'}, {'.', '.', '#', '.'}, {'.', '.', '.', '.'}, {'.', '.', '.', '.'}}) ==
            std::vector<std::vector<char>>{
                {'.', '.', '.', '.'}, {'.', '.', '.', '.'}, {'.', '.', '#', '.'}, {'.', '#', '#', '.'}}));
    // TEST_END

    // TEST
    assert((LandGravityMode({{'.', '#', '#', '#', '#', '.'},
                             {'#', '.', '.', '#', '#', '.'},
                             {'.', '#', '.', '.', '.', '.'},
                             {'.', '.', '.', '.', '.', '.'}}) ==
            std::vector<std::vector<char>>{{'.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '.', '.'},
                                           {'.', '#', '.', '#', '#', '.'},
                                           {'#', '#', '#', '#', '#', '.'}}));
    // TEST_END

    // TEST
    try {
        LandGravityMode({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LandGravityMode({{'.', '#'}, {'.'}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LandGravityMode({{'^'}, {'.'}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}