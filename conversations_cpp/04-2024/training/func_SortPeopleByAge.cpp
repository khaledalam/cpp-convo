/*
 *
 * e3027e18-1de1-4b4e-9411-1b470bd38fe8
 *
 * Prompt:
 *
 * Write me a C++ function named SortPeopleByAge that accepts two input parameters, first input is a list of names of type vector<string>, second input is a list of ages of type vector<int>, each age number in the second input represents the age of the person name from the first input of the same index. The function should returns a sorted list of names of type vector<string> in an ascending order based on ages. Please take in your consideration that if 2 persons has the same ago sort them alphabetically based on their names, also try to use lambda function for sorting. Don't forget to validate that both inputs need to have the same size.
 *
 */

// Function Signature:
// bool IsValidSoftwareVersion(std::string software_version)
#include <cassert>
#include <string>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> SortPeopleByAge(std::vector<std::string> names, std::vector<int> ages) {

	if (names.size() != ages.size()) {
		throw std::invalid_argument("Both input lists should be with same length.");
	}

	std::vector<std::pair<std::string, int>> persons;
	std::vector<std::string> sorted_names;

	int idx = 0;
	for (std::string name : names) {
		persons.push_back( { name, ages[idx++] });
	}

	sort(persons.begin(), persons.end(), [](const std::pair<std::string, int> a, const std::pair<std::string, int> b) {
		if (a.second < b.second) {
			return true;
		}
		if (a.second > b.second) {
			return false;
		}

		return a.first < b.first;
	});

	for (std::pair<std::string, int> person : persons) {
		sorted_names.push_back(person.first);
	}

	return sorted_names;
}

int main() {
	// TEST
	std::vector<std::string> names { "adam", "sara", "james" };
	std::vector<int> ages { 20, 30, 26 };
	std::vector<std::string> output { "adam", "james", "sara" };
	assert(SortPeopleByAge(names, ages) == output);
	// TEST_END

	// TEST
	names = { "Ali", "Khaled", "AHMED" };
	ages = { 35, 27, 29 };
	output = { "Khaled", "AHMED", "Ali" };
	assert(SortPeopleByAge(names, ages) == output);
	// TEST_END

	// TEST
	names = { "Yaser", "Khaled" };
	ages = { 35 };
	output = { };
	try {
		assert(SortPeopleByAge(names, ages) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Both input lists should be with same length.");
	}
	// TEST_END

	// TEST
	names = { "Ali", "Khaled", "AHMED" };
	ages = { 30, 30, 30 };
	output = { "AHMED", "Ali", "Khaled" };
	assert(SortPeopleByAge(names, ages) == output);
	// TEST_END
}
