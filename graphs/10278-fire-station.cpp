/*
 Created by Thibault Gagnaux on 2019-03-04.

 uva 10278 - Fire Station

 Summary: Where to place a new fire station so that the maximum distance from any intersection to any fire station is
 minimized.
 Solution:
 1. This boils down to a dijkstra with multiple sources. Convert the multiple sources to a SSSP-dijkstra by
    introducing a new virtual node 0 which is connected with weight 0 to every fire station.
 2. First run dijkstra once if there are existing fire stations
 3. For every intersection i which doesn't already have a fire stations:
    a) place a fire station
    b) connect virtual node 0 to fire station with weight 0
    c) run dijkstra starting from virtual source 0
    d) record max distance
 4. Find minimum of all recorded max distances and print the intersection index where the fire station is placed
 Implementation details: The graph is represented using adjacency list: The intersections are the vertices in the
 graph and the edges are represented by an edge struct. Note how getline(cin, line) and stringstream is used to read
 an unknown number of lines until blank line or EOF.
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
#include <sstream>
#include <array>

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

struct Edge {
    int to;
    int weight;

    Edge() = default;

    Edge(int to, int weight) : to{to}, weight{weight} {};

    bool operator<(const Edge &n) const {
        return weight > n.weight;
    }
};

array<int, 501> dist;
array<vector<Edge>, 501> graph;
array<bool, 501> has_fire_station;

void print_graph(int max_vertex) {
    FOR(i, 0, max_vertex) {
        vector<Edge> edges = graph[i];
        for (const Edge &edge: edges) {
            printf("(%d,%d): %d\n", i, edge.to, edge.weight);
        }
    }
}

int dijkstra(int start) {
    dist.fill(INF);
    priority_queue<Edge> pq;
    dist[0] = 0;
    graph[0].emplace_back(Edge(start, 0));
    pq.push(Edge(0, 0));
    int max_distance = 0;
    while (!pq.empty()) {
        Edge node = pq.top();
        int u = node.to;
        int weight = node.weight;
        pq.pop();
        if (weight > dist[u]) continue;
        if (weight > max_distance) {
            max_distance = weight;
        }
        for (const Edge &neighbours: graph[u]) {
            int v = neighbours.to;
            int uv_weight = neighbours.weight;
            if (dist[u] + uv_weight < dist[v]) {
                dist[v] = dist[u] + uv_weight;
                pq.push(Edge(v, dist[v]));
            }
        }
    }
    graph[0].pop_back();
    return max_distance;
}

int main() {
    int t, f, intersections, fire_station, from, to, weight;
//    string line;
    char line[505];
    cin >> t;
    while (t--) {
        cin >> f >> intersections;
        FORN(i, 0, f) {
            cin >> fire_station;
            graph[0].emplace_back(Edge(fire_station, 0));
            has_fire_station[fire_station] = true;
        }
//        getline(cin, line);
        gets(line);
//        while (getline(cin, line) && !line.empty()) {
            while(gets(line) && line[0]) {
//            stringstream ss(line);
//            ss >> from >> to >> weight;
            sscanf(line, "%d %d %d", &from, &to, &weight);
            graph[from].emplace_back(Edge(to, weight));
            graph[to].emplace_back(Edge(from, weight));
        }

        int min_distance = f ? dijkstra(0) : INF;
        int min_index = 1;
        FOR(i, 1, intersections) {
            if (has_fire_station[i]) continue;
            int max_distance = dijkstra(i);
            if (max_distance < min_distance) {
                min_distance = max_distance;
                min_index = i;
            }
        }
        cout << min_index << endl;
        if (t) {
            cout << endl;
        }
        FOR(i, 0, intersections) {
            graph[i].clear();
            has_fire_station[i] = false;
        }
    }
    return 0;
}