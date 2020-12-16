#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/*
Try that solution with s.substring().
*/
class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int n = s.size();
        string res = s;
        int shiftCount = 0;
        for (auto const &v: shift) {
            if (v[0] == 0) shiftCount -= v[1];
            else shiftCount += v[1];
            shiftCount %= n;
        }
        if (shiftCount == 0) return res;
        else {
            for (int i = 0; i < s.size(); i++) {
                int j = (i + shiftCount + n) % n;
                res[j] = s[i];
            }
            return res;
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> v = {
      {0, 7}, {1, 7}, {1, 0}, {1, 3}, {0, 3}, {0, 6}, {1, 2}
    };
    cout << s.stringShift("wpdhhcj", v) << endl;
}