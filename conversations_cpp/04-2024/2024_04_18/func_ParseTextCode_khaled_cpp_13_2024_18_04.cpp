/***
 * Prompt:




 khaled_cpp_13_2024_18_04: 264bf0de-9e62-4b8b-805a-2451a9cf26b2






 Design me a C++ function named ParseTextCode that accepts one input called text of type std::string. The function should returns another text of type std::string that represent the final output after reformatting the string. Please make the function to reformat the string by replacing each 2 consecutive backticks to <code> and </code>.



 */

#include <string>
#include <map>

std::string ParseTextCode(std::string text) {
	bool open = false;
	int last_index = 0;

	for (int i = 0; i < text.length(); i++) {
		if (!open && text[i] == '`') {
			open = true;
			last_index = i;
		} else if (open && text[i] == '`') {
			open = false;

			text.erase(last_index, 1);
			text.erase(i - 1, 1);

			text.insert(i - 1, std::string("</code>"));
			text.insert(last_index, std::string("<code>"));
		}
	}

	return text;
}

#include <cassert>
int main() {
	// TEST
	std::string input = std::string("`Test` Now.");
	std::string output = std::string("<code>Test</code> Now.");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("'Test' Now");
	output = std::string("'Test' Now");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("This is `some code` here!");
	output = std::string("This is <code>some code</code> here!");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("This is ``some cod`e` here!");
	output = std::string("This is <code></code>some cod<code>e</code> here!");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("This is `some cod`e` here!");
	output = std::string("This is <code>some cod</code>e` here!");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("This is `some cod`e``` here!");
	output = std::string("This is <code>some cod</code>e<code></code>` here!");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("");
	output = std::string("");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("``");
	output = std::string("<code></code>");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("`");
	output = std::string("`");
	assert(ParseTextCode(input) == output);
	// TEST_END

	// TEST
	input = std::string("```");
	output = std::string("<code></code>`");
	assert(ParseTextCode(input) == output);
	// TEST_END
}
