/***
 * Prompt:




 khaled_cpp_16_2024_19_04: f5843b5a-8eb5-4683-9b91-0d318318b67a



 func_MazeGrid_khaled_cpp_16_2024_19_04





 Design me a C++ function named MazeGrid that accepts two inputs first one called grid of type std::vector<std::string> and second one called entry_point of type std::pair<int, int>. The first input is 2d array of characters, each character can be dot "." or hash "#". The second input is the initial coordinate that will start moving from. The function should returns type of boolean true if you can react to any border point from the initial position. A border point is any character that is placed on the edge of the maze. You can start to move from the initial position in any direction, up, down, right or left if the position has a dot character, otherwise you can't move to the position. Don't forget to validate the inputs and use std::set and recursion in the solution.



 */

#include <stdexcept>
#include <string>
#include <vector>
#include <set>

void Visit(const std::vector<std::string> &grid, std::pair<int, int> position, bool &ok) {
	if (position.first < 0 || position.second >= grid[0].length() || ok || '.' != grid[position.first][position.second]) {
		return;
	}

	if (position.first == 0 || position.second == 0 || position.first == grid[0].length() - 1 || position.second == grid[0].length() - 1) {
		ok = true;
		return;
	}

	Visit(grid, { position.first, position.second + 1 }, ok);
	Visit(grid, { position.first, position.second - 1 }, ok);
	Visit(grid, { position.first + 1, position.second }, ok);
	Visit(grid, { position.first - 1, position.second }, ok);
}

bool MazeGrid(std::vector<std::string> grid, std::pair<int, int> entry_point) {
	bool is_valid_input = false;
	std::set<int> lengths;

	if (grid.empty()) {
		throw std::invalid_argument("Cannot input empty grid");
	}

	for (const std::string &line : grid) {
		lengths.insert(line.length());

		if (lengths.size() > 1) {
			throw std::invalid_argument("Invalid input");
		}

		for (const char &ch : line) {
			if (ch != '.' && ch != '#') {
				throw std::invalid_argument("Invalid input");
			}
		}
	}

	Visit(grid, entry_point, is_valid_input);

	return is_valid_input;
}

#include <cassert>
int main() {
	// TEST
	std::vector<std::string> input1 = { std::string("##"), std::string("##") };
	std::pair<int, int> input2 = std::make_pair(0, 0);
	bool output = false;
	assert(MazeGrid(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { std::string(".") };
	input2 = std::make_pair(0, 0);
	output = true;
	assert(MazeGrid(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { std::string(".."), std::string("..") };
	input2 = std::make_pair(0, 0);
	output = true;
	assert(MazeGrid(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { std::string("#.#"), std::string("#.#"), std::string("###") };
	input2 = std::make_pair(1, 1);
	output = true;
	assert(MazeGrid(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { std::string("###"), std::string("#.#"), std::string("###") };
	input2 = std::make_pair(1, 1);
	output = false;
	assert(MazeGrid(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { std::string("###"), std::string("##"), std::string("###") };
	input2 = std::make_pair(1, 1);
	output = false;
	try {
		assert(MazeGrid(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = { std::string(".."), std::string("..") };
	input2 = std::make_pair(0, 4);
	output = false;
	try {
		assert(MazeGrid(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = { };
	input2 = std::make_pair(0, 0);
	output = false;
	try {
		assert(MazeGrid(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Cannot input empty grid");
	}
	// TEST_END
}
