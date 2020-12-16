#include <vector>
#include <iostream>

using namespace std;

/*
Problem:
Given an array nums, write a function to move all 0's to the end of it
while maintaining the relative order of the non-zero elements.

E.g. [0,1,0,3,12] -> [1,3,12,0,0]

Solution:
My first attempt resulted from just try and error on paper with two pointers i (always points
to zeros) and j (always points to Non-Zeros). If we find such a pointer pair (i,j) we swap them.
This is a bit ugly because you need to pay attention when you are at the end or edge cases with
only zeroes, no zeroes etc.

The simplest solution is implemented in _moveZeroesSimple:
Count the number of non-Zeros and directly insert them at the front. This can be implemented in
two ways:
1. Use swap (writes to a temp variable)
2. Or just overwrite and fill up with zeros starting at index nonZerosCount.

For number 2 the worst case array is [0, 0, 0, ..., 1] as all the n-1 writes are not needed.
So it depends on how many non-zero elements the array contains if either 1 or 2 is better.

Note:
While looking at the fastest c++ solution I found out that the function `remove` from stl exactly solves
that problem by removing a certain value from an iterable without changing its size (thus in-place
with undefined values) and returns an iterator to the first non-defined index.
See moveZeroesFastAndClever for this elegant solution.

*/

class Solution {
public:
    void moveZeroesFirstAttempt(vector<int>& nums) {
        int i = 0;
        while (true) {
            while (i < nums.size() && nums[i] != 0) i++;
            int j = i + 1;
            if (j > nums.size()) break;
            while (j < nums.size() && nums[j] == 0) j++;
            if (j == nums.size()) break;
            swap(nums[i], nums[j]);
        }
    }

    void _moveZeroesSimple(vector<int>& nums) {
        int nonZerosCount = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                swap(nums[nonZerosCount++], nums[i]);
            }
        }
    }

    void moveZeroesFastAndClever(vector<int>& nums) {
        auto it = remove(nums.begin(), nums.end(), 0);
        while (it != nums.end()) *it++ = 0;
    }
};

int main() {
    Solution s;
    vector<int> v = { 0, 1, 0 };
    s.moveZeroesFastAndClever(v);
    for (int i: v) {
        cout << i << " ";
    }
}