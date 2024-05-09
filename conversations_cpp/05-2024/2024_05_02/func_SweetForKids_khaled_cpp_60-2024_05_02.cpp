/***
 * Prompt:

 khaled_cpp_61-2024_05_02



 khaled_cpp_60-2024_05_02: 59274ca3-1eff-47bc-a625-ced7d7b2ab9c


 func_SweetForKids_khaled_cpp_60-2024_05_02

 Write me a C++ function called SweetForKids, it will accept two inputs. First input called sweets of type std::vector<int> which represent a list of sweets' levels. Second input called kid_age of type int. This function should return number of type integer that represent how many sweets that are eligible for the kid. Please note that sweet is eligible for kid if its sweet's level less than or equal to kid age. Please validate that kid age and the sweet's levels can't be zero or negative.


 */

#include <stdexcept>
#include <iostream>
#include <vector>

int SweetForKids(const std::vector<int> &sweets, int kid_age) {
	if (kid_age < 1) {
		throw std::invalid_argument("Age can't be less than 1");
	}

	int eligible_count = 0;

	for (const int &sweet : sweets) {
		if (sweet < 1) {
			throw std::invalid_argument("Sweet level can't be less than 1");
		}

		if (sweet <= kid_age) {
			eligible_count++;
		}
	}

	return eligible_count;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(SweetForKids( { 1, 2, 3 }, 1) == 1);
	// TEST_END

	// TEST
	assert(SweetForKids( { 1, 2, 3 }, 2) == 2);
	// TEST_END

	// TEST
	assert(SweetForKids( { 1, 2, 3 }, 3) == 3);
	// TEST_END

	// TEST
	assert(SweetForKids( { 1, 2, 3 }, 4) == 3);
	// TEST_END

	// TEST
	assert(SweetForKids( { 2, 3 }, 1) == 0);
	// TEST_END

	// TEST
	assert(SweetForKids( { }, 1) == 0);
	// TEST_END

	// TEST
	try {
		SweetForKids( { -1, 2, 3 }, 4);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Sweet level can't be less than 1");
	}
	// TEST_END

	// TEST
	try {
		SweetForKids( { 0, 2, 3 }, 4);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Sweet level can't be less than 1");
	}
	// TEST_END

	// TEST
	try {
		SweetForKids( { 1, 2, 3 }, -4);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Age can't be less than 1");
	}
	// TEST_END

	// TEST
	try {
		SweetForKids( { 1, 2, 3 }, 0);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Age can't be less than 1");
	}
	// TEST_END
}

