#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp = grid;
        
        // init first row, only reachable by right

        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        // init first col, only reachable from above
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        // dp[row][col] = grid[row][col] + min(dp[row-1][col], dp[row][col-1]), == min(fromAbove, Right)
        for (int row = 1; row < m; row++) {
            for (int col = 1; col < n; col++) {
                dp[row][col] = grid[row][col] + min(dp[row-1][col], dp[row][col-1]);
            }
        }
        return dp[m-1][n-1];
    }
};


int main() {
    Solution s;
    vector<vector<int>> v = {{1,3,1},{1,5,1},{4,2,1}};
    cout << s.minPathSum(v) << endl;
    return 0;
}
