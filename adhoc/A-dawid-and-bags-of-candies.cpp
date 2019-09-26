/*
Created by Thibault Gagnaux on 23.09.19.

 Codeforces Round 588 - A. Dawid and Bags of Candies

 Adhoc - Just try all possibilites. Don't forget that you can also divide the bags in a 3:1 relation.

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
    int a1, a2, a3, a4;
    VI bags;
    cin >> a1 >> a2 >> a3 >> a4;
    int sum = a1 + a2 + a3 + a4;
    if (sum % 2 != 0) {
        cout << "NO" << endl;
    } else {
        int average = sum / 2;
        if (a1 + a2 == average || a1 + a3 == average || a1 + a4 == average) {
            cout << "YES" << endl;
        } else if (a1 == average || a2 == average || a3 == average || a4 == average) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}