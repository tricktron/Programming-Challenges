/*
 Created by Thibault Gagnaux on 2019-03-08.

 uva 10199 - Tourist guide

 Summary: Cameras are placed strategically on a road net. They are placed at each city C that you need to pass through
 if you want to drive from A to B.

 Solution: The cameras are placed at an articulation point of a graph. An articulation point is a vertex in a graph
 that disconnects (or increases the number of connected components in a graph) the graph if removed.

 Algorithm to find articulation points:
 A vertex v is a an articulation point if:
 v is the root and has 2 or more children in the dfs spanning graph.
 u is a vertex whose subgraph v has NO edge to any ancestor of u.

 This algorithm can be implemented in O(V + E) using dfs and two special arrays:
 - the normal depth[V] array which not only tracks if a vertex is visited but at what time (depth)
 it was discovered using a counter.
 - lowest_ancestor[V] which keeps track of the lowest depth reachable.
 An articualtion point u is then defined as, for every edge from u to v:
 if lowest_ancestor[v] >= depth[u] then u is an articulation point == if !lowest_ancestor[v] < depth[u] == u is a
 vertex whose subgraph v has no edge to any ancestor of u.

 Update the arrays:
 if v is not visited:
 - lowest_ancestor[u] = min(lowest_ancestor[u], lowest_ancestor[v]) == Update all involved vertices in the cycle
 if v is visited: lowest_ancestor[u] = min(lowest_ancestor[u], depth[v]) == invariant lowest_ancestor[u] <= depth[u]
 must be fulfilled.

 Two special cases need to be taken care of:
  - the root always fulfills that condition but it is only an articulation point if it has two or more children in the
 dfs spanning tree (not in the normal graph)
 - back edges to to the same vertex do NOT count

 Caution: Run the findArticulationPoints algorithm for every unvisited vertex as the graph may not be connected.
 (Connected components may be > 1).
*/



#include <bits/stdc++.h>

using namespace std;

#define MIN(a, b) a < b ? a : b
#define UNVISITED -1
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

array<VI, 110> graph;
array<int, 110> depth;
array<int, 110> lowest_ancestor;
array<int, 110> parent;
array<string, 110> cities;
map<string, int> name_to_id;
set<string> cameras;

void findArticulationPoints(int root, int u, int count) {
    depth[u] = lowest_ancestor[u] = count++;
    int rootChildren = 0;
    for (auto v : graph[u]) {
        if (depth[v] == UNVISITED) {
            parent[v] = u;
            rootChildren++;
            findArticulationPoints(root, v, count);
            if (lowest_ancestor[v] >= depth[u]) {
                if (u != root || rootChildren > 1) cameras.insert(cities[u]);
            }
            lowest_ancestor[u] = MIN(lowest_ancestor[u], lowest_ancestor[v]);
        } else if (v != parent[u]) {
            lowest_ancestor[u] = MIN(lowest_ancestor[u], depth[v]);
        }
    }
}

int main() {
    int N, R;
    int d = 0;
    string city, from, to;
    depth.fill(UNVISITED);
    while (cin >> N && N) {
        FORN(i, 0, N) {
            cin >> city;
            name_to_id.insert(MP(city, i));
            cities[i] = city;
        }
        cin >> R;
        FORN(i, 0, R) {
            cin >> from >> to;
            int from_id = name_to_id[from];
            int to_id = name_to_id[to];
            graph[from_id].PB(to_id);
            graph[to_id].PB(from_id);
        }
        FORN(i, 0, N) {
            if (depth[i] == UNVISITED) {
                findArticulationPoints(i, i, 0);
            }
        }
        if (d) cout << "\n";
        printf("City map #%d: %lu camera(s) found\n", ++d, cameras.size());
        for (const auto &c : cameras) {
            cout << c << "\n";
        }
        FORN(i, 0, N) {
            graph[i].clear();
            depth[i] = UNVISITED;
            lowest_ancestor[i] = 0;
            parent[i] = 0;
        }
        name_to_id.clear();
        cameras.clear();
    }
    return 0;
}