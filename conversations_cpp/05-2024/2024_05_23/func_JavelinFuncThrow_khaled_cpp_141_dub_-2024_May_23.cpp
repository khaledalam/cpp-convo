/***
 * Prompt:




 khaled_cpp_141_dub_-2024_May_23: 1885e655-7d22-4f6f-8b64-e6b086f27719

 func_JavelinFuncThrow_khaled_cpp_141_dub_-2024_May_23


Create a C++ function called JavelinFuncThrow that takes the initial speed (v00 in m/s) of type double and the throw angle (angle in degrees) of type double. All inputs should be greater than 0. This function should return the maximum height and maximum range reached by the javelin as std::pair<double,double>. Consider EPS = 0.6 and please don't forget to validate the inputs.
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

std::pair<double, double> JavelinFuncThrow(double v00, double angle) {
    if (v00 < 0 || angle < 0) {
        throw std::invalid_argument("All inputs should be greater than 0");
    }

    const double arr = angle * (M_PI / 180);

    const double grav = 9.81;

    double v0y = v00 * sin(arr);

    double peak_height = pow(v0y, 2) / (2 * grav);

    double ttt = 2 * v0y / grav;

    double vxx = v00 * cos(arr);

    double x_max = 0 + vxx * ttt;

    return std::pair<double, double>{peak_height, x_max};
}

#include <cassert>
int main() {
    const double EPS = 0.6;

    // TEST
    assert(JavelinFuncThrow(36.7, 45).first - 34.0 < EPS);
    // TEST_END

    // TEST
    assert(JavelinFuncThrow(36.7, 45).second - 137.0 < EPS);
    // TEST_END

    // TEST
    assert(JavelinFuncThrow(51.3, 20).first - 16.0 < EPS);
    // TEST_END

    // TEST
    assert(JavelinFuncThrow(51.3, 20).second - 172.0 < EPS);
    // TEST_END

    // TEST
    assert(JavelinFuncThrow(100.1, 89).first - 511.0 < EPS);
    // TEST_END

    // TEST
    assert(JavelinFuncThrow(100.1, 89).second - 36.0 < EPS);
    // TEST_END

    // TEST
    try {
        JavelinFuncThrow(-1, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}