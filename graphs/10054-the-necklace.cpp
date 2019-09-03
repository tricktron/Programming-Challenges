/*
 Created by Thibault Gagnaux on 2019-02-26.

 uva 10054 - The Necklace

 The colours are the vertices and the beads are the edges.
 Then this boils down to find the euler tour starting from any vertex.
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
#include <float.h>

using namespace std;

#define PI acos(-1)
#define MP make_pair
#define PB push_back
#define VI vector <int>
#define PII pair <int, int>
#define PIB pair<int, bool>
#define LL long long
#define SET(v, i) memset(v, i, sizeof(v))
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define FORN(i, a, b) for (int i = (a); i < (b); i++)
#define DOWN(i, b) for (int i = 0; i > (b); i--)
#define FIT(it, v) for (typeof(v.begin()) it = v.begin(); it != v.end(); it++)
#define FITD(it, v) for (typeof(v.rbegin()) it = v.rbegin(); it != v.rend(); it++)
#define FREOPEN freopen("a.in", "r", stdin); freopen("a.out", "w", stdout)

list<int> cycles = {};
vector<PIB> adj_list[51];


void eulerTour(list<int>::iterator i, int u) {
    for(PIB &v: adj_list[u]) {
        if (v.second) {
            v.second = false;
            for (PIB &bi_directional: adj_list[v.first]) {
                if (bi_directional.first == u && bi_directional.second) {
                    bi_directional.second = false;
                    break;
                }
            }
            eulerTour(cycles.insert(i, u), v.first);
        }
    }
}


int main() {
    int T, N;
    scanf("%d", &T);
    FORN(c, 0, T) {
        if (c) printf("\n");
        printf("Case #%d\n", c + 1);
        scanf("%d", &N);
        int start;
        for (vector<PIB> &neighbours : adj_list) {
            neighbours.clear();
        }
        FORN(i, 0, N) {
            int from, to;
            scanf("%d %d", &from, &to);
            adj_list[from].emplace_back(PIB(to, true));
            adj_list[to].emplace_back(PIB(from, true));
            start = from;
        }

        bool is_eulerian = true;
        for (const vector<PIB> &degree: adj_list) {
            if (degree.size() % 2 == 1) {
                printf("some beads may be lost\n");
                is_eulerian = false;
                break;
            }
        }
        if (is_eulerian) {
            cycles.clear();
            eulerTour(cycles.begin(), start);
            if (cycles.size() != N) { // graph may be disconnected
                printf("some beads may be lost\n");
            } else {
                for (auto it = next(cycles.begin()); it != cycles.end(); ++it) {
                    printf("%d %d\n", *prev(it), *it);
                }
                printf("%d %d\n", cycles.back(), cycles.front());
            }
        }
    }
    return 0;
}