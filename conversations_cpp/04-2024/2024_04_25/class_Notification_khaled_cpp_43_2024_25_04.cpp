/***
 * Prompt:





 khaled_cpp_43_2024_25_04: df2d2200-c55d-4e46-a8b3-cba6d34a8d5d

 class_Notification_khaled_cpp_43_2024_25_04


 Design a C++ class called Notification which contains a function called Display, it accepts two inputs, first input called messages of type std::vector<Message> where Message is a struct that contains text member of type std::string and order member of type int, second input called output of type std::stringstream. This function should return nothing of type void and sort the messages based on the lowest order first and if two orders are equal then sort them based on the length of the text and if the lengths also equal sort them by their initial position in the first input and after that put each message text followed by endline to the second input. Please note that order can be negative. Use lambda function in the solution.


 */

#include <stdexcept>

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

struct Message {
	std::string text;
	int order;
};

class Notification {
public:
	void Display(std::vector<Message> messages, std::stringstream &output) {

		sort(messages.begin(), messages.end(), [](const Message &a, const Message &b) {
			if (a.order == b.order) {
				return a.text.length() < b.text.length();
			}

			return a.order < b.order;
		});

		for (const Message &message : messages) {
			output << message.text << std::endl;
		}
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	Notification notification;

	std::stringstream output;
	// TEST
	notification.Display( { Message { .text = "Test", .order = 0 } }, output);
	assert(std::string(output.str()) == std::string("Test\n"));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { Message { .text = "Test", .order = 0 } }, output);
	assert(output.str() != std::string("Test"));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { Message { .text = "Test again", .order = 0 } }, output);
	assert(output.str() == std::string("Test again\n"));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { Message { .text = "Test 0", .order = 0 }, Message { .text = "Test -3", .order = -3 } }, output);
	assert(output.str() == std::string("Test -3\nTest 0\n"));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { Message { .text = "Test 0", .order = 0 }, Message { .text = "Te 0", .order = 0 } }, output);
	assert(output.str() == std::string("Te 0\nTest 0\n"));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { }, output);
	assert(output.str() == std::string(""));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { Message { .text = "0 Test 1", .order = 1 }, Message { .text = "1 Te 1", .order = 1 }, Message { .text = "Te 0", .order = 0 } }, output);
	assert(output.str() == std::string("Te 0\n1 Te 1\n0 Test 1\n"));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { Message { .text = "0K", .order = 1 }, Message { .text = "OK", .order = 1 }, Message { .text = "Te 0", .order = 0 } }, output);
	assert(output.str() == std::string("Te 0\n0K\nOK\n"));
	// TEST_END

	// TEST
	output.str("");
	notification.Display( { Message { .text = "oK", .order = 1 }, Message { .text = "0K", .order = 1 }, Message { .text = "Te 0", .order = 0 } }, output);
	assert(output.str() == std::string("Te 0\noK\n0K\n"));
	// TEST_END
}

