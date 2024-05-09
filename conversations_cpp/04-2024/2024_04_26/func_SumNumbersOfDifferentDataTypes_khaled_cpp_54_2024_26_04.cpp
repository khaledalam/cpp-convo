/***
 * Prompt:


 khaled_cpp_55_2024_27_04

 khaled_cpp_54_2024_26_04: 152204e6-5425-44b2-b0a7-223d27225430

 func_SumNumbersOfDifferentDataTypes_khaled_cpp_54_2024_26_04

 Write a C++ function called SumNumbersOfDifferentDataTypes, it will accept one input called number of type T where T is a typename that can be int or std::string "template<typename T>". This input represent a zero or positive number as int or std::string type. This function should return the sum of digits of the given input number. Please don't forget to validate input.




 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <type_traits>

template<typename T>
int SumNumbersOfDifferentDataTypes(T number) {
	int sum = 0;

	if constexpr (std::is_same<T, int>::value) {
		int num = (number + 0);

		if (num < 0) {
			throw std::invalid_argument("Input should be zero or positive number");
		}

		while (num) {
			sum += num % 10;
			num /= 10;
		}
	} else if constexpr (std::is_same<T, std::string>::value) {
		bool start_with_dash = false;
		int index = 0;
		for (const char &character : (std::string) number) {
			if (!index++) {
				if (character == '-') {
					start_with_dash = true;
				} else if (isdigit(character)) {
					sum += (character - '0');
				} else {
					throw std::invalid_argument("Input should be a valid number");
				}
				continue;
			}

			if (!isdigit(character)) {
				throw std::invalid_argument("Input should be a valid number");
			}

			sum += (character - '0');
		}

		if (start_with_dash) {
			throw std::invalid_argument("Input should be zero or positive number");
		}
	} else {
		throw std::invalid_argument("strings and integers data types only are allowed");
	}

	return sum;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(SumNumbersOfDifferentDataTypes(std::string("12")) == 3);
	// TEST_END

	// TEST
	assert(SumNumbersOfDifferentDataTypes(std::string("1")) == 1);
	// TEST_END

	// TEST
	assert(SumNumbersOfDifferentDataTypes(1) == 1);
	// TEST_END

	// TEST
	assert(SumNumbersOfDifferentDataTypes(0) == 0);
	// TEST_END

	// TEST
	assert(SumNumbersOfDifferentDataTypes(123) == 6);
	// TEST_END

	// TEST
	try {
		assert(SumNumbersOfDifferentDataTypes(std::string("-1")) == -1);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input should be zero or positive number");
	}
	// TEST_END

	// TEST
	try {
		SumNumbersOfDifferentDataTypes(-1);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input should be zero or positive number");
	}
	// TEST_END

	// TEST
	try {
		SumNumbersOfDifferentDataTypes(std::string("a"));
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input should be a valid number");
	}
	// TEST_END

	// TEST
	try {
		SumNumbersOfDifferentDataTypes(std::string("-12-3"));
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input should be a valid number");
	}
	// TEST_END

	// TEST
	try {
		SumNumbersOfDifferentDataTypes(1.5);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "strings and integers data types only are allowed");
	}
	// TEST_END
}

/***
 * Prompt:


 khaled_cpp_55_2024_27_04

 khaled_cpp_54_2024_26_04:

 Write a C++ function called SumNumbersOfDifferentDataTypes, it will accept one input called numbers of type std::vector<Type> where Type is a struct type. Please make Type struct deal with both types of std::string and int so that we can add strings and integers using it. this function should return the sum of the given input list numbers of both types std::string and int. Please note that if type is std::string you need to validate that its a valid number, it can be a negative number as well otherwise if it's invalid number throw an invalid_argument  exception.




 */

//#include <stdexcept>
//#include <iostream>
//#include <algorithm>
//#include <vector>
//
//struct Type {
//	enum DataType {
//		String, Integer
//	};
//
//	DataType GetType() const {
//		return type;
//	}
//
//	std::string GetValue() const {
//		if (type == String) {
//			return value.GetString();
//		}
//		return std::to_string(value.GetInteger());
//	}
//
//private:
//	union Union {
//		Union(const std::string &val) :
//				str_value(val) {
//		}
//		Union(const int &val) :
//				int_value(val) {
//		}
//
//		std::string GetString() const {
//			return str_value;
//		}
//		int GetInteger() const {
//			return int_value;
//		}
//	private:
//		std::string str_value;
//		int int_value;
//	};
//
//	DataType type;
//	Union value;
//};
//
//int SumNumbersOfDifferentDataTypes(Type number) {
//	int sum = 0;
//
//
//
//	for (const Type &number : numbers) {
//		int index = 0;
//		for (const char &character : number.GetValue()) {
//			if (!isdigit(character) || (character == '-' && index)) {
//				throw std::invalid_argument("Invalid input");
//			}
//			index++;
//		}
//
//		sum += std::stoi((std::string) number.GetValue());
//	}
//
//	return sum;
//}
//
//#include <cassert>
//int main(int argc, const char *argv[]) {
//
//	// TEST
//	assert(SumNumbersOfDifferentDataTypes(std::vector<Type> { Type { "1" } }) == 3);
//	// TEST_END
//
////
////	// TEST
////	assert(SumNumbersOfDifferentDataTypes( { Type("-1"), Type(2) }) == 1);
////	// TEST_END
////
////	// TEST
////	assert(SumNumbersOfDifferentDataTypes( { Type("1"), Type("-4"), Type(2) }) == -1);
////	// TEST_END
////
////	// TEST
////	try {
////		assert(SumNumbersOfDifferentDataTypes( { Type("-41-3"), Type(2) }) == -1);
////		assert(false);
////	} catch (const std::invalid_argument &e) {
////		assert(std::string(e.what()) == "Invalid input");
////	}
////	// TEST_END
////
////	// TEST
////	try {
////		assert(SumNumbersOfDifferentDataTypes( { Type("a"), Type(2) }) == -1);
////		assert(false);
////	} catch (const std::invalid_argument &e) {
////		assert(std::string(e.what()) == "Invalid input");
////	}
////	// TEST_END
//}
