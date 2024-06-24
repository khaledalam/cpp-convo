/***


 khaled_cpp_mil_219_2024_June_16: ae3ac21c-bc35-423e-9890-dba2a4d09feb

 func_BestPortfolio_khaled_cpp_mil_219_2024_June_16
 

*/

/*


Design a C++ function called BestPortfolio that takes an integer num_assets, a vector of doubles const std::vector<double> representing the expected returns of each asset, a vector of doubles const std::vector<double> representing the risks (standard deviations) of each asset, a 2D vector of doubles const std::vector<std::vector<double>> representing the correlation matrix between the assets, and a double risk_tolerance. The function should return a vector of doubles std::vector<double> representing the optimal weights of the assets in the portfolio to maximize the return while minimizing the risk according to the given risk tolerance.



*/


#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

struct Portfolio {
    double return_value;
    double risk;
    std::vector<double> weights;

    bool operator<(const Portfolio &other) const { return return_value / risk > other.return_value / other.risk; }
};

double CalculatePortfolioRisk(const std::vector<double> &weights, const std::vector<double> &risks,
                              const std::vector<std::vector<double>> &correlation_matrix) {
    double risk = 0.0;
    int num_assets = weights.size();
    for (int i = 0; i < num_assets; ++i) {
        for (int j = 0; j < num_assets; ++j) {
            risk += weights[i] * weights[j] * risks[i] * risks[j] * correlation_matrix[i][j];
        }
    }
    return std::sqrt(risk);
}

std::vector<double> BestPortfolio(int num_assets, const std::vector<double> &returns,
                                      const std::vector<double> &risks,
                                      const std::vector<std::vector<double>> &correlation_matrix,
                                      double risk_tolerance) {
    if (num_assets <= 0 || returns.size() != num_assets || risks.size() != num_assets ||
        correlation_matrix.size() != num_assets || correlation_matrix[0].size() != num_assets) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Portfolio> portfolios;
    int num_combinations = 1 << num_assets;

    for (int mask = 0; mask < num_combinations; ++mask) {
        std::vector<double> weights(num_assets, 0.0);
        double total_return = 0.0;
        double total_weight = 0.0;

        for (int i = 0; i < num_assets; ++i) {
            if (mask & (1 << i)) {
                weights[i] = 1.0 / risks[i];
                total_weight += weights[i];
                total_return += returns[i] * weights[i];
            }
        }

        for (int iii = 0; iii < num_assets; ++iii) {
            weights[iii] /= total_weight;
        }

        double portfolio_risk = CalculatePortfolioRisk(weights, risks, correlation_matrix);

        if (portfolio_risk <= risk_tolerance) {
            portfolios.push_back({total_return, portfolio_risk, weights});
        }
    }

    if (portfolios.empty()) {
        throw std::runtime_error("No valid portfolios found within the given risk tolerance");
    }

    return std::max_element(portfolios.begin(), portfolios.end())->weights;
}

#include <cassert>
int main() {
    // TEST
    int num_assets1 = 3;
    std::vector<double> returns1 = {0.1, 0.2, 0.15};
    std::vector<double> risks1 = {0.05, 0.1, 0.07};
    std::vector<std::vector<double>> correlation_matrix1 = {{1.0, 0.2, 0.4}, {0.2, 1.0, 0.5}, {0.4, 0.5, 1.0}};
    double risk_tolerance1 = 0.08;
    std::vector<double> result1 =
        BestPortfolio(num_assets1, returns1, risks1, correlation_matrix1, risk_tolerance1);
    assert(result1.size() == 3);
    assert(std::abs(result1[0] + result1[1] + result1[2] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_assets2 = 4;
    std::vector<double> returns2 = {0.12, 0.18, 0.1, 0.15};
    std::vector<double> risks2 = {0.06, 0.08, 0.05, 0.07};
    std::vector<std::vector<double>> correlation_matrix2 = {
        {1.0, 0.3, 0.2, 0.4}, {0.3, 1.0, 0.4, 0.2}, {0.2, 0.4, 1.0, 0.3}, {0.4, 0.2, 0.3, 1.0}};
    double risk_tolerance2 = 0.07;
    std::vector<double> result2 =
        BestPortfolio(num_assets2, returns2, risks2, correlation_matrix2, risk_tolerance2);
    assert(result2.size() == 4);
    assert(std::abs(result2[0] + result2[1] + result2[2] + result2[3] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_assets3 = 3;
    std::vector<double> returns3 = {0.15, 0.22, 0.18};
    std::vector<double> risks3 = {0.07, 0.09, 0.08};
    std::vector<std::vector<double>> correlation_matrix3 = {{1.0, 0.25, 0.3}, {0.25, 1.0, 0.35}, {0.3, 0.35, 1.0}};
    double risk_tolerance3 = 0.075;
    std::vector<double> result3 =
        BestPortfolio(num_assets3, returns3, risks3, correlation_matrix3, risk_tolerance3);
    assert(result3.size() == 3);
    assert(std::abs(result3[0] + result3[1] + result3[2] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_assets4 = 5;
    std::vector<double> returns4 = {0.1, 0.12, 0.15, 0.18, 0.2};
    std::vector<double> risks4 = {0.04, 0.05, 0.06, 0.07, 0.08};
    std::vector<std::vector<double>> correlation_matrix4 = {{1.0, 0.1, 0.2, 0.3, 0.4},
                                                            {0.1, 1.0, 0.2, 0.3, 0.4},
                                                            {0.2, 0.2, 1.0, 0.3, 0.4},
                                                            {0.3, 0.3, 0.3, 1.0, 0.4},
                                                            {0.4, 0.4, 0.4, 0.4, 1.0}};
    double risk_tolerance4 = 0.065;
    std::vector<double> result4 =
        BestPortfolio(num_assets4, returns4, risks4, correlation_matrix4, risk_tolerance4);
    assert(result4.size() == 5);
    assert(std::abs(result4[0] + result4[1] + result4[2] + result4[3] + result4[4] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_assets5 = 2;
    std::vector<double> returns5 = {0.1, 0.2};
    std::vector<double> risks5 = {0.05, 0.1};
    std::vector<std::vector<double>> correlation_matrix5 = {{1.0, 0.5}, {0.5, 1.0}};
    double risk_tolerance5 = 0.075;
    std::vector<double> result5 =
        BestPortfolio(num_assets5, returns5, risks5, correlation_matrix5, risk_tolerance5);
    assert(result5.size() == 2);
    assert(std::abs(result5[0] + result5[1] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    try {
        BestPortfolio(-1, {0.1}, {0.1}, {{1.0, 0.5}}, 0.075);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
