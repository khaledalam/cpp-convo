/***
 * Prompt:

 khaled_cpp_69-2024_May_04: 5cc40a1b-7417-417c-88bf-e84b00f71dc5

 func_GetSession_khaled_cpp_69-2024_May_04

 Create a C++ function called GetSession, it should accept two inputs, first input should be a non-empty list called people_kids_ages of type std::vector<int>, second input called how_many of type int. The function should sort the list of kids' ages and return another list of type std::vector<int> where the kids who their ages are between 4 and 10 to be at the beginning of the list and the remain kids to be at the end of the list, and in general each group whatever in 4 to 10 range ages or outside this range should be sorted in an ascending order. Please note that ages can't be zero or negative and how_many input should be less than or equal to people_kids_ages size.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> GetSession(std::vector<int> people_kids_ages, int how_many) {
	if (people_kids_ages.empty()) {
		throw std::invalid_argument("people_kids_ages can't be empty");
	}

	if (how_many < 1) {
		throw std::invalid_argument("how_many should be greater than zero");
	}

	if (how_many > people_kids_ages.size()) {
		throw std::invalid_argument("how_many can't be grater than count of people_kids_ages' items");
	}

	for (const int &age : people_kids_ages) {
		if (age < 1) {
			throw std::invalid_argument("kid age should be greater than zero");
		}
	}

	std::sort(people_kids_ages.begin(), people_kids_ages.end(), [](const int &age_1, const int &age_2) {
		if ((age_1 >= 4 && age_1 <= 10) && (age_2 < 4 || age_2 > 10)) {
			return true;
		}
		return age_1 < age_2;
	});

	std::vector<int> result;

	for (size_t idx = 0; idx < how_many; idx++) {
		result.push_back(people_kids_ages[idx]);
	}

	return result;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert((GetSession( { 1, 3, 5 }, 2) == std::vector<int> { 5, 1 }));
	// TEST_END

	// TEST
	assert((GetSession( { 4, 9, 11, 15 }, 1) == std::vector<int> { 4 }));
	// TEST_END

	// TEST
	assert((GetSession( { 6, 4, 11, 15 }, 2) == std::vector<int> { 4, 6 }));
	// TEST_END

	// TEST
	assert((GetSession( { 6, 4, 15, 11 }, 4) == std::vector<int> { 4, 6, 11, 15 }));
	// TEST_END

	// TEST
	assert((GetSession( { 15, 2 }, 2) == std::vector<int> { 2, 15 }));
	// TEST_END

	// TEST
	assert((GetSession( { 12 }, 1) == std::vector<int> { 12 }));
	// TEST_END

	// TEST
	try {
		GetSession( { }, 1);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "people_kids_ages can't be empty");
	}
	// TEST_END

	// TEST
	try {
		GetSession( { 1 }, -1);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "how_many should be greater than zero");
	}
	// TEST_END

	// TEST
	try {
		GetSession( { 1 }, 0);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "how_many should be greater than zero");
	}
	// TEST_END

	// TEST
	try {
		GetSession( { 0 }, 1);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "kid age should be greater than zero");
	}
	// TEST_END

	// TEST
	try {
		GetSession( { -1 }, 1);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "kid age should be greater than zero");
	}
	// TEST_END

	// TEST
	try {
		GetSession( { 1, 4, 5 }, 4);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "how_many can't be grater than count of people_kids_ages' items");
	}
	// TEST_END
}

