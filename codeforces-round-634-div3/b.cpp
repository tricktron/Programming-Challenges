#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, a, b;
        cin >> n >> a >> b;
        if (b == 1) cout << string(n, 'a') << endl;
        else {
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            string s(n, 'a');
            for (int j = 0; j < n; j++) {
                int k = j % b;
                s[j] = alphabet[k];
            }
            cout << s << endl;
        }
    }
    return 0;
}
