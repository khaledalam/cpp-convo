/***
 * Prompt:




 khaled_cpp_82-2024_May_08: 78f64f60-8ff9-4371-b117-076f88563943

 func_SortAndFilterStudents_khaled_cpp_82-2024_May_08

 Design me a C++ function called SortByFractionValue that takes in a vector of pairs representing fractions. Each pair consists of two integers, the numerator and denominator. The function should sort the fractions in ascending order based on their decimal values.


 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int grade;

    bool operator==(const Student &another) const {
        return name == another.name && grade == another.grade;
    }
};

std::vector<Student> SortAndFilterStudents(std::vector<Student> students) {
    if (students.empty()) {
        throw std::invalid_argument("input can't be empty");
    }
    for (const Student &student : students) {
        if (student.name.length() < 1) {
            throw std::invalid_argument("invalid student name");
        }

        if (student.grade < 0 || student.grade > 100) {
            throw std::invalid_argument("invalid student grade");
        }
    }

    std::sort(students.begin(), students.end(), [](const Student &student_1, const Student &student_2) {
        return student_1.grade > student_2.grade;
    });

    students.erase(std::unique(students.begin(), students.end()), students.end());

    return students;
}

#include <cassert>
int main() {
    // TEST
    std::vector<Student> input { { "Ali", 85 }, { "Wael", 90 }, { "Ali", 85 }, { "Charlie", 70 } };
    std::vector<Student> output { { "Wael", 90 }, { "Ali", 85 }, { "Charlie", 70 } };
    assert(SortAndFilterStudents(input) == output);
    // TEST_END

    // TEST
    input = { { "Emily", 95 }, { "David", 80 }, { "David", 80 }, { "Emily", 95 } };
    output = { { "Emily", 95 }, { "David", 80 } };
    assert(SortAndFilterStudents(input) == output);
    // TEST_END

    // TEST
    input = { { "Ahmed", 75 }, { "Ahmed", 75 }, { "Ahmed", 75 }, { "Ahmed", 75 } };
    output = { { "Ahmed", 75 } };
    assert(SortAndFilterStudents(input) == output);
    // TEST_END

    // TEST
    input = { { "Ahmed", 1 } };
    output = { { "Ahmed", 1 } };
    assert(SortAndFilterStudents(input) == output);
    // TEST_END

    // TEST
    input = { { "Ahmed", 1 }, { "Ahmed", 2 } };
    output = { { "Ahmed", 2 }, { "Ahmed", 1 } };
    assert(SortAndFilterStudents(input) == output);
    // TEST_END

    // TEST
    input = { { "Yara", 88 }, { "Maged", 92 }, { "Yara", 88 }, { "Sayed", 85 } };
    output = { { "Maged", 92 }, { "Yara", 88 }, { "Sayed", 85 } };
    assert(SortAndFilterStudents(input) == output);
    // TEST_END

    // TEST
    input = { { "Ahmed", 75 }, { "Ahmed", 75 }, { "Ahmed", 75 }, { "Ahmed", 75 } };
    output = { { "Ahmed", 75 } };
    assert(SortAndFilterStudents(input) == output);
    // TEST_END

    // TEST
    try {
        input = { };
        SortAndFilterStudents(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        input = { { "", 75 }, };
        SortAndFilterStudents(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        input = { { "Ali", -1 }, };
        SortAndFilterStudents(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        input = { { "Ali", 102 }, };
        SortAndFilterStudents(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

