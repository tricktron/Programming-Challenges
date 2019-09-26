/*
Created by Thibault Gagnaux on 24.09.19.

 Codeforces Round 588 - C. Anadi and Domino

 Adhoc/Brute force/graph - After try and error you realize that if n == 6 the result is always m.
 If n == 7 you need to find the two vertices which have the least common neighbours. I just try all pairs of vertices.

 Difficulty: Getting the right idea on how to solve the n = 7 case.

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
    VI graph[10] = {};
    int degrees[10] = {};
    int n, m, from, to;
    cin >> n >> m;
    FORN(i, 0, m) {
        cin >> from >> to;
        graph[from].PB(to);
        graph[to].PB(from);
        degrees[from]++;
        degrees[to]++;
    }

    if (n <= 6) {
        cout << m << endl;
    } else {
        if (m == 0) {
            cout << 0 << endl;
            return 0;
        }

        int minSharedVerticesCount = INF;
        FOR(i, 1, 7) {

            FOR(j, i + 1, 7) {
                int sharedVerticesCount = 0;
                bool visited[10] = {};
                for (auto v : graph[i]) {
                    visited[v] = true;
                }
                for (auto v : graph[j]) {
                    if (visited[v]) sharedVerticesCount++;
                }
                if (sharedVerticesCount < minSharedVerticesCount) {
                    minSharedVerticesCount = sharedVerticesCount;
                }
            }
        }
        cout << m - minSharedVerticesCount << endl;
    }
    return 0;
}

