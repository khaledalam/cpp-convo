/***
 * Prompt:




 khaled_cpp_40_2024_24_04: 696ee23f-0d5d-42e1-9f21-017c1589a041


 class_Alarm_khaled_cpp_40_2024_24_04

 Design a C++ class called Alarm which contain a method named BatchTurnOff, it accepts two inputs. First input called alarms of type std::vector<std::pair<Time24, bool>>, which first argument of each pair is Time24, Time24 is a struct type which represents time in 24 hours format, Time24 contains hour and minutes members both of them of type int and second argument of the pair refers to if the alarm is turned on or off. Second input called now_in_24h of type Time24 which represents the current time. The method should return a list of type std::vector<Time24> with the alarms that are turned on and its time value greater than the given current time. Please don't forget to validate the inputs.



 */

#include <stdexcept>
#include <vector>
#include <iostream>

struct Time24 {
    int hour;
    int minutes;

    bool operator<(const Time24 another_time24) const {
        if (hour != another_time24.hour) {
            return hour < another_time24.hour;
        }

        return minutes < another_time24.minutes;
    }

    bool operator==(const Time24 another_time24) const {
        return hour == another_time24.hour && minutes == another_time24.minutes;
    }

    bool IsValid() const {
        return minutes >= 0 && minutes <= 59 && hour >= 0 && hour <= 11;
    }
};

class Alarm {
public:
    std::vector<Time24> BatchTurnOff(std::vector<std::pair<Time24, bool>> alarms, Time24 now_in_24h) {

        std::vector<Time24> result;

        if (!now_in_24h.IsValid()) {
            throw std::invalid_argument("Invalid now_in_24h formats");
        }

        for (const std::pair<Time24, bool> &alarm : alarms) {
            if (!alarm.first.IsValid()) {
                throw std::invalid_argument("Invalid alarm formats");
            }

            if (alarm.second && !(alarm.first < now_in_24h)) {
                result.push_back(alarm.first);
            }
        }

        return result;
    }
};

#include <cassert>
int main(int argc, const char *argv[]) {
    Alarm alarm;

    // TEST
    assert((alarm.BatchTurnOff( { std::make_pair(Time24 { hour: 1, minutes: 30 }, true), std::make_pair(Time24 { hour: 2, minutes: 30 }, true) }, Time24 { hour: 2, minutes: 0 }) == std::vector<Time24> { Time24 { hour: 2, minutes: 30 } }));
    // TEST_END

    // TEST
    assert((alarm.BatchTurnOff( { }, Time24 { hour: 2, minutes: 0 }) == std::vector<Time24> { }));
    // TEST_END

    // TEST
    assert((alarm.BatchTurnOff( { std::make_pair(Time24 { hour: 1, minutes: 30 }, true), std::make_pair(Time24 { hour: 2, minutes: 30 }, true) }, Time24 { hour: 1, minutes: 0 }) == std::vector<Time24> { Time24 { hour: 1, minutes: 30 }, Time24 { hour: 2, minutes: 30 } }));
    // TEST_END

    // TEST
    assert((alarm.BatchTurnOff( { std::make_pair(Time24 { hour: 1, minutes: 30 }, true), std::make_pair(Time24 { hour: 2, minutes: 30 }, true) }, Time24 { hour: 2, minutes: 30 }) == std::vector<Time24> { Time24 { hour: 2, minutes: 30 } }));
    // TEST_END

    // TEST
    assert((alarm.BatchTurnOff( { std::make_pair(Time24 { hour: 1, minutes: 30 }, true), std::make_pair(Time24 { hour: 2, minutes: 30 }, true) }, Time24 { hour: 2, minutes: 31 }) == std::vector<Time24> { }));
    // TEST_END

    // TEST
    try {
        alarm.BatchTurnOff( { std::make_pair(Time24 { hour: 1, minutes: 69 }, true) }, Time24 { hour: 2, minutes: 31 });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        alarm.BatchTurnOff( { std::make_pair(Time24 { hour: 24, minutes: 1 }, true) }, Time24 { hour: 2, minutes: 31 });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        alarm.BatchTurnOff( { std::make_pair(Time24 { hour: 1, minutes: 05 }, true) }, Time24 { hour: 42, minutes: 31 });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

