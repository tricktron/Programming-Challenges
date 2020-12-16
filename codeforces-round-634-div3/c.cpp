#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        unordered_set<int> s;
        int freq[2 * 100000 + 1] = {};
        int maxSame = 0;
        int n;
        cin >> n;
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            s.insert(a);
            freq[a]++;
            maxSame = max(maxSame, freq[a]);
        }
        if (n == 1) cout << 0 << endl;
        else {
            int distinctCount = s.size();
            if (distinctCount == maxSame) cout << distinctCount - 1 << endl;
            else cout << min(distinctCount, maxSame) << endl;
        }
    }
    return 0;
}
