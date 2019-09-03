//
// Created by Thibault Gagnaux on 2019-07-03.
//
#include <iostream>
#include <vector>
#include <queue>
#define FORN(i,a,b) for (int i = (a); i < (b); i++)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define pb push_back
#define eb emplace_back
#define MAX_VERTICES 110

using namespace std;

struct Edge {
    int to;
    double weight;

    Edge(int to, double weight) : to(to), weight(weight) {};
};


vector<Edge> graph[MAX_VERTICES];

double bfs(int target) {
    double dist[MAX_VERTICES] = {};
    bool visited[MAX_VERTICES] = {};
    queue<int> pq;
    dist[1] = 1.0;
    visited[1] = true;
    pq.push(1);
    while (!pq.empty()) {
        int u = pq.front();
        visited[u] = false;
        pq.pop();
        for (const Edge &neighbours: graph[u]) {
            int v = neighbours.to;
            double probability = dist[u] * neighbours.weight;
            if (probability > dist[v]) {
                dist[v] = probability;
                if (!visited[v]) {
                    pq.push(v);
                    visited[v] = true;
                }
            }
        }
    }
    return dist[target];
}

int main() {
    int n, m;
    while (true) {
        cin >> n;
        if (n == 0) break;
        cin >> m;
        FOR(i, 0, 100) graph[i].clear();
        FORN(i, 0, m) {
            int from, to, percentage;
            cin >> from >> to >> percentage;
            double probability = (double) percentage / 100.0;
            graph[from].eb(Edge(to, probability));
            graph[to].eb(Edge(from, probability));
        }
        double max_probability = bfs(n);
        printf("%.6f percent\n", max_probability * 100.0);
    }
    return 0;
}
