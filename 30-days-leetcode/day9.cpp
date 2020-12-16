#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1;
        int j = T.size() - 1; 
        while (i >= 0 || j >= 0) {
            int hashCountS = 0;
            while (i >= 0 && (hashCountS > 0 || S[i] == '#')) {
              if (S[i] == '#')
                hashCountS++;
              else
                hashCountS--;
              i--;
            }
            int hashCountT = 0;
            while (j >= 0 && (hashCountT > 0 || T[j] == '#')) {
              if (T[j] == '#')
                hashCountT++;
              else
                hashCountT--;
              j--;
            }

            if (i >= 0 && j >= 0) {
                if (S[i--] != T[j--]) return false;
            } else {
              if (i >= 0 || j >= 0)
                return false;
            }
        }
        return i < 0 && j < 0;
    }
};


int main() {
    Solution sol;
    string s = "a";
    string t = "b";
    if (sol.backspaceCompare(s, t)) {
        cout << "true" << endl;
    }
    else {
        cout << "false";
    }
}