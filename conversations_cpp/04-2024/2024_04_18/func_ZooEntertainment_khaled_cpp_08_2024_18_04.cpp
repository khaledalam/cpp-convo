/***
 * Prompt:

 khaled_cpp_08_2024_18_04: 5eb5e9d8-9784-49e0-b36c-0e4db65ea992




 Write me a C++ function called ZooEntertainment that accepts two inputs, first input called joy_levels of type std::list<int>, second input called ticket_limit of type int. The first input joy_levels contains a list of numbers that representing the joy level that the person can gain from visiting the animal with the same index. The second input ticket_limit should be zero or positive number that represent how many animals that the person can visit. The function should returns number of type int that represent the sum of the max joy level that the person can gain with his ticket. Please consider that there are negative joy levels. Use lambda function in your solution and don't forget to validate the second input.


 */

#include <list>
#include <algorithm>

int ZooEntertainment(std::list<int> joy_levels, int ticket_limit) {
	int max_joy_levels = 0;

	if (ticket_limit < 0) {
		throw std::invalid_argument("The second input should be zero or positive number");
	}

	joy_levels.sort([](const int &a, const int &b) {
		return a > b;
	});

	while (ticket_limit-- > 0) {
		max_joy_levels += joy_levels.front();
		joy_levels.pop_front();
	}

	return max_joy_levels;
}

#include <cassert>
int main() {
	// TEST
	assert(ZooEntertainment( { 1, 3, 2 }, 1) == 3);
	// TEST_END

	// TEST
	assert(ZooEntertainment( { 1, 3, 2 }, 2) == 5);
	// TEST_END

	// TEST
	assert(ZooEntertainment( { }, 2) == 0);
	// TEST_END

	// TEST
	assert(ZooEntertainment( { 1, 0, 111 }, 10) == 112);
	// TEST_END

	// TEST
	assert(ZooEntertainment( { -1, 5, -6, 1, 3 }, 2) == 8);
	// TEST_END

	// TEST
	assert(ZooEntertainment( { -1, 5, -6, 1, 3 }, 2) == 8);
	// TEST_END

	// TEST
	assert(ZooEntertainment( { -1, -5, -3 }, 2) == -4);
	// TEST_END

	// TEST
	try {
		assert(ZooEntertainment( { 9, 1 }, -1));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "The second input should be zero or positive number");
	}
	// TEST_END
}
