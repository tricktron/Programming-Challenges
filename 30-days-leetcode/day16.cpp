#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> brackets;
        stack<int> jokers;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(') brackets.push(i);
            else if (c == '*') jokers.push(i);
            else {
                if (brackets.empty() && jokers.empty()) return false;
                else if (!brackets.empty()) {
                    brackets.pop();
                } else {
                    jokers.pop();
                }
            }
        }
        while (!brackets.empty() && !jokers.empty()) {
            if (brackets.top() > jokers.top()) return false;
            brackets.pop();
            jokers.pop();
        }
        return brackets.empty();
    }
};

int main() {
    Solution s;
    string test = "(())((())()()(*)(*()(())())())()()((()())((()))(*";
    if (s.checkValidString(test)) cout << "true";
    else cout << "false";
    return 0;
}