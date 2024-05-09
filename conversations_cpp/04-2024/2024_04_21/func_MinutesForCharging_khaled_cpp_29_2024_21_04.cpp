/***
 * Prompt:
 
 
 khaled_cpp_29_2024_21_04: 62c37e58-a793-4b9c-8bfa-6895248696c8
 
 func_MinutesForCharging_khaled_cpp_29_2024_21_04
 
 Design me a C++ function named MinutesForCharging that accepts two inputs of type int, First input called mobile_battery_percentage which represents the initial value of mobile battery percentage, second input called road_distance_km which represents the distance that person need to walk. Note that person can charge phone with electricity and each percentage will takes 3 minutes and can charge phone with powerbank only if the initial mobile_battery_percentage is even and in this case each percentage will takes 2 minutes. The function should return the minimum number of minutes needed to charge the phone so that its battery doesn't die on the road. Please note that the percentage needed is 4 multiply the length of the road in KM, and note that all inputs values can't be negative. Don't forget to validate that.
 
 */
#include <string>
#include <stdexcept>

int MinutesForCharging(int mobile_battery_percentage, int road_distance_km) {
	if (mobile_battery_percentage < 0 || road_distance_km < 0) {
		throw std::invalid_argument("Invalid input");
	}

	int percentage_needed = road_distance_km * 4;

	if (percentage_needed > mobile_battery_percentage) {
		if (mobile_battery_percentage % 2 == 0) {
			return (percentage_needed - mobile_battery_percentage) * 2;
		} else {
			return (percentage_needed - mobile_battery_percentage) * 3;
		}
	}

	return 0;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	int input1 = 20;
	int input2 = 2;
	int output = 0;
	assert(MinutesForCharging(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = 20;
	input2 = 6;
	output = 8;
	assert(MinutesForCharging(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = 21;
	input2 = 6;
	output = 9;
	assert(MinutesForCharging(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = 0;
	input2 = 1;
	output = 8;
	assert(MinutesForCharging(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = 0;
	input2 = 0;
	output = 0;
	assert(MinutesForCharging(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = 1;
	input2 = 1;
	output = 9;
	assert(MinutesForCharging(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = -2;
	input2 = 1;
	output = 2;
	try {
		assert(MinutesForCharging(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = 1;
	input2 = -1;
	output = 2;
	try {
		assert(MinutesForCharging(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

