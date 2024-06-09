/***






 khaled_cpp_191_2024_June_09: 15582cb2-4c38-4ba6-a8ae-b79b16c5778e

func_ConstructPhylogeneticTree_khaled_cpp_191_2024_June_09



Design a C++ function called ConstructPhylogeneticTree that takes a 2D array distances of type std::vector<std::vector<double>> representing the genetic distance between different species. The array is symmetric, and the diagonal elements are zero (distance to itself is zero). The function should use the Neighbor-Joining (NJ) algorithm to construct a phylogenetic tree and return the tree structure as a std::vector<std::tuple<int, int, double>> representing the edges of the tree, where each tuple is (species1, species2, distance).


*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::tuple<int, int, double>> ConstructPhylogeneticTree(std::vector<std::vector<double>> distances) {
    int n_size = distances.size();

    if (n_size < 2) {
        throw std::invalid_argument("There must be at least two species.");
    }

    for (const auto &row : distances) {
        if (row.size() != n_size) {
            throw std::invalid_argument("The distance matrix must be square.");
        }
    }

    std::vector<int> active(n_size);
    for (int idx = 0; idx < n_size; ++idx) {
        active[idx] = idx;
    }

    auto MinIndex = [](const std::vector<std::vector<double>> &mtx, const std::vector<int> &actives) {
        double min_val = std::numeric_limits<double>::max();
        std::tuple<int, int> min_idx(-1, -1);
        for (int idx : actives) {
            for (int jdx : actives) {
                if (idx != jdx && mtx[idx][jdx] < min_val) {
                    min_val = mtx[idx][jdx];
                    min_idx = std::make_tuple(idx, jdx);
                }
            }
        }
        return min_idx;
    };

    std::vector<std::tuple<int, int, double>> tree_edges;
    while (active.size() > 2) {
        auto [iii, jjj] = MinIndex(distances, active);

        double total_dist = 0.0;
        for (int kkk : active) {
            total_dist += distances[iii][kkk] + distances[jjj][kkk];
        }

        double total_active = active.size() - 2.0;
        double dij = distances[iii][jjj];
        double dik = 0.5 * (dij + (total_dist - 2 * dij) / total_active);
        double djk = 0.5 * (dij + (total_dist - 2 * dij) / total_active);

        tree_edges.push_back(std::make_tuple(iii, jjj, dij));

        for (int kkk : active) {
            if (kkk != iii && kkk != jjj) {
                distances[iii][kkk] = distances[kkk][iii] = 0.5 * (distances[iii][kkk] + distances[jjj][kkk] - dij);
            }
        }

        active.erase(std::remove(active.begin(), active.end(), jjj), active.end());
    }

    auto [last_i, last_j] = std::make_tuple(active[0], active[1]);
    tree_edges.push_back(std::make_tuple(last_i, last_j, distances[last_i][last_j]));

    return tree_edges;
}

#include <cassert>
int main() {
    // TEST
    std::vector<std::vector<double>> distances = {{0.0, 5.0, 9.0, 9.0, 8.0},
                                                  {5.0, 0.0, 10.0, 10.0, 9.0},
                                                  {9.0, 10.0, 0.0, 8.0, 7.0},
                                                  {9.0, 10.0, 8.0, 0.0, 3.0},
                                                  {8.0, 9.0, 7.0, 3.0, 0.0}};
    auto tree = ConstructPhylogeneticTree(distances);
    assert(std::get<0>(tree[0]) == 3);
    assert(std::get<1>(tree[0]) == 4);
    assert(std::get<2>(tree[0]) == 3);

    assert(std::get<0>(tree[1]) == 0);
    assert(std::get<1>(tree[1]) == 1);
    assert(std::get<2>(tree[1]) == 5);
    // TEST_END

    // TEST
    try {
        ConstructPhylogeneticTree({{0.0}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ConstructPhylogeneticTree({{0.0, 1.0}, {1.0, 0.0}, {1.0, 0.0}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
