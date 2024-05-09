/***
 * Prompt:





 khaled_cpp_48_2024_25_04: f44052ab-e2d7-47cf-8452-268f066c49d8


 func_FootballReviewCamera_khaled_cpp_48_2024_25_04


 Write me a C++ function called FootballReviewCamera, it will accept two inputs, first input called ball_position of type Point where Point is a struct type that contains 2 members x and y of type double, and second input called area of type Circle where Circle is a struct type that contains member of type Point called point and member of type double called radius. The function should return boolean true if the ball lies on the given circle or inside it otherwise return false. Please note that the EPS for compare doubles values is 1e-3.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>

struct Point {
	double x, y;
};

struct Circle {
	Point point;
	double radius;
};

double DistanceBetweenTwoPoints(Point a, Point b) {
	return pow(fabs(a.x - b.x) + fabs(a.y - b.y), 0.5);
}

bool FootballReviewCamera(Point ball_position, Circle area) {
	const double EPS = 1e-3;

	if (area.radius < 0) {
		throw std::invalid_argument("Invalid input");
	}

	return (abs(DistanceBetweenTwoPoints(ball_position, area.point) - area.radius) <= EPS);
}

#include <cassert>
int main(int argc, const char *argv[]) {

	// TEST
	assert(FootballReviewCamera(Point { .x = 0, .y = 0 }, Circle { .point = Point { .x = 1, .y = 0 }, .radius = 1 }) == true);
	// TEST_END

	// TEST
	assert(FootballReviewCamera(Point { .x = 0, .y = 0 }, Circle { .point = Point { .x = 0, .y = 1 }, .radius = 1 }) == true);
	// TEST_END

	// TEST
	assert(FootballReviewCamera(Point { .x = 0, .y = 0 }, Circle { .point = Point { .x = 1, .y = 1 }, .radius = 1 }) == false);
	// TEST_END

	// TEST
	assert(FootballReviewCamera(Point { .x = 0, .y = 0 }, Circle { .point = Point { .x = 1, .y = 1 }, .radius = 1.41421 }) == true);
	// TEST_END

	// TEST

	// TEST_END

	// TEST
	try {
		assert(FootballReviewCamera(Point { .x = 0, .y = 0 }, Circle { .point = Point { .x = 1, .y = 1 }, .radius = -1.41421 }) == true);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

