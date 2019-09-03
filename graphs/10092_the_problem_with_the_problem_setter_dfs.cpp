/*
 Created by Thibault Gagnaux on 2019-06-25.

 uva 10092 - The problem with the problem setter

 Summary: Given m categories and n problems where each problem n_i may belong to
 to multiple categories m_i and each category m_i needs at least j problems find a
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
 capacities. --> this solution.
 2. Using only one adjacency list with a struct with three ints. The back_index lets us find the back edge in
 the graph efficiently otherwise enumerating the neighbours takes O(Max_edges). It works the following way:
 back_index of forward edge (u, v) = graph[v].size()
 back_index of backwards edge (u, v) = graph[v].size() - 1 // important!
 This approach presented two challenges:
  - Insertion order matters: we first have to insert the forward edge and then directly the back edge (the back_index
      of (u,v) is assigned after inserting the forward edges)
  - The back_edge of a back_edge is graph[v].size() - 1 because again the forward edge was inserted before

 This solution here uses variant 1 with a separate residual matrix and it is 0.01 slower as we save a 2D array with
 1 million entries.

 Total runtime of this solution (0.02s).

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
#include <iostream>
#include <stack>
#include <queue>
#include <array>
#include <numeric>

#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FORN(i, a, b) for(int i = a; i < b; i++)
#define PB push_back
#define VI vector<int>
#define MAX_VERTICES 1024
#define INF 10000000
#define MAX_EDGES 24

using namespace std;

int residual[MAX_VERTICES][MAX_VERTICES];
VI graph[MAX_VERTICES];
int path[MAX_VERTICES];


bool dfs(int source, int target) {
    stack<int> stack;
    stack.push(source);
    FORN(i, 0, MAX_VERTICES) path[i] = -1;
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        if (u == target) return true;

        for (auto &v : graph[u]) {
            if (residual[u][v] > 0 && path[v] == -1) {
                stack.push(v);
                path[v] = u;
            }
        }
    }
    return false;
}

int fordFulkerson(int source, int target) {
    int max_flow = 0;
    while (dfs(source, target)) {
        int path_flow = INF;
        for (int v = target; v != source; v = path[v]) {
            int u = path[v];
            if (residual[u][v] < path_flow) path_flow = residual[u][v];
        }
        for (int v = target; v != source; v = path[v]) {
            int u = path[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
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
            cin >> capacity;
            categories.PB(capacity);
            graph[0].PB(i);
            residual[0][i] = capacity;
        }
        FOR(i, categoryCount + 1, target - 1) {
            graph[i].PB(target);
            residual[i][target] = 1;
            int edgeCount;
            cin >> edgeCount;
            FORN(j, 0, edgeCount) {
                int to;
                cin >> to;
                graph[to].PB(i);
                graph[i].PB(to);
                residual[to][i] = 1;
            }
        }
        int max_flow = fordFulkerson(0, target);
        if (max_flow == accumulate(begin(categories), end(categories), 0)) {
            printf("1\n");
            FOR(i, 1, categoryCount) {
                int match = 0;
                FOR(j, categoryCount + 1, target - 1) {
                    if (residual[j][i] == 1) {
                        match++;
                        if (match > 1) printf(" %d", j - categoryCount);
                        else printf("%d", j - categoryCount);
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
            FORN(j, 0, target) {
                residual[i][j] = 0;
            }
        }
        categories.clear();
    }
    return 0;
}

