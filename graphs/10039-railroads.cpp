/*
 Created by Thibault Gagnaux on 2019-03-02.

 uva 10039 - railroads

 Summary: Find the earliest arrival time at destination taking trains from home -> destination with the following
 constraints:
 1. A starting time is given. We can only take trains with departure time > starting time
 2. We only travel during 1 day so the arrival time cannot be later than 23:59
 3. Trains arriving and departing at the same time can be taken (we can change instantaneously)
 4. If there are multiple ways to arrive at the same earliest arrival time, we want to leave at the latest departure
 time.

 Solution: Constraint 4 disallows a simple SSSD-dijkstra and many thus solve this problem with dp. I am not yet quite
 clear when a shortest-path problem can be converted to a dp problem. Anyway with a very nice trick we can still use
 dijkstra:
 1. Use dijkstra to find the earliest arrival time: if not possible: print no connection
 2. Do dijkstra on the reverse graph starting from destination -> source and find the latest departure. For this we
 just reverse the graph and negative start and arrival times (This is necessary as dijkstra only works with "<"
 relaxation (remember finding the longest path is NP)).

 Implementation details: Graph representation: adjacency list of connection structs, arrays for city names and arrival
 times and map to map city names -> vertex index in adjacency list

 This solution is very elegant: fast and not much code: AC 0.020 leading to the 6th fastest runtime.
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

struct Connection {
    int to;
    int start_time;
    int arrival_time;

    Connection() = default;

    Connection(int to, int start_time, int end_time) : to{to}, start_time{start_time}, arrival_time{end_time} {};

    bool operator<(const Connection &c) const {
        return arrival_time > c.arrival_time;
    }

};

array<string, 101> cities;
map<string, int> city_to_id;
array<vector<Connection>, 101> graph;
array<vector<Connection>, 101> reverse_graph;
array<int, 101> arrival_times;

int convert_time_to_int(string time) {
    return time[3] - '0' + 10 * (time[2] - '0') + 100 * (time[1] - '0') + 1000 * (time[0] - '0');
}

string convert_time_to_string(int time) {
    if (time < 1000) return "0" + to_string(time);
    return to_string(time);
}

int dijkstra(int source, int dest, int start_time, array<vector<Connection>, 101> &graph) {
    arrival_times.fill(INF);
    arrival_times[source] = start_time;
    priority_queue<PII > pq;
    pq.push(MP(-arrival_times[source], source));
    while (!pq.empty() && pq.top().second != dest) {
        PII vertex = pq.top();
        pq.pop();
        int weight = -vertex.first;
        int u = vertex.second;
        if (weight > arrival_times[u]) continue;
        for (Connection &c : graph[u]) {
            if (c.start_time < weight) continue;
            int v = c.to;
            if (c.arrival_time < arrival_times[v]) {
                arrival_times[v] = c.arrival_time;
                pq.push(MP(-c.arrival_time, c.to));
            }
        }
    }
    return arrival_times[dest];
}


int main() {
    int s, C, T, desc;
    string depart, arrival, from, to, home, destination, start_time;
    cin >> s;
    FOR(j, 1, s) {
        cin >> C;
        printf("Scenario %d\n", j);
        FORN(i, 0, C) {
            cin >> cities[i];
            city_to_id.insert(MP(cities[i], i));
        }
        cin >> T;
        while (T--) {
            cin >> desc;
            FORN(i, 0, desc) {
                from = to;
                depart = arrival;
                cin >> arrival >> to;
                if (i != 0) {
                    Connection c = Connection(city_to_id[to], convert_time_to_int(depart),
                                              convert_time_to_int(arrival));
                    int from_id = city_to_id[from];
                    graph[from_id].PB(c);
                    reverse_graph[c.to].emplace_back(Connection(from_id, -c.arrival_time, -c.start_time));
                }
            }
        }
        cin >> start_time >> home >> destination;
        int earliest_arrival = dijkstra(city_to_id[home], city_to_id[destination], convert_time_to_int(start_time),
                                        graph);
        if (earliest_arrival == INF) {
            printf("No connection\n");
        } else {
            int latest_departure = -dijkstra(city_to_id[destination], city_to_id[home], -earliest_arrival,
                                             reverse_graph);
            string departure_time = convert_time_to_string(latest_departure);
            string arrival_time = convert_time_to_string(earliest_arrival);
            printf("Departure %s %s\nArrival   %s %s\n", departure_time.c_str(), home.c_str(), arrival_time.c_str(),
                   destination.c_str());
        }

        printf("\n");

        city_to_id.clear();
        FORN(i, 0, C) {
            graph[i].clear();
            reverse_graph[i].clear();
        }
    }
    return 0;
}