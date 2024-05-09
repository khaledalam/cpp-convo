/***
 * Prompt:




 khaled_cpp_28_2024_21_04: 7f5f8ef2-16d2-4ec7-8a0d-7988220b6843


 func_MaximumItems_khaled_cpp_28_2024_21_04

 Write me a C++ function named MaximumItems that accepts three inputs, First input called items_prices of type std::vector<int> which represents the price of each item, second input called money which represents the amount of money that we can buy with, third input called free_coupons which represent how many items that we can buy for free. The function should returns maximum count of items that we can buy using money and free_coupons. Please note that there all inputs values can't be negative, don't forget to validate that.



 */

#include <string>
#include <vector>

int MaximumItems(std::vector<int> items_prices, int money, int free_coupons) {
	int max_items_count = 0;

	if (money < 0 || free_coupons < 0) {
		throw std::invalid_argument("Invalid input");
	}

	sort(items_prices.begin(), items_prices.end());

	for (const int &item_price : items_prices) {
		if (item_price < 0) {
			throw std::invalid_argument("Invalid input");
		}

		if (item_price <= money) {
			money -= item_price;
			max_items_count++;
		} else if (free_coupons) {
			free_coupons--;
			max_items_count++;
		} else {
			break;
		}
	}

	return max_items_count;
}

#include <cassert>
int main() {
	// TEST
	std::vector<int> input1 = { 1, 2, 3 };
	int input2 = 3;
	int input3 = 0;
	int output = 2;
	assert(MaximumItems(input1, input2, input3) == output);
	// TEST_END

	// TEST
	input1 = { 1, 2, 3 };
	input2 = 3;
	input3 = 1;
	output = 3;
	assert(MaximumItems(input1, input2, input3) == output);
	// TEST_END

	// TEST
	input1 = { 1, 2, 3 };
	input2 = 0;
	input3 = 1;
	output = 1;
	assert(MaximumItems(input1, input2, input3) == output);
	// TEST_END

	// TEST
	input1 = { 1 };
	input2 = 5;
	input3 = 0;
	output = 1;
	assert(MaximumItems(input1, input2, input3) == output);
	// TEST_END

	// TEST
	input1 = { 1, 4, 6 };
	input2 = 10;
	input3 = 0;
	output = 2;
	assert(MaximumItems(input1, input2, input3) == output);
	// TEST_END

	// TEST
	input1 = { };
	input2 = 5;
	input3 = 0;
	output = 0;
	assert(MaximumItems(input1, input2, input3) == output);
	// TEST_END

	// TEST
	input1 = { -1 };
	input2 = 5;
	input3 = 0;
	output = 1;
	try {
		assert(MaximumItems(input1, input2, input3) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = { 1 };
	input2 = -5;
	input3 = 0;
	output = 1;
	try {
		assert(MaximumItems(input1, input2, input3) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = { 1, 4 };
	input2 = 5;
	input3 = -4;
	output = 1;
	try {
		assert(MaximumItems(input1, input2, input3) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}
