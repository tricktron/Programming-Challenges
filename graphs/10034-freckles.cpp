/*
 Created by Thibault Gagnaux on 2019-02-22.

 uva 10034 - Freckles

 The problem reduces to find the minimum spanning tree of a graph given in grid form.
 The weight between two vertices is the 2-norm distance.
 To solve the problem prim's MST algorithm with a priority queue of an edge struct is used.
 Complexity: O(n^2*logn + n^2)
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

struct Edge {
    double cost;
    int dest;

    Edge(double cost, int dest) : cost{cost}, dest{dest} {};

    bool operator<(const Edge &edge) const {
        return cost > edge.cost;
    }
};

int main() {
    //    FREOPEN;
    int t, n;
    bool visited[101];
    double x[101], y[101], dist[101][101];
    cin >> t;
    while (t--) {
        cin >> n;
        FORN(i, 0, n) {
            cin >> x[i] >> y[i];
            FORN(j, 0, i) {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                dist[i][j] = dist[j][i] = sqrt(dx * dx + dy * dy);
            }
        }

        priority_queue<Edge> queue;
        SET(visited, false);
        double sum = 0;
        int start_vertex = 0;
        FORN(i, 0, n - 1) {
            visited[start_vertex] = true;
            FORN(j, 1, n) {
                double cost = dist[start_vertex][j];
                queue.push(Edge(cost, j));
            }
            if (!queue.empty()) {
                Edge min_edge = queue.top();
                while (visited[min_edge.dest]) {
                    queue.pop();
                    min_edge = queue.top();
                }
                start_vertex = min_edge.dest;
                sum += min_edge.cost;

            }
        }
        printf("%.2f\n", sum);
        if (t > 0) {
            cout << endl;
        }
    }
    return 0;
}
