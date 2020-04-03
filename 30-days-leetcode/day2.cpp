#include <string> 
#include <numeric>
#include <iostream>
#include <unordered_set>

/* 
Problem:
Check if a number is happy. A happy number is defined as follows:
Starting with any positive integer, replace the number by the sum of the squares of its digits,
and repeat the process until the number equals 1 (where it will stay),
or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy numbers.

E.g. 19
1 * 1 + 9 * 9 = 82
8 * 8 + 2 * 2 = 68
6 * 6 + 8 * 8 = 100
1 * 1 + 0 * 0 + 0 * 0 = 1

Solution: 
Code the algorithm. I tried some functional c++ using accumulate and without using any loops.
*/
using namespace std;
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> mem;
        return _isHappy(n, mem);
    }

    bool _isHappy(int n, unordered_set<int> &mem) {
        if (n == 1) return true;
        if (mem.find(n) != mem.end()) return false;
        mem.insert(n);
        return _isHappy(squareOfDigits(n), mem);
    }

    int squareOfDigits(int n) {
        string number = to_string(n);
        return accumulate(number.begin(), number.end(), 0, squareCharValue);
    }

    int static squareCharValue(int fst, char snd) {
        int y = snd - '0';
        return fst + y * y;
    }
};

int main() {
    Solution s;
    /* int n = 20; // unhappy */
    int n = 19; // happy
    if (s.isHappy(n)) {
        cout << n << " is a happy number." << endl;
    } else {
        cout << "No happy number.";
    }
}