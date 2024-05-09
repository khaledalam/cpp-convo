/***
 * Prompt:




 khaled_cpp_52_2024_26_04: e55f57dd-b9c7-420c-9dfc-53addef3718f


 func_Fishing_khaled_cpp_52_2024_26_04


 Write a C++ function called Fishing, it will accept 2 inputs. First input called fishes of type std::vector<std::pair<int, int>> which represent list of fishes that we can fish, first argument in each of these pairs refers to the danger of catching the fish and the second argument refers to the weight of the fish. Second inputs called hours_we_have of type int which refers to hours that we can spend on fishing today. The function should return number of type int which represent the sum of danger values of fishes that we will fish when we catch the highest weights fishes during hours_we_have hours. Please note that if 2 fishes are the same in the weight we choose the lowest danger value fish, also consider that we can catch 1 fish per hour, use lambda function in the solution and validate that there is no negative values in the inputs.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

int Fishing(std::vector<std::pair<int, int>> fishes, int hours_we_have) {
	int result = 0;

	if (hours_we_have < 0) {
		throw std::invalid_argument("Invalid input");
	}

	for (const std::pair<int, int> &fish : fishes) {
		if (0 > fish.first || 0 > fish.second) {
			throw std::invalid_argument("Invalid input");
		}
	}

	sort(fishes.begin(), fishes.end(), [](const std::pair<int, int> a, const std::pair<int, int> b) {
		if (a.second != b.second) {
			return a.second > b.second;
		}
		return (a.first < b.first);
	});

	int idx = 0;
	while (hours_we_have--) {
		if (fishes.empty()) {
			break;
		}

		result += fishes[idx++].first;
	}

	return result;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(Fishing(std::vector<std::pair<int, int>> { { 1, 3 }, { 1, 2 } }, 1) == 1);
	// TEST_END

	// TEST
	assert(Fishing(std::vector<std::pair<int, int>> { { 4, 3 }, { 1, 2 } }, 1) == 4);
	// TEST_END

	// TEST
	assert(Fishing(std::vector<std::pair<int, int>> { { 4, 2 }, { 1, 2 } }, 1) == 1);
	// TEST_END

	// TEST
	try {
		assert(Fishing(std::vector<std::pair<int, int>> { { -4, 3 } }, 1) == 3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert(Fishing(std::vector<std::pair<int, int>> { { 4, -3 } }, 1) == 3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert(Fishing(std::vector<std::pair<int, int>> { { 4, 3 }, { -1, 2 } }, 1) == 3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert(Fishing(std::vector<std::pair<int, int>> { { 4, 3 }, { 1, 2 } }, -1) == 3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

