/*
 Created by Thibault Gagnaux on 2019-02-22.

 spoj DIVSUM - Divisor Summation
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <vector>
#include <queue>
#include <deque>
#include <ctype.h>

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
#define FIT(it, v) for (typeof(v.begin()) it = v.begin(); it != v.end(); it++)
#define FITD(it, v) for (typeof(v.rbegin()) it = v.rbegin(); it != v.rend(); it++)
#define FREOPEN freopen("a.in", "r", stdin); freopen("a.out", "w", stdout)

LL int divisor_sum(int n) {
    LL int sum = 0;
    FOR(i, 2, sqrt(n)) {
        if (n % i == 0) {
            if (i == (n / i)) sum += i;
            else sum += (i + n / i);
        }
    }
    return sum + 1;
}

int main() {
    int test_count, n;
    cin >> test_count;
    FORN(i, 0, test_count) {
        cin >> n;
        if (n == 1) cout << 0 << endl;
        else cout << divisor_sum(n) << endl;
    }
}



