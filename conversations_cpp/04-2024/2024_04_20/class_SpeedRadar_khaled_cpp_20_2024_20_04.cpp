/***
 * Prompt:




 khaled_cpp_20_2024_20_04: db67ae20-67e1-46be-8bb5-15df28d49f34


 class_SpeedRadar_khaled_cpp_20_2024_20_04





 Create a C++ class named SpeedRadar, this class will include two methods named ShouldApproveCar and CanMockApprovedLogs, each of them accepts two inputs of type std::vector<MotorLog> and int. MotorLog is a struct that contains int member called speed_measure and char member called action, action should be uppercase or lowercase of "I" or "D", "I" means increase and "D" means decrease. First input in ShouldApproveCar method called motor_logs and it represents list of motor logs and second input called max_allowed_limit which represents the allowed maximum speed. ShouldApproveCar method should return type of boolean true if the sum of speed_measure sequence in the logs not exceeded the max_allowed_limit otherwise returns false. First input in CanMockApprovedLogs method called valid_motor_logs and it represents a valid list of motor logs and second input called max_allowed_limit which represents the allowed maximum speed. The CanMockApprovedLogs method should returns type of boolean true if we can sort valid_motor_logs in a way that the sum of speed_measure sequence in the valid sorted logs list not exceeded max_allowed_limit otherwise return false. Please note that car speed can't be negative, speed_measure are zero or positive. Don't forget to validate inputs.


 */

#include <string>
#include <vector>

struct MotorLog {
	int speed_measure;
	char action;
};

class SpeedRadar {
public:
	bool ShouldApproveCar(std::vector<MotorLog> motor_logs, int max_allowed_limit) {
		int speed_so_far = 0;

		for (const MotorLog &log : motor_logs) {
			if (log.speed_measure < 0) {
				throw std::invalid_argument("Invalid input");
			}

			if (std::toupper(log.action) == 'I') {
				speed_so_far += log.speed_measure;
			} else if (std::toupper(log.action) == 'D') {
				speed_so_far = std::max(0, speed_so_far - log.speed_measure);
			} else {
				throw std::invalid_argument("Invalid input");
			}

			if (speed_so_far > max_allowed_limit) {
				return false;
			}
		}

		return true;
	}

	bool CanMockApprovedLogs(std::vector<MotorLog> valid_motor_logs, int max_allowed_limit) {
		std::vector<MotorLog> positive, negative;
		int speed_so_far = 0;

		for (const MotorLog &log : valid_motor_logs) {
			if (std::toupper(log.action) == 'I') {
				positive.push_back(log);
			} else if (std::toupper(log.action) == 'D') {
				negative.push_back(log);
			}
		}

		MotorLog max_motor_log = *std::max_element(positive.begin(), positive.end(), [](const MotorLog &a, const MotorLog &b) {
			return (a.speed_measure < b.speed_measure);
		});

		if (max_motor_log.speed_measure > max_allowed_limit) {
			return false;
		}

		sort(negative.begin(), negative.end(), [](const MotorLog &a, const MotorLog &b) {
			return (a.speed_measure < b.speed_measure);
		});

		for (const MotorLog &log : positive) {
			speed_so_far += log.speed_measure;

			while (speed_so_far > max_allowed_limit && negative.size()) {

				speed_so_far = std::max(0, speed_so_far - negative[0].speed_measure);

				negative.erase(negative.begin());
			}

			if (speed_so_far > max_allowed_limit && !negative.size()) {
				return false;
			}

		}

		return speed_so_far <= max_allowed_limit;
	}
};

#include <cassert>
int main() {
	SpeedRadar speed_radar;

	// TEST
	std::vector<MotorLog> input1 = { MotorLog { speed_measure: 10, action: 'I' }, MotorLog { speed_measure: 30, action: 'I' } };
	int input2 = 50;
	bool output1 = true;
	bool output2 = true;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END

	// TEST
	input1 = { MotorLog { speed_measure: 20, action: 'i' }, MotorLog { speed_measure: 30, action: 'I' } };
	input2 = 50;
	output1 = true;
	output2 = true;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END

	// TEST
	input1 = { MotorLog { speed_measure: 21, action: 'I' }, MotorLog { speed_measure: 30, action: 'I' } };
	input2 = 50;
	output1 = false;
	output2 = false;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END

	// TEST
	input1 = { MotorLog { speed_measure: 30, action: 'D' }, MotorLog { speed_measure: 30, action: 'I' }, MotorLog { speed_measure: 10, action: 'I' } };
	input2 = 30;
	output1 = false;
	output2 = true;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END

	// TEST
	input1 = { MotorLog { speed_measure: 10, action: 'D' }, MotorLog { speed_measure: 30, action: 'I' } };
	input2 = 50;
	output1 = true;
	output2 = true;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END

	// TEST
	input1 = { MotorLog { speed_measure: 10, action: 'D' }, MotorLog { speed_measure: 51, action: 'I' } };
	input2 = 50;
	output1 = false;
	output2 = true;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END

	// TEST
	input1 = { MotorLog { speed_measure: 0, action: 'I' }, MotorLog { speed_measure: 1, action: 'd' } };
	input2 = 0;
	output1 = true;
	output2 = true;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END

// TEST
	input1 = { MotorLog { speed_measure: 10, action: 'G' } };
	input2 = 20;
	output1 = false;
	output2 = true;
	try {
		assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
		assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = { MotorLog { speed_measure: -1, action: 'D' } };
	input2 = 20;
	output1 = false;
	output2 = true;
	try {
		assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
		assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = { };
	input2 = 50;
	output1 = true;
	output2 = true;
	assert(speed_radar.ShouldApproveCar(input1, input2) == output1);
	assert(speed_radar.CanMockApprovedLogs(input1, input2) == output2);
	// TEST_END
}
