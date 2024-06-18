#include <iostream>
#include <vector>


std::vector<int> LISS(std::vector<int>& nums) {
        if(nums.size() == 0) {
            return std::vector<int>();
        }

        std::vector<int> parents(nums.size());
        std::vector<int> dp(nums.size());
        
        parents[nums.size() - 1] = nums.size() - 1;
        dp[nums.size() - 1] = 1;

        int max = 1;
        int winner = nums.size() - 1;

        for(int i = nums.size() - 2; i >= 0; --i) {
            int max_comp = 0;
            int parent = i;
            for(int j = i + 1; j < nums.size(); ++j) {
                
                if(nums[i] < nums[j] && dp[j] > max_comp) {
                    max_comp = dp[j];
                    parent = j;
                }
            }
            dp[i] = max_comp + 1;
            parents[i] = parent;

            if(max < dp[i]) {
                max = dp[i];
                winner = i;

            }
        }
        int iter = winner;
        std::vector<int> solution;

        while(parents[iter] != iter) {
            solution.push_back(nums[iter]);
            iter = parents[iter];
        } 
        solution.push_back(nums[iter]);

        return solution;
}


int main() {
    std::vector<std::vector<int>> test_cases = {
        {}, // Test Case 1
        {10}, // Test Case 2
        {1, 2, 3, 4, 5}, // Test Case 3
        {5, 4, 3, 2, 1}, // Test Case 4
        {10, 22, 9, 33, 21, 50, 41, 60, 80}, // Test Case 5
        {7, 7, 7, 7, 7}, // Test Case 6
        {3, 10, 2, 1, 20} // Test Case 7
    };


    for(auto elem: test_cases) {
        auto temp = LISS(elem);
        for(int e: temp) {
            std::cout << e << " ";
        }  
        std::cout << "; length:" <<  temp.size();
        std::cout << std::endl;
    }

}