/***
 * Prompt:


 khaled_cpp_58_2024_28_04



 khaled_cpp_57_2024_28_04: 0bf9700a-5591-40b3-9caa-ec57fb33cdf6





 Design me a C++ function named Deadlock, this function will accept two parameters called addresses_of_resources_mapper_1 and addresses_of_resources_mapper_2 both of type std::vector<int> each of them contain the index of the resource address that the i-th process needs to use. This function should return boolean true if there is 2 processes i-th need to use the same resource otherwise return false. Please note that one process can use same resource multiple times without any problem.


 */

#include <stdexcept>

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

bool Deadlock(std::vector<int> addresses_of_resources_mapper_1, std::vector<int> addresses_of_resources_mapper_2) {

	std::map<int, std::set<int>> per_address;

	int index_1 = 0, index_2 = 0;
	for (const int &address : addresses_of_resources_mapper_1) {
		per_address[address].insert(index_1++);

		if (per_address[address].size() > 1) {
			return true;
		}
	}

	for (const int &address : addresses_of_resources_mapper_2) {
		per_address[address].insert(index_2++);

		if (per_address[address].size() > 1) {
			return true;
		}
	}

	return false;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert((Deadlock( { 1, 2, 3 }, { 4 }) == false));
	// TEST_END

	// TEST
	assert((Deadlock( { 1, 2, 1 }, { 4 }) == true));
	// TEST_END

	// TEST
	assert((Deadlock( { 1, 2, 3 }, { 1 }) == false));
	// TEST_END

	// TEST
	assert((Deadlock( { 1, 2, 3 }, { 2 }) == true));
	// TEST_END

	// TEST
	assert((Deadlock( { 1, 2, 3 }, { }) == false));
	// TEST_END

	// TEST
	assert((Deadlock( { }, { 1 }) == false));
	// TEST_END

	// TEST
	assert((Deadlock( { }, { }) == false));
	// TEST_END
}
