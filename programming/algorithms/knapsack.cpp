#include <iostream>
#include <vector>


double knapsack(std::vector<double> values, 
                std::vector<int> weights, 
                int weight_capacity) {
    const int n = values.size();
    std::vector<std::vector<double>> dp(n, std::vector<double>(weight_capacity + 1, 0));


    for(int i = 0; i <= weight_capacity; ++i) {
        dp[n - 1][i] = weights[n - 1] <= i ? values[n - 1] : 0;  
    }

    int left = 0;
    double value = 0; 



    for(int i = n - 2; i >= 0; --i) {
        for(int j = 0; j <= weight_capacity; ++j) {
            value = 0;

            left = j - weights[i];
            if(left >= 0) {
                value += values[i] + dp[i + 1][left]; 
            }
            dp[i][j] = value > dp[i + 1][j] ? value : dp[i + 1][j];
        }
    }

    return dp[0][weight_capacity];
}

// Helper function to print test results
void printTestResult(int testCaseNumber, double result, double expected) {
    std::cout << "Test Case " << testCaseNumber << ": ";
    if (result == expected) {
        std::cout << "Passed" << std::endl;
    } else {
        std::cout << "Failed (Expected " << expected << ", got " << result << ")" << std::endl;
    }
}



int main() {
    std::cout << "here\n";
// Test Case 1: Basic Functionality
{
    std::vector<double> values = {10.0, 20.0, 30.0};
    std::vector<int> weights = {1, 2, 3};
    int weight_capacity = 5;
    double expected = 50.0;  // Example expected value, needs correct calculation
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(1, result, expected);
}

// Test Case 2: Exact Fit
{
    std::vector<double> values = {10.0, 40.0, 50.0};
    std::vector<int> weights = {2, 4, 6};
    int weight_capacity = 6;
    double expected = 50.0;
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(2, result, expected);
}

// Test Case 3: Large Numbers
{
    std::vector<double> values = {1000.0, 2000.0, 3000.0, 4000.0};
    std::vector<int> weights = {100, 200, 300, 400};
    int weight_capacity = 500;
    double expected = 5000.0;
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(3, result, expected);
}

// Test Case 4: Zero Capacity
{
    std::vector<double> values = {5.0, 10.0, 15.0};
    std::vector<int> weights = {1, 2, 3};
    int weight_capacity = 0;
    double expected = 0.0;
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(4, result, expected);
}

// Test Case 5: Single Item Too Heavy
{
    std::vector<double> values = {10.0, 20.0, 30.0};
    std::vector<int> weights = {10, 20, 30};
    int weight_capacity = 5;
    double expected = 0.0;
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(5, result, expected);
}

// Test Case 6: All Items Fit
{
    std::vector<double> values = {10.0, 20.0, 30.0};
    std::vector<int> weights = {1, 2, 3};
    int weight_capacity = 10;
    double expected = 60.0;
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(6, result, expected);
}

// Test Case 7: Optimal Subset
{
    std::vector<double> values = {15.0, 10.0, 45.0, 30.0};
    std::vector<int> weights = {2, 2, 6, 5};
    int weight_capacity = 8;
    double expected = 60.0;  // Example expected value, needs correct calculation
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(7, result, expected);
}

// Test Case 8: Floating Point Precision
{
    std::vector<double> values = {0.5, 0.75, 1.25, 1.5};
    std::vector<int> weights = {1, 1, 2, 2};
    int weight_capacity = 3;
    double expected = 2.25;  // Example expected value, needs correct calculation
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(8, result, expected);
}

// Test Case 9: Duplicate Weights and Values
{
    std::vector<double> values = {10.0, 10.0, 20.0, 20.0};
    std::vector<int> weights = {2, 2, 4, 4};
    int weight_capacity = 6;
    double expected = 30.0;  // Example expected value, needs correct calculation
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(9, result, expected);
}

// Test Case 10: Non-Sorted Input
{
    std::vector<double> values = {25.0, 10.0, 35.0, 15.0};
    std::vector<int> weights = {5, 2, 6, 3};
    int weight_capacity = 8;
    double expected = 45.0;  // Example expected value, needs correct calculation
    double result = knapsack(values, weights, weight_capacity);
    printTestResult(10, result, expected);
}

    return 0;
}