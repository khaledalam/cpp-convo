/***
 * Prompt:





 khaled_cpp_44_2024_25_04: 77c76a44-c820-4406-9382-8104787347df

 class_Bicycle_khaled_cpp_44_2024_25_04

 Design me a C++ class called Bicycle which contains a function called Dynamo, it accepts three inputs, first input called distance_in_km of type int, second input called options of type std::vector<int>, third input called time_allowed_in_hours of type int. Note that distance_in_km, each value of options and time_allowed_in_hours should be zero or positive numbers. This function should returns true if we can cover the whole distance with or without using any of the given options, where each option refers to how many KM that bicycle dynamo can generate per hour otherwise return false. Note that initially bicycle must work for 1 KM without need for any dynamo, and this 1 KM will cost 1 hour from the time_allowed_in_hours. Don't forget to validate the inputs.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

class Bicycle {
public:
	bool Dynamo(int distance_in_km, std::vector<int> options, int time_allowed_in_hours) {
		if (distance_in_km < 0) {
			throw std::invalid_argument("distance_in_km can't be negative");
		}

		if (time_allowed_in_hours < 0) {
			throw std::invalid_argument("time_allowed_in_hours can't be negative");
		}

		for (const int &option : options) {
			if (option < 0) {
				throw std::invalid_argument("option can't be negative");
			}
		}

		if (!distance_in_km || (distance_in_km == 1 && time_allowed_in_hours > 0)) {
			return true;
		}

		distance_in_km--, time_allowed_in_hours--;

		for (const int &option : options) {

			if (option * time_allowed_in_hours >= distance_in_km) {
				return true;
			}
		}

		return false;
	}
};

#include <cassert>
int main() {
	Bicycle bicycle;

	// TEST
	assert(bicycle.Dynamo(1, { 1 }, 3) == true);
	// TEST_END

	// TEST
	assert(bicycle.Dynamo(1, { }, 0) == false);
	// TEST_END

	// TEST
	assert(bicycle.Dynamo(0, { }, 0) == true);
	// TEST_END

	// TEST
	assert(bicycle.Dynamo(1, { }, 1) == true);
	// TEST_END

	// TEST
	assert(bicycle.Dynamo(10, { 2 }, 3) == false);
	// TEST_END

	// TEST
	assert(bicycle.Dynamo(10, { 2, 5 }, 3) == true);
	// TEST_END

	// TEST
	try {
		bicycle.Dynamo(-1, { 1 }, 3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "distance_in_km can't be negative");
	}
	// TEST_END

	// TEST
	try {
		bicycle.Dynamo(0, { -1 }, 0);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "option can't be negative");
	}
	// TEST_END

	// TEST
	try {
		bicycle.Dynamo(1, { -1 }, 3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "option can't be negative");
	}
	// TEST_END

	// TEST
	try {
		bicycle.Dynamo(1, { 1 }, -3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "time_allowed_in_hours can't be negative");
	}
	// TEST_END
}

