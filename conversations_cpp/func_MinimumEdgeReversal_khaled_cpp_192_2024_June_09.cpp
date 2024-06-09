/***






 khaled_cpp_192_2024_June_09: 86893d5a-e339-416e-9a68-3433f4b05917

func_MinimumEdgeReversal_khaled_cpp_192_2024_June_09

Design a C++ function called MinimumEdgeReversal that takes the following inputs:

- An integer num_nodes representing the number of nodes in the graph.
- A vector of pairs of integers edges representing directed edges in the graph, where Edge is a struct contains 2 integers from_node and to_node.
- Two integers start_node and end_node representing the start and target nodes respectively.

The function should return an integer representing the minimum number of edge reversals required to reach the target node from the start node. If it's not possible to reach the target node, please make the function return -1.

*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

struct Edge {
    int from_node;
    int to_node;
};

int MinimumEdgeReversal(int num_nodes, std::vector<Edge> edges, int start_node, int end_node) {
    if (num_nodes <= 0 || start_node < 0 || start_node >= num_nodes || end_node < 0 || end_node >= num_nodes) {
        throw std::invalid_argument("Invalid input");
    }

    std::vector<std::vector<std::pair<int, int>>> graph(num_nodes);
    for (const auto &edge : edges) {
        graph[edge.from_node].emplace_back(edge.to_node, 0);
        graph[edge.to_node].emplace_back(edge.from_node, 1);
    }

    std::vector<int> distances(num_nodes, std::numeric_limits<int>::max());
    std::deque<int> node_queue;
    node_queue.push_back(start_node);
    distances[start_node] = 0;

    while (!node_queue.empty()) {
        int current_node = node_queue.front();
        node_queue.pop_front();
        for (const auto &neighbor : graph[current_node]) {
            int neighbor_node = neighbor.first;
            int edge_cost = neighbor.second;
            if (distances[current_node] + edge_cost < distances[neighbor_node]) {
                distances[neighbor_node] = distances[current_node] + edge_cost;
                if (edge_cost == 0) {
                    node_queue.push_front(neighbor_node);
                } else {
                    node_queue.push_back(neighbor_node);
                }
            }
        }
    }

    return distances[end_node] == std::numeric_limits<int>::max() ? -1 : distances[end_node];
}

#include <cassert>
int main() {
    // TEST
    std::vector<Edge> edges1 = {{0, 1}, {2, 0}, {1, 2}};
    int result1 = MinimumEdgeReversal(3, edges1, 0, 2);
    assert(result1 == 0);
    // TEST_END

    // TEST
    std::vector<Edge> edges2 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
    int result2 = MinimumEdgeReversal(4, edges2, 0, 3);
    assert(result2 == 0);
    // TEST_END

    // TEST
    std::vector<Edge> edges3 = {{0, 1}, {1, 2}, {2, 3}};
    int result3 = MinimumEdgeReversal(4, edges3, 3, 0);
    assert(result3 == 3);
    // TEST_END

    // TEST
    std::vector<Edge> edges4 = {{0, 1}, {1, 2}, {2, 3}};
    int result4 = MinimumEdgeReversal(4, edges4, 0, 3);
    assert(result4 == 0);
    // TEST_END

    // TEST
    std::vector<Edge> edges5 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    int result5 = MinimumEdgeReversal(5, edges5, 0, 4);
    assert(result5 == 0);
    // TEST_END
}
