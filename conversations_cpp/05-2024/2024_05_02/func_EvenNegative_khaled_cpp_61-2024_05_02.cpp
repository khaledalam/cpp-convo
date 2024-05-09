/***
 * Prompt:

 khaled_cpp_61-2024_05_02: d4624936-4cd4-44d2-a591-d9de227dac05


 func_EvenNegative_khaled_cpp_61-2024_05_02

 Design me a C++ function called EvenNegative, it will accept an input called numbers of type std::vector<int>. This function should return a number of type integer that represent how many negative numbers in the list that are even. Please note that even number is the number that accept division by 2, also not that zero is not acceptable value so please validate the input regarding that.


 */

#include <stdexcept>
#include <iostream>
#include <vector>

int EvenNegative(const std::vector<int> &numbers) {

	int result = 0;

	for (const int &number : numbers) {
		if (number == 0) {
			throw std::invalid_argument("Zero is not a valid value");
		}

		if (number < 0 && (number % 2 == 0)) {
			result++;
		}
	}

	return result;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(EvenNegative( { 1, -2, 3 }) == 1);
	// TEST_END

	// TEST
	assert(EvenNegative( { }) == 0);
	// TEST_END

	// TEST
	assert(EvenNegative( { 1, 2, -3 }) == 0);
	// TEST_END

	// TEST
	assert(EvenNegative( { -1, -2, 3, -4 }) == 2);
	// TEST_END

	// TEST
	try {
		EvenNegative( { 0, 2, 3 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Zero is not a valid value");
	}
	// TEST_END
}

