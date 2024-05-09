/***
 * Prompt:




 khaled_cpp_41_2024_24_04: bb715863-7aa6-45b0-a2cd-a4d108f32d24

 class_WirelessFirmware_khaled_cpp_41_2024_24_04

 Design a C++ class called WirelessFirmware which contains a function called SignalDistributor, it accepts two inputs. First input called devices of type std::vector<Device>, by the way Device is a struct type that contains ID member of type short and signal member of type boolean, signal member refers to if the device is in a linked position or not. Second input called link of type Device which represents the device that we want to link with. Please note that when we link some device we should unlink other devices by switching other devices signal value to false and keep only the linked device signal with true. Note also that if the device that we want to perform the linking on doesn't exist in the devices list then we should add it to the devices list then performing the linking process. The method should return another list of type std::vector<Device> after we perform the linking process on the list. Last note that 2 Devices are the same if their IDs are the same not necessary their signals value to be the same.



 */

#include <stdexcept>

#include <vector>
#include <iostream>
#include <algorithm>

struct Device {
	short ID;
	bool signal;

	bool operator ==(const Device &another) const {
		return ID == another.ID;
	}
};

class WirelessFirmware {
public:
	std::vector<Device> SignalDistributor(std::vector<Device> devices, Device link) {

		if (std::find(devices.begin(), devices.end(), link) == devices.end()) {
			devices.push_back(link);
		}

		std::vector<Device>::iterator it = devices.begin();

		while (it != devices.end()) {
			it->signal = (it->ID == link.ID);

			it++;
		}

		return devices;
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	WirelessFirmware wireless_firmware;

	// TEST
	assert((wireless_firmware.SignalDistributor( { Device { ID: 123, signal: false } }, Device { ID: 123 }) == std::vector<Device> { Device { ID: 123, signal: true } }));
	// TEST_END

// TEST
	assert((wireless_firmware.SignalDistributor( { }, Device { ID: 123 }) == std::vector<Device> { Device { ID: 123, signal: true } }));
	// TEST_END

	// TEST
	assert((wireless_firmware.SignalDistributor( { Device { ID: 123, signal: true } }, Device { ID: 123 }) == std::vector<Device> { Device { ID: 123, signal: true } }));
	// TEST_END

	// TEST
	assert((wireless_firmware.SignalDistributor( { Device { ID: 12, signal: false } }, Device { ID: 123 }) == std::vector<Device> { Device { ID: 12, signal: false }, Device { ID: 123, signal: true } }));
	// TEST_END

	// TEST
	assert((wireless_firmware.SignalDistributor( { Device { ID: 123, signal: true }, Device { ID: 12, signal: true }, Device { ID: 13, signal: true }, Device { ID: -14, signal: false } }, Device { ID: 123 }) == std::vector<Device> { Device { ID: 123, signal: true }, Device { ID: 12, signal: true },
	        Device { ID: 13, signal: false }, Device { ID: -14, signal: false } }));
	// TEST_END

	// TEST
	assert((wireless_firmware.SignalDistributor( { Device { ID: 123, signal: true }, Device { ID: 12, signal: true } }, Device { ID: 123 }) == std::vector<Device> { Device { ID: 123, signal: true }, Device { ID: 12, signal: false } }));
	// TEST_END

	// TEST
	assert((wireless_firmware.SignalDistributor( { Device { ID: 123, signal: false }, Device { ID: 12, signal: true } }, Device { ID: 123 }) == std::vector<Device> { Device { ID: 123, signal: true }, Device { ID: 12, signal: false } }));
	// TEST_END
}

