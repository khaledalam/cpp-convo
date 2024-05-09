/***
 * Prompt:


 khaled_cpp_60-2024_05_02


 khaled_cpp_59_2024_28_04: c13fc1f9-6647-4b1e-83b4-e41d22c5ce3f

 func_BuyTable_khaled_cpp_59_2024_28_04


 Write me a C++ function called BuyTable, it will accept two inputs. First input called tables of type std::vector<std::pair<int, int>> which represent a tables in the market as a list of pairs, each pair represent table width and height. Second input called requirements of type std::pair<int, int>, which represent the needed table width and height. This function should return pair of type std::pair<int, int> which represent the best fit table that we will buy. Please consider that the best fit table is the table where the difference between widths and heights of it and the needed table is less than or equal to 5. Table can't be less than the needed height or the needed width. if there are 2 tables match the condition then get the one that has the lowest difference between hights and widths between the market table and the needed one, and if both tables differences are the same bring the first one that appears in the list. Please also note that all values should be positive and if there are no suitable tables in the market throw an invalid_argument.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

std::pair<int, int> BuyTable(const std::vector<std::pair<int, int>> &tables, const std::pair<int, int> &requirements) {
	if (requirements.first <= 0 || requirements.second <= 0) {
		throw std::invalid_argument("Input values should be positive");
	}

	std::pair<int, int> best_fit;
	int best_fit_diff = 1e9;
	bool found_suitable_table = false;

	for (const std::pair<int, int> &table : tables) {
		if (table.first <= 0 || table.second <= 0) {
			throw std::invalid_argument("Input values should be positive");
		}

		bool valid = table.first >= requirements.first && table.second >= requirements.second;

		if (!valid) {
			continue;
		}

		found_suitable_table |= ((table.first - requirements.first) <= 5 && (table.second - requirements.second) <= 5);

		int total_diff = (table.first - requirements.first) + (table.second - requirements.second);
		if (total_diff < best_fit_diff) {
			best_fit_diff = total_diff;
			best_fit = table;
		}
	}

	if (!found_suitable_table) {
		throw std::invalid_argument("No suitable table");
	}

	return best_fit;
}

#include <cassert>

#define MP std::pair<int, int>

int main(int argc, const char *argv[]) {
	// TEST
	std::pair<int, int> result = BuyTable(std::vector<MP> { MP { 2, 3 }, MP { 1, 1 } }, MP { 1, 2 });
	std::pair<int, int> excpect = MP { 2, 3 };
	assert(result.first == excpect.first && result.second == excpect.second);
	// TEST_END

	// TEST
	result = BuyTable(std::vector<MP> { MP { 2, 3 }, MP { 1, 2 } }, MP { 1, 2 });
	excpect = MP { 1, 2 };
	assert(result.first == excpect.first && result.second == excpect.second);
	// TEST_END

	// TEST
	result = BuyTable(std::vector<MP> { MP { 5, 3 }, MP { 3, 3 } }, MP { 1, 2 });
	excpect = MP { 3, 3 };
	assert(result.first == excpect.first && result.second == excpect.second);
	// TEST_END

	// TEST
	result = BuyTable(std::vector<MP> { MP { 2, 3 }, MP { 3, 4 } }, MP { 1, 2 });
	excpect = MP { 2, 3 };
	assert(result.first == excpect.first && result.second == excpect.second);
	// TEST_END

	// TEST
	try {
		BuyTable(std::vector<MP> { }, MP { 1, 2 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "No suitable table");
	}
	// TEST_END

	// TEST
	try {
		BuyTable(std::vector<MP> { { 2, 1 } }, MP { 1, 2 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "No suitable table");
	}
	// TEST_END

	// TEST
	try {
		BuyTable(std::vector<MP> { { 2, 1 }, { 1, 1 } }, MP { 1, 2 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "No suitable table");
	}
	// TEST_END

	// TEST
	try {
		BuyTable(std::vector<MP> { { 0, 1 } }, MP { 1, 2 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input values should be positive");
	}
	// TEST_END

	// TEST
	try {
		BuyTable(std::vector<MP> { { -1, 1 } }, MP { 1, 2 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input values should be positive");
	}
	// TEST_END

	// TEST
	try {
		BuyTable(std::vector<MP> { { 10, 10 } }, MP { -1, 2 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input values should be positive");
	}
	// TEST_END
}

