/***
 * Prompt:




 khaled_cpp_17_2024_20_04: f15551d6-3de0-44c2-930c-85fd7eda98ed





 Create a C++ class named VerbalCalculator, this class will include a method named Calculate. This method will accept an input of type std::string, this string consists of verbal equation that consists of number, operation and another number. Operation can be one of these lowercase or uppercase values "plus", "minus", "multiply", "divided" and "modulo". Note also that only one operation can be passed in the input. This method should return number of type int that represents the value after perform calculation on this equation. Please don't forget to validate the inputs and note that the number can be negative, number should not start with 0, there should be space between each number and operation and throw an exception if divided by zero.


 */

#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

class VerbalCalculator {
public:
	int Calculate(const std::string &line) {
		int first_number, second_number;
		std::string operation;

		std::stringstream ss;

		ss << line;

		ss >> first_number;
		ss >> operation;
		ss >> second_number;

		ss.clear();

		ss << line;
		std::string first_number_string = std::string(""), second_number_string = std::string("");
		ss >> first_number_string;
		ss >> operation;
		ss >> second_number_string;

		if (std::to_string(first_number).length() != first_number_string.length() || std::to_string(second_number).length() != second_number_string.length()) {
			throw std::invalid_argument("Invalid input");
		}

		for (char &ch : operation) {
			ch = tolower(ch);
		}

		std::vector<std::string> operations = { std::string("plus"), std::string("minus"), std::string("multiply"), std::string("divided"), std::string("modulo") };

		if (std::find(operations.begin(), operations.end(), operation) == operations.end()) {
			throw std::invalid_argument("Invalid input");
		}

		int result = 0;
		if (operation == std::string("plus")) {
			result = first_number + second_number;
		}

		if (operation == std::string("minus")) {
			result = first_number - second_number;
		}

		if (operation == std::string("multiply")) {
			result = first_number * second_number;
		}

		if (operation == std::string("divided")) {
			if (!second_number) {
				throw std::invalid_argument("Invalid input");
			}
			result = first_number / second_number;
		}

		if (operation == std::string("modulo")) {
			result = (first_number % second_number);
		}

		return result;
	}
};

#include <cassert>
int main() {
	VerbalCalculator verbal_calculator;

	// TEST
	std::string input = std::string("1 plus 2");
	int output = 3;
	assert(verbal_calculator.Calculate(input) == output);
	//TEST_END

	// TEST
	std::string input_multispace = std::string("1    plus 2");
	int output_multispace = 3;
	assert(verbal_calculator.Calculate(input_multispace) == output_multispace);
	// TEST_END

	// TEST
	input = std::string("-1 plus 2");
	output = 1;
	assert(verbal_calculator.Calculate(input) == output);
	//TEST_END

	// TEST
	input = std::string("1 minus 2");
	output = -1;
	assert(verbal_calculator.Calculate(input) == output);
	//TEST_END

	// TEST
	input = std::string("3 multiply 2");
	output = 6;
	assert(verbal_calculator.Calculate(input) == output);
	//TEST_END

	// TEST
	input = std::string("3 divided 2");
	output = 1;
	assert(verbal_calculator.Calculate(input) == output);
	//TEST_END

	// TEST
	input = std::string("8 modulo 3");
	output = 2;
	assert(verbal_calculator.Calculate(input) == output);
	//TEST_END

	//TEST
	try {
		input = std::string("8 modulo3");
		output = 2;
		assert(verbal_calculator.Calculate(input) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	//TEST
	try {
		input = std::string("test modulo3");
		output = 2;
		assert(verbal_calculator.Calculate(input) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	//TEST
	try {
		input = std::string("08 plus 1");
		output = 2;
		assert(verbal_calculator.Calculate(input) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	//TEST
	try {
		input = std::string("8 divided 0");
		output = 91;
		assert(verbal_calculator.Calculate(input) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	//TEST
	try {
		input = std::string("");
		output = 0;
		assert(verbal_calculator.Calculate(input) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END
}
