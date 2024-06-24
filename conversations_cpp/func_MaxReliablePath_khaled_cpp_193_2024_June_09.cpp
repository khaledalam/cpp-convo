/***






 khaled_cpp_193_2024_June_09: 0dd3dec4-c133-4405-b944-85a7a10463ea

func_MaxReliablePath_khaled_cpp_193_2024_June_09


Design me a C++ function called MaxReliablePath that takes an integer num_nodes, a vector of tuples const
std::vector<std::tuple<int, int, double>> representing the edges of the graph where each tuple contains two integers
(nodes) and a double (reliability), and an integer start_node and end_node. The function should return a double
representing the maximum reliability path from the start_node to the end_node. Please don't forget to validate the
inputs.

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

const double TOLERANCE = 1e-6;

bool DoubleEquals(double aaa, double bbb, double tolerance = TOLERANCE) { return std::fabs(aaa - bbb) < tolerance; }

double MaxReliablePath(int num_nodes, const std::vector<std::tuple<int, int, double>> &edges, int start_node,
                       int end_node) {
    if (num_nodes <= 0 || start_node < 0 || start_node >= num_nodes || end_node < 0 || end_node >= num_nodes) {
        throw std::invalid_argument("Invalid input");
    }

    std::vector<std::vector<double>> dpp(num_nodes, std::vector<double>(num_nodes, 0.0));
    for (const auto &edge : edges) {
        int uuu, vvv;
        double reliability;
        std::tie(uuu, vvv, reliability) = edge;
        dpp[uuu][vvv] = reliability;
        dpp[vvv][uuu] = reliability;
    }

    std::vector<double> max_reliability(num_nodes, 0.0);
    max_reliability[start_node] = 1.0;

    for (int kkk = 0; kkk < num_nodes; ++kkk) {
        for (const auto &edge : edges) {
            int uuu, vvv;
            double reliability;
            std::tie(uuu, vvv, reliability) = edge;
            if (max_reliability[uuu] * reliability > max_reliability[vvv]) {
                max_reliability[vvv] = max_reliability[uuu] * reliability;
            }
            if (max_reliability[vvv] * reliability > max_reliability[uuu]) {
                max_reliability[uuu] = max_reliability[vvv] * reliability;
            }
        }
    }

    return max_reliability[end_node];
}

#include <cassert>
int main() {
    // TEST
    int num_nodes1 = 4;
    std::vector<std::tuple<int, int, double>> edges1 = {{0, 1, 0.9}, {1, 2, 0.9}, {0, 2, 0.5}, {2, 3, 0.7}};
    int start_node1 = 0;
    int end_node1 = 3;
    double result1 = MaxReliablePath(num_nodes1, edges1, start_node1, end_node1);
    assert(DoubleEquals(result1, 0.567));
    // TEST_END

    // TEST
    int num_nodes2 = 3;
    std::vector<std::tuple<int, int, double>> edges2 = {{0, 1, 0.8}, {1, 2, 0.9}};
    int start_node2 = 0;
    int end_node2 = 2;
    double result2 = MaxReliablePath(num_nodes2, edges2, start_node2, end_node2);
    assert(DoubleEquals(result2, 0.72));
    // TEST_END

    // TEST
    int num_nodes3 = 4;
    std::vector<std::tuple<int, int, double>> edges3 = {{0, 1, 0.9}, {1, 2, 0.9}, {2, 3, 0.8}, {0, 3, 0.6}};
    int start_node3 = 0;
    int end_node3 = 3;
    double result3 = MaxReliablePath(num_nodes3, edges3, start_node3, end_node3);
    assert(DoubleEquals(result3, 0.648));
    // TEST_END

    // TEST
    int num_nodes4 = 5;
    std::vector<std::tuple<int, int, double>> edges4 = {
        {0, 1, 0.8}, {1, 2, 0.9}, {2, 3, 0.7}, {3, 4, 0.9}, {0, 4, 0.3}};
    int start_node4 = 0;
    int end_node4 = 4;
    double result4 = MaxReliablePath(num_nodes4, edges4, start_node4, end_node4);
    assert(DoubleEquals(result4, 0.4536));
    // TEST_END

    // TEST
    int num_nodes5 = 5;
    std::vector<std::tuple<int, int, double>> edges5 = {{0, 1, 0.8}, {1, 2, 0.8}, {2, 3, 0.8}, {3, 4, 0.8}};
    int start_node5 = 0;
    int end_node5 = 4;
    double result5 = MaxReliablePath(num_nodes5, edges5, start_node5, end_node5);
    assert(DoubleEquals(result5, 0.4096));
    // TEST_END

    // TEST
    try {
        MaxReliablePath(-1, {{0, 1, 0.8}}, 0, 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxReliablePath(4, {{0, 1, 0.8}}, 6, 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxReliablePath(40, {{0, 1, 0.8}}, 6, -1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
