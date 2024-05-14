/***
 * Prompt:




 khaled_cpp_99-2024_May_12: 100f64e3-bb90-47ef-a622-12bd96043195


func_QuizHandler_khaled_cpp_99-2024_May_12

 Design a C++ function called QuizHandler which accepts two inputs, first input non-empty list called questions of type std::vector<Question> where Question is a struct that contains a non-empty string member of type std::string called text and a number member of type int called answer_index which its value should be greater than zero, second input called answers_indexes of type std::vector<int> which represent the indexes of the user answers. This function should return a Boolean true if the user's answers are correct otherwise return false. Please don't forget to validate the inputs.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Question {
    std::string text;
    int answer_index;
};

bool QuizHandler(std::vector<Question> questions, std::vector<int> answers_indexes) {
    if (questions.empty()) {
        throw std::invalid_argument("questions can't be empty");
    }

    if (answers_indexes.empty()) {
        throw std::invalid_argument("answers_indexes can't be empty");
    }

    if (questions.size() != answers_indexes.size()) {
        throw std::invalid_argument("questions and answers_indexes should be with the same size");
    }

    int idx = 0;
    for (const Question &question : questions) {
        if (question.text.empty()) {
            throw std::invalid_argument("question text can't be empty");
        }

        if (question.answer_index < 1) {
            throw std::invalid_argument("question answer_index can't be less than 1");
        }

        if (question.answer_index != answers_indexes[idx++]) {
            return false;
        }
    }

    return true;
}

#include <cassert>
int main() {
    // TEST
    assert((QuizHandler({{"are you ok?", 1}}, {1}) == true));
    // TEST_END

    // TEST
    assert((QuizHandler({{"fasf &$@ a1?", 2}}, {1}) == false));
    // TEST_END

    // TEST
    assert((QuizHandler({{"?", 2}}, {2}) == true));
    // TEST_END

    // TEST
    assert((QuizHandler({{"are you ok?", 2}, {"where is paper?", 1}}, {2, 1}) == true));
    // TEST_END

    // TEST
    assert((QuizHandler({{"are you ok?", 2}, {"where is paper?", 2}}, {2, 1}) == false));
    // TEST_END

    // TEST
    try {
        QuizHandler({{"", 2}, {"where is paper?", 2}}, {2, 1});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        QuizHandler({{"where is paper?", 0}}, {1});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        QuizHandler({{"where is paper?", 1}}, {1, 2});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
