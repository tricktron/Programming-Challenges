/*
 Created by Thibault Gagnaux on 2019-06-25.

 uva 10092 - The problem with the problem setter

 Summary: Given m categories and n problems where each problem n_i may belong to
 to multiple categories m_i and each category m_i needs at least j problems to find a
 possible allocation.

 Solution: This boils down to a maximum bipartite matching (MBM) problem.
 An MBM problem can be solved in multiple ways:
 1. Convert it to a Max flow problem by adding source and target and then the max flow equals the max matching
 2. Find augmenting alternating paths to get the maximum matching

 I converted it to a max flow problem by modelling it the following way:
 Build up the bipartite graph: 1. Connect each category m_i with the problem n_i with capacity 1 if the problem
                                  belongs to that category.
                               2. Add a back edge with capacity for each edge in 1 in opposite direction
 Add source and target: Connect source with every category using capacity j (how many problems need to be
                        in the category), and every problem with the sink with capacity 1.
       m_1 -1- n_1
    j/                \1
  s -j- m_2 -1- n_2 -1- t                t
 ...   important: back edges between m and n

 A maximum flow problem can be solved with Ford Fulkerson:
 0. max_flow = 0
 1. while there exist augmenting paths:
      2. Find bottleneck == min possible flow on path (s, t)
      3. Reduce capacity on forward edges by bottleneck
      4. Increase capacity on back edges by bottleneck (important for correctness)
      5.max_flow += bottleneck
 return max_flow

 Lastly if max_flow == sum of needed problems for all categories print 1 and the allocation else print 0

 Important insights during this exercise:

 The run time of a graph (V, E) ford fulkerson depends on step 1:
  If we find augmenting paths by dfs the runtime is O(|f|* E) where |f| is the max flow value
  If we find augmenting paths by bfs the runtime is O(V * E^2) also knows as Edmonds-Karp

 Often network flow problems have test cases where |f| is very large and thus you always need to use
 edmonds-karp. But in this problem |f| can only become 100 and therefore dfs is faster (by around 0.02s)

 Enumerating the neighbours of a vertex in O(k = nunber of neighbours) and finding the back edge of an edge in O(1)
 can be achieved using two variants:
 1. An adjacency list for the neighbours and a separate 2d residual array[MAX_VERTICES][MAX_VERTICES] to save
 capacities. --> see 10092_the_problem_with_the_problem_setter_dfs.cpp
 2. Using only one adjacency list with a struct with three ints. The back_index lets us find the back edge in
 the graph efficiently otherwise enumerating the neighbours takes O(Max_edges). It works the following way:
 back_index of forward edge (u, v) = graph[v].size()
 back_index of backwards edge (u, v) = graph[v].size() - 1 // important!
 This approach presented two challenges:
  - Insertion order matters: we first have to insert the forward edge and then directly the back edge (the back_index
      of (u,v) is assigned during inserting the forward edges)
  - The back_edge of a back_edge is graph[v].size() - 1 because again the forward edge was inserted before

 This solution here uses variant 2 with only one edge adjacency list and it is 0.01 faster as we save a 2D array with
 1 million entries that we need to clear after each example.

 Total runtime of this solution (0.01s).

 Possible future improvements but not implemented to get the runtime to (0.0s):
 - Using dinic's algorithm which is O(V^2*E) but may perform very well for the test set
 - Using approach 2 to find the maximum matching using Hopcroft-Karp algorithm which is O(sqrt(V) * E) and looks very
 promising but then I would have missed out on all the findings from maximum flow.

 Common errors on the way to the solution:
  - Always validate if we have modelled the problem correctly. For a long time I modelled the
    problem: source -> problem -> category -> target which is wrong. In a matching on the left side is always the set
    that can be in multiple sets on the right side: A category can have multiple problems but a problem can only
    belong to one category in a matching!
 - No back edges to source and no back edges from target!
 - The maximum flow may be correct without without having modelled the back edges correctly because in all the udebug
 examples no back edges are needed. That is why it is important to understand the back edges.
*/

#include <vector>
#include <cstdio>
#include <stack>
#include <numeric>

#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FORN(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define eb emplace_back
#define VI vector<int>
#define MAX_VERTICES 1024
#define INF 10000000
#define MAX_EDGES 24

using namespace std;

struct Edge {
    int to; // the (v in the (u,v) edge)
    int capacity;
    int back_index; // to quickly find the back edge

    Edge() : to(-1), capacity(0), back_index(-1) {}

    Edge(int to, int capacity, int back_index) :
            to(to), capacity(capacity), back_index(back_index) {}
};

vector<Edge> graph[MAX_VERTICES];
pair<int, int> path[MAX_VERTICES];


bool dfs(int source, int target) {
    stack<int> stack;
    stack.push(source);
    FORN(i, 0, MAX_VERTICES) path[i] = make_pair(-1, -1);
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        if (u == target) return true;
        FORN(j, 0, graph[u].size()) {
            Edge v = graph[u][j];
            if (v.capacity > 0 && path[v.to].first == -1) {
                stack.push(v.to);
                path[v.to] = make_pair(u, j);
            }
        }
    }
    return false;
}

int fordFulkerson(int source, int target) {
    int max_flow = 0;
    while (dfs(source, target)) {
        int path_flow = INF;
        for (int i = target; i != source; i = path[i].first) {
            int u = path[i].first;
            int v = path[i].second;
            if (graph[u][v].capacity < path_flow) path_flow = graph[u][v].capacity;
        }

        for (int i = target; i != source; i = path[i].first) {
            int u = path[i].first;
            int v = path[i].second;
            int back_index = graph[u][v].back_index;
            graph[u][v].capacity -= path_flow;
            if (u == source || i == target) continue;
            graph[i][back_index].capacity += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    int categoryCount, problemCount;
    VI categories(MAX_EDGES);
    while (scanf("%d %d", &categoryCount, &problemCount) == 2) {
        if (categoryCount == 0 && problemCount == 0) break;
        int target = categoryCount + problemCount + 1;

        FOR(i, 1, categoryCount) {
            int capacity;
            scanf("%d", &capacity);
            categories.pb(capacity);
            graph[0].eb(Edge(i, capacity, graph[i].size()));
        }
        FOR(i, categoryCount + 1, target - 1) {
            graph[i].eb(Edge(target, 1, graph[target].size()));
            int edgeCount;
            scanf("%d", &edgeCount);
            FORN(j, 0, edgeCount) {
                int to;
                scanf("%d", &to);
                graph[to].eb(Edge(i, 1, graph[i].size()));
                graph[i].eb(Edge(to, 0, graph[to].size() - 1));
            }
        }
        int max_flow = fordFulkerson(0, target);
        if (max_flow == accumulate(begin(categories), end(categories), 0)) {
            printf("1\n");
            FOR(i, 1, categoryCount) {
                int match = 0;
                for (const auto &e : graph[i]) {
                    if (e.capacity == 0) {
                        match++;
                        if (match > 1) printf(" %d", e.to - categoryCount);
                        else printf("%d", e.to - categoryCount);
                        if (match == categories[i - 1]) break;
                    }
                }
                printf("\n");
            }
        } else {
            printf("0\n");
        }

        FOR(i, 0, target) {
            graph[i].clear();
        }
        categories.clear();
    }
    return 0;
}