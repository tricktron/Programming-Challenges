#include <vector>
#include <numeric>
#include <functional>
#include <iostream>

using namespace std;

/* 
Problem:
Given a non-empty array of integers, every element appears twice except for one. Find that single one.

E.g. [2,2,1] -> 1

Solution: 
- A frequency table using a hashmap and printing the number with count 1 was my first idea which is in 0(2n) with two
swipes (One for building the frequency table and one for evaluating it).

- A better solution which requires no extra space and is in 0(n) is using the xor property:
2 xor 2 = 0 &&
1 xor 0 = 1 -> That means all elements that appear twice cancel out and the single one remains.
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        return accumulate(begin(nums), end(nums), 0, bit_xor<int>());
    }
};

int main() {
    Solution s;
    vector<int> v = {1, 2, 1, 2, 3};
    cout << s.singleNumber(v);
}
