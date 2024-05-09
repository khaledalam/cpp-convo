/***
 * Prompt:

 khaled_cpp_68-2024_May_04: 4c73900e-276f-49ab-ba37-81b2505dd55b

 func_SortBy3Div_khaled_cpp_68-2024_May_04

 Create me a C++ function called SortBy3Div, it should accept a non-empty input called numbers of type std::vector<int>. The function should return another sorted list of numbers of type std::vector<int> where you should sort numbers based on if they accept division by 3 or not and if there are 2 or more numbers accept or not accept division by 3 then sort them based on the lowest value first. Please don't forget to validate input and use lambda function in the solution.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> SortBy3Div(std::vector<int> numbers) {

	if (numbers.empty()) {
		throw std::invalid_argument("input can't be empty");
	}

	std::sort(numbers.begin(), numbers.end(), [](const int &number_1, const int &number_2) {
		if ((number_1 % 3 == 0) && (number_2 % 3 == 0)) {
			return number_1 < number_2;
		}

		if (number_1 % 3 == 0) {
			return true;
		}

		if (number_2 % 3 == 0) {
			return false;
		}

		return number_1 < number_2;
	});

	return numbers;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert((SortBy3Div( { 1, 3, 5 }) == std::vector<int> { 3, 1, 5 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 1, 3, 3 }) == std::vector<int> { 3, 3, 1 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 0, 3, -1 }) == std::vector<int> { 0, 3, -1 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 9, 3 }) == std::vector<int> { 3, 9 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 3, 9 }) == std::vector<int> { 3, 9 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 9, 3, 12 }) == std::vector<int> { 3, 9, 12 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { -3, 3 }) == std::vector<int> { -3, 3 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 0 }) == std::vector<int> { 0 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 0, -1 }) == std::vector<int> { 0, -1 }));
	// TEST_END

	// TEST
	assert((SortBy3Div( { 0, -15 }) == std::vector<int> { -15, 0 }));
	// TEST_END

	// TEST
	try {
		SortBy3Div( { });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "input can't be empty");
	}
	// TEST_END
}

