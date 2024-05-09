#define ALIGNOF(...) alignof(__VA_ARGS__)
/*
 *
 *
 * Prompt:
 *
 * Create a C++ function named ScreenBrightnessLevel that accepts two inputs of type vector<char> called clicks and type boolean called booster.
 * The first input clicks represents the clicks that user performed to increase or decrease the screen brightness level, each character in the first input list can be plus "+" or minus "-" symbols.
 * The second input booster allow user to increase brightness up to 200% instead of 100%.
 * The function should returns pair of string and boolean pair<string, bool> first argument of it represents the final brightness level after performed the all clicks and second argument of it represents if device need to play warning buzz or not. Note that device play warning buzz if user click on some button to perform forbidden action, and forbidden action is like when brightness level for example is 0% and user try to decrease brightness level more by click on minus.
 * Note that plus symbol represents increase brightness by 10% and minus represents decrease brightness by 10%.
 * Final note, brightness level can not be less than 0% and can not be more than 100% if booster is false and can not be more than 200% if booster is true, also note that the initial brightness level is 0%

 *
 */

#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

std::pair<std::string, bool> ScreenBrightnessLevel(std::vector<char> clicks, bool booster) {
	int brightness = 0;
	bool make_buzz_flag = false;

	for (const char &click : clicks) {
		if (click != '+' && click != '-') {
			throw std::invalid_argument("Invalid input, only plus and minus characters are allowed");
		}

		int brightness_before = brightness;

		brightness = std::max(0, std::min((booster ? 200 : 100), brightness + (click == '+' ? 10 : -10)));

		make_buzz_flag |= (brightness_before == brightness);

	}

	std::stringstream ss;
	ss << brightness << "%";

	return make_pair(ss.str(), make_buzz_flag);
}

int main() {
	// TEST
	assert(ScreenBrightnessLevel( { '+', '+' }, false) == std::make_pair(std::string("20%"), false));
	// TEST_END

	// TEST
	assert(ScreenBrightnessLevel( { '-', '+' }, false) == std::make_pair(std::string("10%"), true));
	// TEST_END

	// TEST
	assert(ScreenBrightnessLevel( { '+', '-' }, false) == std::make_pair(std::string("0%"), false));
	// TEST_END

	// TEST
	assert(
			ScreenBrightnessLevel( { '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' }, false)
					== std::make_pair(std::string("100%"), true));
	// TEST_END

	// TEST
	assert(
			ScreenBrightnessLevel( { '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' }, true)
					== std::make_pair(std::string("120%"), false));
	// TEST_END

	// TEST
	assert(
			ScreenBrightnessLevel( { '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' }, true)
					== std::make_pair(std::string("200%"), true));
	// TEST_END

	// TEST
	try {
		assert(ScreenBrightnessLevel( { '*', '+' }, false) == std::make_pair(std::string(" "), false));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input, only plus and minus characters are allowed");
	}
	// TEST_END
}
