/***
 * Prompt:





 khaled_cpp_47_2024_25_04: 0b0e4a5c-dcaf-4a82-a342-36ac66aba7cb


 func_GitHubContributionGrid_khaled_cpp_47_2024_25_04

 Write me a C++ function called GitHubContributionGrid, it will accept two inputs called, first input called grid of type std::vector<std::string> and second input called pass_level of type int which refers to the required weight value to pass and it can't be negative. Each character in each string in the grid can contain one of these 3 characters "a" which equals 4 weight, "f" which equals 2 weight or "z" which equals 1 weight, any character can be in lower or upper case. This function should return boolean true if the sum of the grid characters can be greater than or equal to the pass_level value. Please use iterators in the solution and don't forget to validate the inputs.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

bool GitHubContributionGrid(std::vector<std::string> grid, int pass_level) {
	std::map<char, int> grader = { { 'a', 4 }, { 'f', 2 }, { 'z', 1 } };

	if (pass_level < 0) {
		throw std::invalid_argument("Invalid input");
	}

	int sum = 0;

	std::vector<std::string>::iterator line = grid.begin();

	while (line != grid.end()) {
		std::string::iterator c = (*line).begin();

		while (c != (*line).end()) {
			if (grader.find(tolower(*c)) == grader.end()) {
				throw std::invalid_argument("Invalid input");
			}

			sum += grader[tolower(*c)];

			c++;
		}

		line++;
	}

	return sum >= pass_level;
}

#include <cassert>
int main(int argc, const char *argv[]) {

	// TEST
	assert(GitHubContributionGrid( { std::string("AFZ") }, 2) == true);
	// TEST_END

	// TEST
	assert(GitHubContributionGrid( { std::string("AFZ"), std::string("AAA") }, 210) == false);
	// TEST_END

	// TEST
	assert(GitHubContributionGrid( { std::string(""), std::string("") }, 0) == true);
	// TEST_END

	// TEST
	assert(GitHubContributionGrid( { std::string("") }, 0) == true);
	// TEST_END

	// TEST
	try {
		assert(GitHubContributionGrid( { std::string("R") }, 0) == true);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert(GitHubContributionGrid( { std::string("") }, -1) == true);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

