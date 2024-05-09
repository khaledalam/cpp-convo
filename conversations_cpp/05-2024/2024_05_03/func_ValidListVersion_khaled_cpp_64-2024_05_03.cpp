/***
 * Prompt:

 khaled_cpp_64-2024_05_03: c0c847e1-8603-4d1c-bbf0-eed0c51c33ae


 func_ValidListVersion_khaled_cpp_64-2024_05_03

 Write a C++ function called ValidListVersion, it will accept two inputs called list1 and list2 both of them of type std::vector<int>. The both lists should be the same size. The function should return boolean true if both list are similar otherwise return false. We call 2 lists similar if we can sort them in a way that makes the difference between each ith element in first list and ith element in the second list are always equal. Please don't forget to validate the input.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

bool ValidListVersion(std::vector<int> list1, std::vector<int> list2) {
	if (list1.size() != list2.size()) {
		throw std::invalid_argument("Lists should be same size");
	}

	sort(list1.begin(), list1.end());
	sort(list2.begin(), list2.end());

	int diff = list1.front() - list2.front();

	for (int idx = 0; idx < list1.size(); idx++) {
		if (list1[idx] - list2[idx] != diff) {
			return false;
		}
	}

	return true;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(ValidListVersion( { 1, 2, 3 }, { 2, 3, 4 }) == true);
	// TEST_END

	// TEST
	assert(ValidListVersion( { -1, 2, 3 }, { -2, 3, 4 }) == false);
	// TEST_END

	// TEST
	assert(ValidListVersion( { -1, 2, 3 }, { 0, 3, 4 }) == true);
	// TEST_END

	// TEST
	assert(ValidListVersion( { -1, 2, 6 }, { -2, 3, 9 }) == false);
	// TEST_END

	// TEST
	assert(ValidListVersion( { -1 }, { 10 }) == true);
	// TEST_END

	// TEST
	assert(ValidListVersion( { -1, 0 }, { 10, 9 }) == true);
	// TEST_END

	// TEST
	assert(ValidListVersion( { -1, 0 }, { 8, 9 }) == true);
	// TEST_END

	// TEST
	assert(ValidListVersion( { }, { }) == true);
	// TEST_END

	// TEST
	try {
		ValidListVersion( { -1 }, { 10, 1 });
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Lists should be same size");
	}
	// TEST_END
}

