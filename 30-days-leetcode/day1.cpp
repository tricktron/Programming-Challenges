#include <vector>
#include <numeric>
#include <functional>
#include <iostream>

using namespace std;

class Solution {
public:
    int static singleNumber(vector<int>& nums) {
        return reduce(begin(nums), end(nums), 0, bit_xor<int>());
    }
};

int main() {
    vector<int> v = {1, 2, 1, 2, 3};
    cout << Solution::singleNumber(v);
}
