/*
Created by Thibault Gagnaux on 24.09.19.

 Codeforces Round 588 - B. Ania and Minimizing

 Adhoc - Just go through the number digit by digit and change each to 0 except the first digit (needs to be one) until
 you have done k changes.

 Difficulty: Pay attention to edge cases like if n == 1 and k == 0 return the same number else 0. Additionally, just
 return the number again if n > 1 and k == 0.
*/
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define PI acos(-1)
#define MP make_pair
#define PB push_back
#define VI vector <int>
#define PII pair <int, int>
#define LL long long
#define SET(v, i) memset(v, i, sizeof(v))
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define FORN(i, a, b) for (int i = (a); i < (b); i++)
#define DOWN(i, b) for (int i = 0; i > (b); i--)
#define FIT(it, v) for (typeof(v.begin()) it = v.begin(); it != v.end(); ++it)
#define FITD(it, v) for (typeof(v.rbegin()) it = v.rbegin(); it != v.rend(); it++)
#define INF 1000000000
#define FREOPEN freopen("a.in", "r", stdin); freopen("a.out", "w", stdout)

int main() {
    string s;
    int n, k;
    int mod = 0;
    cin >> n >> k >> s;
    if (n == 1) {
        if (k == 0) {
            cout << s << endl;
        }
        else {
            cout << 0 << endl;
        }
    } else {
        if (k == 0) {
            cout << s;
        } else {
            if ((s[0] - '0' != 1)) {
                s[0] = '1';
                mod++;
            }
            FORN(i, 1, n) {
                if (mod == k) break;
                if ((s[i] - '0' != 0)) {
                    s[i] = '0';
                    mod++;
                }
            }
            cout << s << endl;
        }
    }
    return 0;
}