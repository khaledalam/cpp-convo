/***
 * Prompt:




 khaled_cpp_51_2024_25_04: bcb355cc-26c7-430b-83cd-0f660ed068f1


 func_Trees_khaled_cpp_51_2024_25_04

 Write a C++ function called Trees, it will accept three inputs. First input called trees_water_level of type std::vector<int> which represent a list of the water level of each tree we have, 1 level can make the tree survive for 1 day. Second input called water_we_have of type int, which represent the water that we can add to trees levels. Third input is travel_days of type int which represent how many days our trip. This function should return number of type int the represent the additional water that we will need beside the water_we_have so that the tree stay live during our trip. Please note that all inputs including the trees_water_level values can't be negative.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

int Trees(std::vector<int> trees_water_level, int water_we_have, int travel_days) {
	int result = 0;

	if (water_we_have < 0 || travel_days < 0) {
		throw std::invalid_argument("Inputs can not be negative");
	}

	for (const int &level : trees_water_level) {
		if (level < 0) {
			throw std::invalid_argument("Inputs can not be negative");
		}

		result += std::max(0, travel_days - level);
	}

	return result - water_we_have;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(Trees( { 1, 2, 3 }, 1, 3) == 2);
	// TEST_END

	// TEST
	assert(Trees( { 1, 2, 3 }, 3, 4) == 3);
	// TEST_END

	// TEST
	assert(Trees( { 0, 2, 3 }, 0, 3) == 4);
	// TEST_END

	// TEST
	try {
		assert(Trees( { 1, -2, 3 }, 1, 3) == 2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Inputs can not be negative");
	}
	// TEST_END

	// TEST
	try {
		assert(Trees( { 1, 2, 3 }, -1, 3) == 2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Inputs can not be negative");
	}
	// TEST_END

	// TEST
	try {
		assert(Trees( { 1, 2, 3 }, 1, -3) == 2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Inputs can not be negative");
	}
	// TEST_END
}

