#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    int rowCount;
    int colCount;
    vector<vector<char>> matrix;

public:
    int numIslands(vector<vector<char>>& grid) {
        rowCount = grid.size();
        colCount = grid[0].size();
        matrix = grid;
        int islandCount = 0;
        for (int row = 0; row < rowCount; row++) {
            for (int col = 0; col < colCount; col++) {
                if (matrix[row][col] == '1') {
                    dfs(row, col);
                    islandCount++;
                }
            }
        }
        return islandCount;
    }
    
    void dfs(int row, int col) {
        if (row < 0 || row >= rowCount || col < 0 || col >= colCount || matrix[row][col] == 'v' || matrix[row][col] == '0') return;
        matrix[row][col] = 'v';
        for (auto dir: directions) {
            dfs(row + dir.first, col + dir.second);
        }
    }
};

int main() {
    Solution s;
    vector<vector<char>> v = {{'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}};
    cout << s.numIslands(v);
    return 0;
}

