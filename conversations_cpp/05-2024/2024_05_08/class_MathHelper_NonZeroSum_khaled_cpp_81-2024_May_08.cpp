/***
 * Prompt:




 khaled_cpp_81-2024_May_08: 9409a806-3071-44fd-91e1-9482fa577b0f


 class_MathHelper_NonZeroSum_khaled_cpp_81-2024_May_08


 Design a C++ class called MathHelper. This class contains a method member called NonZeroSum which accepts two inputs called first_number and second_number both of them of type int which can accept negative, zero, or positive numbers. This method should return another number of type int which represents the sum of the two inputs. Please note that we should remove zeros from both inputs if their initial values are not zero, then sum the two numbers, and then remove zeros from the sum if the sum is not zero. So for example, if the inputs are 107 and 30 the method should return 2 since it will be 17+3=20 then we remove zero from 20 to be 2. If the inputs' values are zeros or the sum is zero then the method should return zero.


 */

#include <stdexcept>

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

class MathHelper {
public:
    int NonZeroSum(int first_number, int second_number) {
        int sum = 0;

        std::stringstream stringstreamer;
        std::string number_1, number_2, number_sum;
        stringstreamer << first_number;
        stringstreamer >> number_1;
        if (number_1 != "0") {
            number_1.erase(std::remove(number_1.begin(), number_1.end(), '0'), number_1.end());
        }
        first_number = stoi(number_1);
        stringstreamer.clear();

        stringstreamer << second_number;
        stringstreamer >> number_2;
        if (number_2 != "0") {
            number_2.erase(std::remove(number_2.begin(), number_2.end(), '0'), number_2.end());
        }
        second_number = stoi(number_2);

        sum = first_number + second_number;

        stringstreamer.clear();
        stringstreamer << sum;
        stringstreamer >> number_sum;

        if (number_sum == "0") {
            return 0;
        }

        number_sum.erase(std::remove(number_sum.begin(), number_sum.end(), '0'), number_sum.end());

        return stoi(number_sum);
    }
};

#include <cassert>
int main() {
    MathHelper math_helper;

    // TEST
    assert(math_helper.NonZeroSum(10, 20) == 3);
    // TEST_END

    // TEST
    assert(math_helper.NonZeroSum(101, 9) == 2);
    // TEST_END

    // TEST
    assert(math_helper.NonZeroSum(-10, 5) == 4);
    // TEST_END

    // TEST
    assert(math_helper.NonZeroSum(0, 5) == 5);
    // TEST_END

    // TEST
    assert(math_helper.NonZeroSum(0, 0) == 0);
    // TEST_END

    // TEST
    assert(math_helper.NonZeroSum(-1, 1) == 0);
    // TEST_END

    // TEST
    assert(math_helper.NonZeroSum(10, 5) == 6);
    // TEST_END

    // TEST
    assert(math_helper.NonZeroSum(-1010, -30) == -14);
    // TEST_END
}

