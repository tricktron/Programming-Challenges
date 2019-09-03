/*
 Created by Thibault Gagnaux on 2019-02-22.

 spoj ROADNET - Road net
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

int main() {
    int t, n;
    const int MAX_TOWNS = 200;
    cin >> t;
    while (t--) {
        cin >> n;
        int adjacency_matrix[MAX_TOWNS][MAX_TOWNS] = {};
        FORN(l, 0, n) {
            FORN(m, 0, n) {
                cin >> adjacency_matrix[l][m];
            }
        }
        FORN(i, 0, n) {
            FORN(j, i + 1, n) {
                bool is_neighbour = true;
                FORN(k, 0, n) {
                    if (k == i || k == j) continue;
                    if (adjacency_matrix[i][j] == adjacency_matrix[i][k] + adjacency_matrix[k][j]) {
                        is_neighbour = false;
                    }
                }
                if (is_neighbour) {
                    cout << i + 1 << " " << j + 1 << endl;
                }
            }
        }
    }
    return 0;
}

