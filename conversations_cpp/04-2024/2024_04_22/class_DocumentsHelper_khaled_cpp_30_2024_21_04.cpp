/***
 * Prompt:




 khaled_cpp_30_2024_21_04: d8023e77-9a11-4026-a2f9-e02a76c5762e





 Create a C++ class named DocumentsHelper, this class will include a method named Match. This method will accept two inputs of type Document, where Document is a type of struct that contains content member of type std::string and metadata member of type std::map<std::string, std::string> and == operator function. This method should return boolean true if both of inputs are equal. Please note that 2 Documents are equal if both of them have the same metadata and the same content. Note that 2 contents are equal if the values are equal after trim and replace all multiple spaces into one single space.


 */

#include <string>
#include <sstream>
#include <map>
#include <iostream>

std::string RemoveSpaces(std::string content) {
	std::stringstream stringstreamer;
	std::string word, parsed = "";

	stringstreamer << content;
	int idx = 0;
	while (stringstreamer >> word) {
		if (idx++) {
			word = (' ' + word);
		}

		parsed += word;
	}

	return parsed;
}

struct Document {
	std::string content;
	std::map<std::string, std::string> metadata;

	bool operator==(const Document &another_page) const {
		for (const std::pair<std::string, std::string> pair : metadata) {

			if (another_page.metadata.size() != metadata.size() || !std::equal(another_page.metadata.begin(), another_page.metadata.end(), metadata.begin())) {
				return false;
			}
		}

		return RemoveSpaces(content) == RemoveSpaces(another_page.content);
	}
};

class DocumentsHelper {
public:
	bool Match(Document &a, Document &b) {
		return a == b;
	}
};

#include <cassert>
int main() {
	DocumentsHelper documents_helper;

	// TEST
	Document input1 = Document { content: std::string("This is test  sentence.") };
	Document input2 = Document { content: std::string("This is test sentence.") };
	bool output = true;
	assert(documents_helper.Match(input1, input2) == output);
	//TEST_END

	// TEST
	input1 = Document { content: std::string("This is test  sentence.") };
	input2 = Document { content: std::string("This is testsentence.") };
	output = false;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string("") };
	input2 = Document { content: std::string("") };
	output = true;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string(" This ") };
	input2 = Document { content: std::string("this") };
	output = false;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string(" this ") };
	input2 = Document { content: std::string("this") };
	output = true;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string("test ") };
	input2 = Document { content: std::string("test") };
	output = true;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string(" test") };
	input2 = Document { content: std::string("test") };
	output = true;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("checksum", std::string("123")) } };
	input2 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("checksum", std::string("104")) } };
	output = false;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("checksum", std::string("123")), std::make_pair("title", std::string("OK")) } };
	input2 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("checksum", std::string("123")), std::make_pair("title", std::string("OK")) } };
	output = true;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { };
	input2 = Document { };
	output = true;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("checksum", std::string("123")), std::make_pair("title", std::string("OK")) } };
	input2 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("checksum", std::string("104")), std::make_pair("title", std::string("Ok")) } };
	output = false;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("title", std::string("OK")), std::make_pair("checksum", std::string("123")) } };
	input2 = Document { content: std::string("This is test sentence."), metadata: { std::make_pair("checksum", std::string("123")), std::make_pair("title", std::string("OK")) } };
	output = true;
	assert(documents_helper.Match(input1, input2) == output);
	// TEST_END
}
