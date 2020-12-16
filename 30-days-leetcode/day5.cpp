#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;
        int i = 0;
        int n = prices.size() - 1;
        if ( prices.empty()) return maxProfit;
        while (true) {
            while (i <= n - 1 && prices[i + 1] < prices[i]) i++;
            if (i == n) break;
            int localMin = prices[i++];
            while (i <= n - 1 && prices[i + 1] > prices[i]) i++;
            maxProfit += prices[i] - localMin;
            if (i++ == n) break;

        }
        return maxProfit;
    }
};

int main() {
    Solution s;
    vector<int> v = { };
    cout << s.maxProfit(v);
    return 0;
}