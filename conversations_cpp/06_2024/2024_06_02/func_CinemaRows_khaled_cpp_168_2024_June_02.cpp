/***






 khaled_cpp_168_2024_June_02: 4d932be8-6aae-4da1-94ee-716bfa77cc28

func_CinemaRows_khaled_cpp_168_2024_June_02


Design me a C++ function called CinemaRows that takes two inputs of type int called row_count and person_count.

A certain cinema has row_count rows of seats, each row having 15 seats. Initially, all seats are empty. Each person
tries to choose a seat that maximizes the distance to the nearest occupied seat. If multiple seats have the same
distance, they choose the seat with the smallest row number, and if there is still a tie, they choose the leftmost seat
in that row.

person_count people are about to enter the cinema; each one will choose their seat following the aforementioned rules.

This function should return a vector of pairs of integers std::vector<std::pair<int, int>>, where each pair represents
the row and seat number (1-indexed) chosen by each person, in the order they enter. Please don't forget to validate the
inputs.



*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> CinemaRows(int row_count, int person_count) {
    if (row_count <= 0 || person_count <= 0) {
        throw std::invalid_argument("Invalid number of rows and/or people");
    }

    std::vector<std::vector<bool>> seats(row_count, std::vector<bool>(15, true));
    std::vector<std::pair<int, int>> chosen_seats;

    for (int person_idx = 0; person_idx < person_count; ++person_idx) {
        int best_row = -1, best_seat = -1, max_dist = -1;

        for (int row_idx = 0; row_idx < row_count; ++row_idx) {
            for (int seat_idx = 0; seat_idx < 15; ++seat_idx) {
                if (seats[row_idx][seat_idx]) {
                    int left_dist = 0, right_dist = 0;

                    for (int left_seat = seat_idx - 1; left_seat >= 0 && seats[row_idx][left_seat]; --left_seat)
                        left_dist++;
                    for (int right_seat = seat_idx + 1; right_seat < 15 && seats[row_idx][right_seat]; ++right_seat)
                        right_dist++;

                    int min_dist = std::min(left_dist, right_dist);
                    int max_dist_current = std::max(left_dist, right_dist);

                    if (min_dist > max_dist || (min_dist == max_dist && max_dist_current > max_dist)) {
                        max_dist = min_dist;
                        best_row = row_idx;
                        best_seat = seat_idx;
                    }
                }
            }
        }

        if (best_row == -1 || best_seat == -1) {
            throw std::runtime_error("No available seat found");
        }

        seats[best_row][best_seat] = false;
        chosen_seats.push_back({best_row + 1, best_seat + 1});
    }

    return chosen_seats;
}

#include <cassert>
int main() {
    // TEST
    assert((CinemaRows(5, 5) == std::vector<std::pair<int, int>>{{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}}));
    // TEST_END

    // TEST
    assert((CinemaRows(75, 23) == std::vector<std::pair<int, int>>{{1, 8},  {2, 8},  {3, 8},  {4, 8},  {5, 8},  {6, 8},
                                                                   {7, 8},  {8, 8},  {9, 8},  {10, 8}, {11, 8}, {12, 8},
                                                                   {13, 8}, {14, 8}, {15, 8}, {16, 8}, {17, 8}, {18, 8},
                                                                   {19, 8}, {20, 8}, {21, 8}, {22, 8}, {23, 8}}));
    // TEST_END

    // TEST
    assert((CinemaRows(3, 1) == std::vector<std::pair<int, int>>{{1, 8}}));
    // TEST_END

    // TEST
    try {
        CinemaRows(-1, 5);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CinemaRows(5, -5);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CinemaRows(5, 0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CinemaRows(2, 31);
        assert(false);
    } catch (const std::runtime_error &e) {
        assert(true);
    }
    // TEST_END
}
