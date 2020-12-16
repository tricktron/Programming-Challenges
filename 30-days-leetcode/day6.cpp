#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> m;
    for (int i = 0; i < strs.size(); i++) {
      string tmp = strs[i];
      sort(tmp.begin(), tmp.end());
      m[tmp].push_back(strs[i]);
    }
    vector<vector<string>> res;
    for (auto const &pair : m) {
      res.push_back(pair.second);
    }
    return res;
  }
};

/*   vector<vector<string>> groupAnagrams(vector<string>& strs) {
      unordered_map<string, vector<string>> m;
      vector<vector<string>> res;
      unordered_map<string, vector<string>> sorted = accumulate(strs.begin(),
strs.end(), m, sortStringLexicographically); for (auto const &pair : sorted) {
          res.push_back(pair.second);
      }
      return res;
  }

  unordered_map<string, vector<string>> static
sortStringLexicographically(unordered_map<string, vector<string>> &m, string &s)
{ string copy = s; sort(copy.begin(), copy.end()); m[copy].push_back(s); return
m;
  }
}; */

int main() {
  Solution s;
  vector<string> v = {"eat", "ate", "tea", "nat"};
  s.groupAnagrams
  (v);
  return 0;
}