/***


 khaled_cpp_mil_223_2024_June_16: 26d98291-f51f-4cea-8afc-4c2ff64c81d1

 func_SeatingTheater_khaled_cpp_mil_223_2024_June_16
 



*/

/*


Write me a C++ function called SeatingTheater that takes two inputs of type int called rows and people.

A certain theater has rows rows of seats, each row having 10 seats. Initially, all seats are empty. The theater has a
rule for seating people: Each person tries to choose a seat that maximizes the distance to the nearest occupied seat. If
multiple seats have the same distance, they choose the seat with the smallest row number, and if there is still a tie,
they choose the leftmost seat in that row.

people people are about to enter the theater; each one will choose their seat following the aforementioned rules.

This function should return a vector of pairs of integers std::vector<std::pair<int, int>>, where each pair represents
the row and seat number (1-indexed) chosen by each person, in the order they enter.



*/


#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::pair<int, int>> SeatingTheater(int rows, int people) {
    if (rows <= 0) {
        throw std::invalid_argument("Invalid number of rows");
    }

    if (people <= 0) {
        throw std::invalid_argument("Invalid number of people");
    }

    std::vector<std::vector<bool>> seats(rows, std::vector<bool>(10, true));
    std::vector<std::pair<int, int>> chosen_seats;

    for (int ppp = 0; ppp < people; ++ppp) {
        int best_row = -1, best_seat = -1, max_dist = -1;

        for (int rrr = 0; rrr < rows; ++rrr) {
            for (int sss = 0; sss < 10; ++sss) {
                if (seats[rrr][sss]) {
                    int left_dist = 0, right_dist = 0;

                    for (int lss = sss - 1; lss >= 0 && seats[rrr][lss]; --lss)
                        left_dist++;
                    for (int rss = sss + 1; rss < 10 && seats[rrr][rss]; ++rss)
                        right_dist++;

                    int min_dist = std::min(left_dist, right_dist);
                    int max_dist_current = std::max(left_dist, right_dist);

                    if (min_dist > max_dist ||
                        (min_dist == max_dist && max_dist_current > std::max(left_dist, right_dist))) {
                        max_dist = min_dist;
                        best_row = rrr;
                        best_seat = sss;
                    }
                }
            }
        }

        if (best_row == -1 || best_seat == -1) {
            throw std::invalid_argument("No available seat found");
        }

        seats[best_row][best_seat] = false;
        chosen_seats.push_back({best_row + 1, best_seat + 1});
    }

    return chosen_seats;
}

#include <cassert>
int main() {
    // TEST
    assert((SeatingTheater(5, 5) == std::vector<std::pair<int, int>>{{1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}}));
    // TEST_END

    // TEST
    assert((SeatingTheater(4, 2) == std::vector<std::pair<int, int>>{{1, 5}, {2, 5}}));
    // TEST_END

    // TEST
    assert((SeatingTheater(1, 2) == std::vector<std::pair<int, int>>{{1, 5}, {1, 8}}));
    // TEST_END

    // TEST
    try {
        SeatingTheater(-1, 5);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SeatingTheater(5, -5);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SeatingTheater(5, 0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SeatingTheater(2, 21);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
