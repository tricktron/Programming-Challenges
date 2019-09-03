/*
 Created by Thibault Gagnaux on 2019-02-25.

  uva 10034 - Freckles

 The problem reduces to find the minimum spanning tree of a graph given in grid form.
 The weight between two vertices is the 2-norm distance.
 To solve the problem Kruskal's MST algorithm with a priority queue of edgeList data structure and a
 union find data structure is used.
 As a stopping criteria either disjointsSetsCount == 1 or edgesCount = vertices - 1 can be used
 Summa summarum: Kruskal is faster but Prim is much easier to implement as no UnionFind data structure needs to be
 memorized, although the edge list data structure is quite neat
 Complexity: O(n^2*logn + n), so a little bit faster than with prim's algorithm
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
#define LL long long
#define SET(v, i) memset(v, i, sizeof(v))
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define FORN(i, a, b) for (int i = (a); i < (b); i++)
#define DOWN(i, b) for (int i = 0; i > (b); i--)
#define FIT(it, v) for (typeof(v.begin()) it = v.begin(); it != v.end(); it++)
#define FITD(it, v) for (typeof(v.rbegin()) it = v.rbegin(); it != v.rend(); it++)
#define FREOPEN freopen("a.in", "r", stdin); freopen("a.out", "w", stdout)

class UnionFind {
private:
    VI parent, rank, setSize;
    int setsCount;
public:
    explicit UnionFind(int n) {
        rank.assign(n, 0);
        parent.assign(n, 0);
        setSize.assign(n, 1);
        setsCount = n;
        FORN(i, 0, n) parent[i] = i;
    }

    int findSet(int i) {
        return parent[i] == i ? i : (parent[i] = findSet(parent[i]));
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            setsCount--;
            int x = findSet(i);
            int y = findSet(j);
            if (rank[x] > rank[y]) {
                parent[y] = x;
                setSize[x] += setSize[y];
            } else {
                parent[x] = y;
                setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }
    int disjointSetsCount() {
        return setsCount;
    }

    int sizeOfSet(int i) {
        return setSize[findSet(i)];
    }
};

int main() {
    int t, n;
    double x[101], y[101];
    cin >> t;
    while (t--) {
        priority_queue<pair<double, PII>> edge_list;
        cin >> n;
        FORN(i, 0, n) {
            cin >> x[i] >> y[i];
            FORN(j, 0, i) {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                double dist = sqrt(dx * dx + dy * dy);
                edge_list.push(MP(-dist, MP(i, j)));
            }
        }
        double mst_cost = 0;
//        int edge_count = 0; if used replace in while loop: uf.disjointSetsCount() > 1 with edge_count < n - 1
        UnionFind uf(n);
        while (!edge_list.empty() && uf.disjointSetsCount() > 1) {
            pair<double, PII > min_edge = edge_list.top();
            edge_list.pop();
            if (!uf.isSameSet(min_edge.second.first, min_edge.second.second)) {
//                edge_count++;
                mst_cost += -min_edge.first;
                uf.unionSet(min_edge.second.first, min_edge.second.second);
            }
        }
        printf("%.2f\n", mst_cost);
        if (t > 0) {
            cout << endl;
        }
    }
    return 0;
}