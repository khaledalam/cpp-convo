/***
 * Prompt:




 khaled_cpp_27_2024_21_04: e93e220d-9af8-44d9-bf4a-dc8f037fedf4


 func_ShiftStone_khaled_cpp_27_2024_21_04


 Write me a C++ function named ShiftStone that accepts two inputs called board and operations both of them of type std::string. First input represents the initial value of board that can contains only dots "." and uppercase cross letter "X". Second input contains only less than symbol ">" which means shift "X" one step forward or greater than symbol "<" which means shift "X" one step backward. Please consider that if shift to right more than right border edge the "X" should go to the beginning of the board and if shift less than left border edge the "X" should go to the end of the board. The function should returns another board of type std::string after perform the shifting operations. Please don't forget to validate the inputs.



 */

#include <string>

std::string ShiftStone(std::string board, std::string operations) {

	int index, initial_index;

	if (std::count(board.begin(), board.end(), 'X') != 1 || board.length() < 1) {
		throw std::invalid_argument("Invalid input");
	}

	for (int i = 0; i < board.size(); i++) {
		if (board[i] != '.' && board[i] != 'X') {
			throw std::invalid_argument("Invalid input");
		}

		if (board[i] == 'X') {
			initial_index = index = i;
			break;
		}
	}

	for (const char op : operations) {
		if (op == '>') {
			index++;
			if (index >= board.length()) {
				index = 0;
			}
		} else if (op == '<') {
			index--;
			if (index < 0) {
				index = board.length() - 1;
			}
		} else {
			throw std::invalid_argument("Invalid input");
		}
	}

	board[initial_index] = '.';
	board[index] = 'X';

	return board;
}

#include <cassert>
int main() {
	// TEST
	std::string input1 = std::string("..X..");
	std::string input2 = std::string(">>");
	std::string output = std::string("....X");
	assert(ShiftStone(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("X");
	input2 = std::string(">");
	output = std::string("X");
	assert(ShiftStone(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string(".X");
	input2 = std::string(">");
	output = std::string("X.");
	assert(ShiftStone(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("..X");
	input2 = std::string("<>");
	output = std::string("..X");
	assert(ShiftStone(input1, input2) == output);
	// TEST_END
	return 0;
	// TEST
	input1 = std::string("..X");
	input2 = std::string("<<<");
	output = std::string("..X");
	assert(ShiftStone(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("..x");
	input2 = std::string("<<<");
	output = std::string("..X");
	try {
		assert(ShiftStone(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("..T");
	input2 = std::string("<<<");
	output = std::string("..X");
	try {
		assert(ShiftStone(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("...");
	input2 = std::string("<<<");
	output = std::string("..X");
	try {
		assert(ShiftStone(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("");
	input2 = std::string("");
	output = std::string("..X");
	try {
		assert(ShiftStone(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}
