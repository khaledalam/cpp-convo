/***
 * Prompt:


 khaled_cpp_55_2024_27_04: 6bb32eb5-58a2-4a43-a4b1-1d9844598ab4


 func_WifiSignal_khaled_cpp_55_2024_27_04

 Design me a C++ function called WifiSignal, it will accept two inputs. First input called routers_locations of type std::vector<std::pair<double, double>> which contains a list of pairs each pair of them represent coordinate of some router. Second input called user_location which represent the coordinate of the user device. This function should return coordinate of type std::pair<double, double> of the nearest router to the user device. Please use lambda function in the solution and add any helper functions inside WifiSignal function.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

std::pair<double, double> WifiSignal(std::vector<std::pair<double, double>> routers_locations, std::pair<double, double> user_location) {

	if (routers_locations.empty()) {
		throw std::invalid_argument(std::string("Invalid input"));
	}

	auto distanceBetweenTwoPoints = [](double first_x, double first_y, double second_x, double second_y) {
		return sqrt(pow(first_x - second_x, 2) + pow(first_y - second_y, 2));
	};

	sort(routers_locations.begin(), routers_locations.end(), [&user_location, &distanceBetweenTwoPoints](const std::pair<double, double> &location_a, const std::pair<double, double> &location_b) {

		double location_a_distance = distanceBetweenTwoPoints(location_a.first, location_a.second, user_location.first, user_location.second);
		double location_b_distance = distanceBetweenTwoPoints(location_b.first, location_b.second, user_location.first, user_location.second);

		return location_a_distance < location_b_distance;
	});

	return routers_locations.front();
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	std::pair<double, double> result = WifiSignal(std::vector<std::pair<double, double>> { std::make_pair<double, double>(1, 0), std::make_pair<double, double>(1, 1) }, std::make_pair<double, double>(0, 0));
	assert(fabs(result.first - 1.0) < 1e-9 && fabs(result.second - 0.0) < 1e-9);
	// TEST_END

	// TEST
	result = WifiSignal(std::vector<std::pair<double, double>> { std::make_pair<double, double>(0.0, -1.7), std::make_pair<double, double>(0.0, -1.5) }, std::make_pair<double, double>(0.0, 0.0));
	assert(fabs(result.first - 0.0) < 1e-9 && fabs(result.second - -1.5) < 1e-9);
	// TEST_END

	// TEST
	try {
		result = WifiSignal(std::vector<std::pair<double, double>> { }, std::make_pair<double, double>(0.0, 0.0));
		assert(fabs(result.first - 0.0) < 1e-9 && fabs(result.second - 0.0) < 1e-9);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == std::string("Invalid input"));
	}
	// TEST_END
}
