#include <vector>
#include <iostream>

using namespace std;

/*
Problem:
Find the maximum 1D subarray.

Solution:
Kadanes single sweep algorithm, with two local variables keeping track of the
localMax and the globalMax.

Idea:
Inductively we know at pos j:
We either take the next int (meaning it increases the sum) or we keep the
current local max. This is equal to localMax = max(nums[i], localMax + nums[i]);

As a final step we update the globalMax if we found a new globalMax.

Another Solution would be divide and conquer which is O(nlogn). The interesting part there is that
you need to only find the maxSum in the left and right part but also the max overlappingSum:
    The maxOverlappingSum is the maxSum from the middle to the left + the maxSum from the middle + 1 to the right.

Note:
The fastest solution is interesting:
int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n==0)
            return 0;
        vector<int> dp(nums);
        int res = nums[0];
        for(int i=1; i<n; ++i){
            dp[i] = max(nums[i], nums[i]+dp[i-1]);
            res = max(res, dp[i]);
        }
        return res;
    }
};

It uses a separate growing vector as dp-list. My assumption is that the lookup
is faster as the vector is very small in the beginning:

*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int globalMax = nums[0];
        int localMax = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            localMax = max(nums[i], localMax + nums[i]);
            globalMax = max(globalMax, localMax);
            
            // faster because of less function calls but less readable in my opinion
/*             int localSum = localMax + nums[i];
            localMax = localSum > nums[i] ? localSum : nums[i];
            if (localMax > globalMax) {
                globalMax = localMax;
            } */
        }
        return globalMax;
    }

    int maxSubArrayDivideAndConquer(vector<int> const &nums, int l, int r) {
        if (l == r) {
            return nums[l];
        }
        int m = (l + r) / 2;
        int leftSum = 0;
        int maxLeftSum = INT_MIN;
        for (int i = m; i >= l; i--) {
            leftSum += nums[i];
            maxLeftSum = max(leftSum, maxLeftSum);
        }

        int rightSum = 0;
        int maxRightSum = INT_MIN;
        for (int i = m + 1; i <= r; i++) {
            rightSum += nums[i];
            maxRightSum = max(rightSum, maxRightSum);
        }

        int maxOverlappingSum = maxLeftSum + maxRightSum;
        return max(maxOverlappingSum, 
            max(maxSubArrayDivideAndConquer(nums, l, m), maxSubArrayDivideAndConquer(nums, m + 1, r)));
    }
};

int main() {
    Solution s;
    vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4 };
    cout << s.maxSubArray(v) << endl;
    cout << s.maxSubArrayDivideAndConquer(v, 0, v.size()) << endl;
}