/***
 * Prompt:


 Address, ZIP,


 khaled_cpp_10_2024_18_04: fe459218-ef32-46ec-826d-7ef401464b68







 Write me a C++ function named SortByMemoryAddress that accepts one input called memory_addresses of type std::vector<std::string>, Each string in the input list represent a memory address. Memory address is a string the starts with a prefix of "0x" plus 4 digits. The function should returns another sorted list of strings of type std::vector<std::string>. Please note that 2 addresses are sorted based on the last 4 digits in an ascending numerical order. Don't forget to validate the input and use lambda function in the solution.


 */

#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> SortByMemoryAddress(std::vector<std::string> memory_addresses)
{

	for (const std::string &address : memory_addresses)
	{
		if (address.length() != 6 || address[0] != '0' || address[1] != 'x')
		{
			throw std::invalid_argument("Invalid input");
		}
		for (int i = 2; i < 6; i++)
		{
			if (!isdigit(address[i]))
			{
				throw std::invalid_argument("Invalid input");
			}
		}
	}

	sort(memory_addresses.begin(), memory_addresses.end(), [](const std::string &first_address, std::string &second_address)
		 {
		std::string first_string = "", second_string = "";
		for (int i = 2; i < 6; i++) {
			first_string += first_address[i];
			second_string += second_address[i];
		}

		int first_number = std::stoi(first_string), second_number = std::stoi(second_string);

		return first_number < second_number; });

	return memory_addresses;
}

#include <cassert>
int main()
{
	// TEST
	std::vector<std::string> input{std::string("0x5678"), std::string("0x1234")};
	std::vector<std::string> output{std::string("0x1234"), std::string("0x5678")};
	assert(SortByMemoryAddress(input) == output);
	// TEST_END

	// TEST
	input = {std::string("0x1678"), std::string("0x1734")};
	output = {std::string("0x1678"), std::string("0x1734")};
	assert(SortByMemoryAddress(input) == output);
	// TEST_END

	// TEST
	input = {std::string("0x0010"), std::string("0x0001")};
	output = {std::string("0x0001"), std::string("0x0010")};
	assert(SortByMemoryAddress(input) == output);
	// TEST_END

	// TEST
	input = {std::string("0x1010")};
	output = {std::string("0x1010")};
	assert(SortByMemoryAddress(input) == output);
	// TEST_END

	// TEST
	input = {};
	output = {};
	assert(SortByMemoryAddress(input) == output);
	// TEST_END

	// TEST
	input = {std::string("0xh0000")};
	output = {};
	try
	{
		assert(SortByMemoryAddress(input) == output);
	}
	catch (const std::invalid_argument &e)
	{
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input = {std::string("0x12345")};
	output = {};
	try
	{
		assert(SortByMemoryAddress(input) == output);
	}
	catch (const std::invalid_argument &e)
	{
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input = {std::string("1x1234")};
	output = {};
	try
	{
		assert(SortByMemoryAddress(input) == output);
	}
	catch (const std::invalid_argument &e)
	{
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input = {std::string("0X1234")};
	output = {};
	try
	{
		assert(SortByMemoryAddress(input) == output);
	}
	catch (const std::invalid_argument &e)
	{
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}
