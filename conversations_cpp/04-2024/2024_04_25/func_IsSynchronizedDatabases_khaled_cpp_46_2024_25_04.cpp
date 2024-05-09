/***
 * Prompt:





 khaled_cpp_46_2024_25_04: b44a3e42-e5f5-46ef-8ea3-1f6cfc01b06b


 func_IsSynchronizedDatabases_khaled_cpp_46_2024_25_04


 Write a C++ function called IsSynchronizedDatabases, it will accept two inputs called db_items_first and db_items_second both of type std::vector<std::string>. Please note that 2 databases called synchronized if they contain same items regardless case sensitivity. This function should return boolean true if both inputs are synchronized otherwise return false.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

bool IsSynchronizedDatabases(std::vector<std::string> db_items_first, std::vector<std::string> db_items_second) {
	std::vector<std::string> temp_first_db, temp_second_db;

	temp_first_db = db_items_first, temp_second_db = db_items_second;

	for (std::string &item : temp_first_db) {
		std::transform(item.begin(), item.end(), item.begin(), [](unsigned char c) {
			return std::tolower(c);
		});
	}

	for (std::string &item : temp_second_db) {
		std::transform(item.begin(), item.end(), item.begin(), [](unsigned char c) {
			return std::tolower(c);
		});
	}

	sort(temp_first_db.begin(), temp_first_db.end(), [](const std::string &a, const std::string &b) {
		return a < b;
	});

	sort(temp_second_db.begin(), temp_second_db.end(), [](const std::string &a, const std::string &b) {
		return a < b;
	});

	return temp_first_db == temp_second_db;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(IsSynchronizedDatabases( { std::string("abc") }, { std::string("abc") }) == true);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { std::string("abc"), std::string("Abc") }, { std::string("abc"), std::string("abc") }) == true);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { std::string("Abc") }, { std::string("abc") }) == true);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { std::string("ABC") }, { std::string("abc") }) == true);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { }, { std::string("abc") }) == false);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { std::string("Abc DEf") }, { std::string("Abc dEf") }) == true);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { std::string("") }, { std::string("") }) == true);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { std::string("") }, { }) == false);
	// TEST_END

	// TEST
	assert(IsSynchronizedDatabases( { }, { }) == true);
	// TEST_END
}

