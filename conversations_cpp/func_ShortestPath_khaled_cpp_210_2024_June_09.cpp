/***


 khaled_cpp_210_2024_June_09: 7bb5f483-53bb-4c92-989e-cacccdeadde6

 func_ShortestPath_khaled_cpp_210_2024_June_09


*/

/*

Design a C++ function called ShortestPath that takes an integer num_nodes, a vector of tuples const std::vector<std::tuple<int, int, int>> representing the edges of the graph where each tuple contains two integers (nodes) and an integer (weight), and two integers source_node and target_node. The function should return an integer representing the shortest path from the source_node to the target_node using Dijkstra's Algorithm. Please don't forget to validate the inputs.


*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

int ShortestPath(int num_nodes, const std::vector<std::tuple<int, int, int>> &edges, int source_node, int target_node) {
    if (num_nodes <= 0 || source_node < 0 || source_node >= num_nodes || target_node < 0 || target_node >= num_nodes) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<std::vector<std::pair<int, int>>> graph(num_nodes);
    for (const auto &edge : edges) {
        int uuu, vvv, weight;
        std::tie(uuu, vvv, weight) = edge;
        if (uuu < 0 || uuu >= num_nodes || vvv < 0 || vvv >= num_nodes || weight < 0) {
            throw std::invalid_argument("Invalid edge values");
        }
        graph[uuu].push_back({vvv, weight});
        graph[vvv].push_back({uuu, weight});
    }

    std::vector<int> distances(num_nodes, std::numeric_limits<int>::max());
    distances[source_node] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pqq;
    pqq.push({0, source_node});

    while (!pqq.empty()) {
        int distance = pqq.top().first;
        int node = pqq.top().second;
        pqq.pop();

        if (distance > distances[node]) {
            continue;
        }

        for (const auto &neighbor : graph[node]) {
            int next_node = neighbor.first;
            int edge_weight = neighbor.second;
            if (distances[node] + edge_weight < distances[next_node]) {
                distances[next_node] = distances[node] + edge_weight;
                pqq.push({distances[next_node], next_node});
            }
        }
    }

    return distances[target_node];
}

#include <cassert>
int main() {
    // TEST
    int num_nodes1 = 5;
    std::vector<std::tuple<int, int, int>> edges1 = {{0, 1, 10}, {0, 4, 3}, {1, 4, 4}, {1, 2, 2},
                                                     {4, 2, 8},  {4, 3, 2}, {2, 3, 7}};
    int source_node1 = 0;
    int target_node1 = 2;
    int result1 = ShortestPath(num_nodes1, edges1, source_node1, target_node1);
    assert(result1 == 9);
    // TEST_END

    // TEST
    int num_nodes2 = 6;
    std::vector<std::tuple<int, int, int>> edges2 = {{0, 1, 7}, {0, 2, 9},  {0, 5, 14}, {1, 2, 10}, {1, 3, 15},
                                                     {2, 5, 2}, {2, 3, 11}, {3, 4, 6},  {4, 5, 9}};
    int source_node2 = 0;
    int target_node2 = 4;
    int result2 = ShortestPath(num_nodes2, edges2, source_node2, target_node2);
    assert(result2 == 20);
    // TEST_END

    // TEST
    try {
        ShortestPath(-1, edges1, source_node1, target_node1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ShortestPath(num_nodes1, {{0, 1, -1}}, source_node1, target_node1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ShortestPath(num_nodes1, edges1, -1, target_node1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
