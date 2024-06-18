#include <iostream>
#include <vector>
#include <string>

int longestCommonSubsequence(std::string text1, std::string text2) {
        std::vector<std::vector<int>> dp(text1.length(), std::vector<int>(text2.length(), 0));
        int m = text1.length();
        int n = text2.length(); 

        for(int i = 0; i < m; ++i) {
            dp[i][n - 1] = 0;
            for(int k = i; k < m; ++k) {
                if(text1[k] == text2[n - 1]) {
                    dp[i][n - 1] = 1;
                    break;
                }
            }
        }
        for(int j = 0; j < n; ++j) {
            dp[m - 1][j] = text1[m - 1] == text2[j];
            for(int k = j; k < n; ++k) {
                if(text1[m - 1] == text2[k]) {
                    dp[m - 1][j] = 1;
                    break;
                }
            }
        }

        for(int i = m - 2; i >= 0; --i) {
            for(int j = n - 2; j >= 0; --j) {
                if (text1[i] == text2[j]) {
                    dp[i][j] = dp[i + 1][j + 1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i][j + 1], dp[i + 1][j]);
                }

            }
        }
    return dp[0][0];
}


int main() {


    return 0;
}