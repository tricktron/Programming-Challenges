/*
 Created by Thibault Gagnaux on 2019-03-08.

 uva 10158 - War

 Summary: Finding disjoint sets that preserve the properties of:
  - the equivalence relation areFriends
  - the symmetric and irreflexive relation areEnemies

 Solution: Use a union find data structure to represent disjoint sets for the relation areFriends. To handle the
 areEnemies relation I introduced an enemy element with value x + n. This means doubling the unionFind size. Then
 follow the properties of the relations:

 Rough pseudocode summary:

 if setFriends x and y: unite(x,y) and unite(enemy_x, enemy_y) else if x and y areEnemies print -1
 if setEnemies x and y: unite(enemy_x, y) and unite (x, enemy_y) else if x and y are friends print -1
 if areFriends x and y: print 1 else print 0
 if areEnemies x and enemy_y or enemy_x and y: print 1 else 0
 see code for details like how the irreflexifity of areEnemies (nobody is an enemy of himself is handled by using:
 isSameSet(enemy_x, enemy_y).
*/


#include <bits/stdc++.h>

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

struct UnionFind {
    VI link;
    VI size;

    explicit UnionFind(int n) {
        link.assign(n, 0);
        size.assign(n, 1);
        FORN(i, 0, n) link[i] = i;
    }

    int find(int x) {
        if (x == link[x]) return x;
        return link[x] = find(link[x]);
    }

    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (size[x] < size[y]) swap(x, y);
        size[x] += size[y];
        link[y] = x;
    }
};

enum Operation {setFriends = 1, setEnemies = 2, areFriends = 3, areEnemies = 4};


int main() {
    int n, c, x, y;
    cin >> n;
    UnionFind uf = UnionFind(2 * n + 10);
    while (cin >> c >> x >> y && (c | x | y)) {
        int enemy_x = x + n;
        int enemy_y = y + n;
        switch (c) {
            case setFriends:
                if (uf.isSameSet(x, enemy_y) && uf.isSameSet(enemy_x, y)) {
                    cout << -1 << "\n";
                } else {
                    uf.unite(x, y);
                    uf.unite(enemy_x, enemy_y);
                }
                break;
            case setEnemies:
                if (uf.isSameSet(x, y) || uf.isSameSet(enemy_x, enemy_y)) {
                    cout << -1 << "\n";
                } else {
                    uf.unite(x, enemy_y);
                    uf.unite(enemy_x, y);
                }
                break;
            case areFriends:
                if (uf.isSameSet(x, y)) {
                    cout << 1 << "\n";
                } else {
                    cout << 0 << "\n";
                }
                break;
            case areEnemies:
                if (uf.isSameSet(x, enemy_y) || uf.isSameSet(enemy_x, y)) {
                    cout << 1 << "\n";
                } else {
                    cout << 0 << "\n";
                }
                break;
            default:break;
        }
    }
    return 0;
}

