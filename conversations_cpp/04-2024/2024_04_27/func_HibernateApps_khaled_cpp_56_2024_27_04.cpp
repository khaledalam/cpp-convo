/***
 * Prompt:


 khaled_cpp_57_2024_28_04


 khaled_cpp_56_2024_27_04: eecd20ee-fd04-4157-9b1b-492187eaf489

 func_HibernateApps_khaled_cpp_56_2024_27_04

 Design a C++ function called HibernateApps, it will accept two inputs. First input called usage_report of type std::vector<std::pair<std::string, int>> which contains a non-empty list of pairs each pair of them represent app usage name as first argument and timestamp as second argument. Second input called old_count which represent how many apps with oldest timestamps in the list we want to collect. This function should return another list of oldest used apps of type std::vector<std::pair<std::string, int>>. Please use lambda function in the solution and make sure that list is not empty and old_count less than or equal to size of the given list.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::pair<std::string, int>> HibernateApps(std::vector<std::pair<std::string, int>> usage_report, int old_count) {

	if (usage_report.empty() || usage_report.size() < old_count) {
		throw std::invalid_argument(std::string("Invalid input"));
	}

	sort(usage_report.begin(), usage_report.end(), [](const std::pair<std::string, int> &usage_a, const std::pair<std::string, int> &usage_b) {
		return usage_a.second < usage_b.second;
	});

	std::vector<std::pair<std::string, int>> result;

	std::vector<std::pair<std::string, int>>::iterator vec_iterator = usage_report.begin();

	while (result.size() < old_count) {
		result.push_back(*vec_iterator);

		vec_iterator++;
	}

	return result;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(
			(HibernateApps(std::vector<std::pair<std::string, int>> { std::make_pair<std::string, int>(std::string("facebook"), 123), std::make_pair<std::string, int>(std::string("instagram"), 456) }, 1)
					== std::vector<std::pair<std::string, int>> { std::make_pair<std::string, int>(std::string("facebook"), 123) }));
	// TEST_END

	// TEST
	assert(
			(HibernateApps(std::vector<std::pair<std::string, int>> { std::make_pair<std::string, int>(std::string("facebook"), 123), std::make_pair<std::string, int>(std::string("instagram"), 456), std::make_pair<std::string, int>(std::string("instagram"), 12) }, 1)
					== std::vector<std::pair<std::string, int>> { std::make_pair<std::string, int>(std::string("instagram"), 12) }));
	// TEST_END

	// TEST
	try {
		HibernateApps(std::vector<std::pair<std::string, int>> { }, 1);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == std::string("Invalid input"));
	}
	// TEST_END

	// TEST
	try {
		HibernateApps(std::vector<std::pair<std::string, int>> { std::make_pair<std::string, int>(std::string("facebook"), 1) }, 2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == std::string("Invalid input"));
	}
	// TEST_END
}
