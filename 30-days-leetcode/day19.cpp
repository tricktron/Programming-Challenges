#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
         int n = nums.size();
        int l = 0;
        int r = n - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] > nums[r]) l = mid + 1;
            else r = mid;
        }
        if (nums[l] == target) return l;
        vector<int>::iterator it;
        if (l == 0) {
            it = lower_bound(nums.begin() + 1, nums.end(), target);
        } else if (l == n - 1) {
            it = lower_bound(nums.begin(), nums.end() - 1, target);
        } else {
            if (target < nums[l]) {
                it = lower_bound(nums.begin(), nums.begin() + l - 1, target);
            } else {
                it = lower_bound(nums.begin() + l + 1, nums.end(), target);
            }
        }
        auto it1 = nums.end();
        return (it == nums.end() || *it != target) ? -1 : distance(nums.begin(), it);
    }   
};

int main() {
    Solution s;
    vector<int> v = {1, 3};
    int target = 0;
    cout << s.search(v, 0) << endl;
    return 0;
}