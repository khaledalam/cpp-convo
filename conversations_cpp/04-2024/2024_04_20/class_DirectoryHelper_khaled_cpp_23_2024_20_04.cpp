/***
 * Prompt:




 khaled_cpp_23_2024_20_04: 89ea0261-bd6c-4a34-bb7a-8591ce933a27



 class_DirectoryHelper_khaled_cpp_23_2024_20_04




 Design me a C++ class named DirectoryHelper, this class will include a function called PrefixFileSearcher. The function accepts two inputs called search_text of type std:string that represents the file prefix name that we want to search for and files_paths input of type std::vector<std::string> which represents a list of files paths. This function should returns another list of files paths that its file start with prefix of search_text. Please not that file path should contains slash "/" and empty string or "*" means match all files. Don't forget to validate inputs.


 */

#include <string>
#include <vector>

class DirectoryHelper {
public:
	std::vector<std::string> PrefixFileSearcher(std::string search_text, std::vector<std::string> files_paths) {
		std::vector<std::string> prefixes;

		if (search_text == "" || search_text == "*") {
			return files_paths;
		}

		for (const std::string file_path : files_paths) {

			auto pos = file_path.find_last_of('/');

			if (pos != std::string::npos) {
				std::string file_name = file_path.substr(pos + 1);

				if (file_name.rfind(search_text, 0) == 0) {
					prefixes.push_back(file_path);
				}
			} else {
				throw std::invalid_argument("Invalid input");
			}
		}

		return prefixes;
	}
};

#include <cassert>
int main() {
	DirectoryHelper directory_helper;

	// TEST
	std::string input1 = std::string("test");
	std::vector<std::string> input2 = { std::string("c://folder1/test.php"), std::string("c://folder1/test.cpp"), std::string("c://folder1/test_a.c") };
	std::vector<std::string> output = { std::string("c://folder1/test.php"), std::string("c://folder1/test.cpp"), std::string("c://folder1/test_a.c") };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("te");
	input2 = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp"), std::string("c://folder1/btest_a.c") };
	output = { std::string("home/folder1/test.php"), };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("a");
	input2 = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp"), std::string("c://folder1/btest_a.c") };
	output = { std::string("c://folder1/atest.cpp"), };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("");
	input2 = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp") };
	output = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp") };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("");
	input2 = { };
	output = { };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("*");
	input2 = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp") };
	output = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp") };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("+");
	input2 = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp") };
	output = { };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("home");
	input2 = { std::string("home/folder1/test.php"), std::string("c://folder1/atest.cpp") };
	output = { };
	assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("a");
	input2 = { std::string("folder1|test.php"), std::string("c://folder1/atest.cpp"), std::string("c://folder1/btest_a.c") };
	output = { std::string("c://folder1/atest.php"), };
	try {
		assert(directory_helper.PrefixFileSearcher(input1, input2) == output);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}
