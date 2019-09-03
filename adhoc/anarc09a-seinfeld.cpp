/*
 Created by Thibault Gagnaux on 2019-02-22.

 spoj ANARC09A - Seinfeld
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

int main() {
    string line;
    int i = 0;
    while (true) {
        int modifications = 0;
        cin >> line;
        int open = 0;
        if (line[0] == '-') break;
        FORN(j, 0, line.length()) {
            char c = line[j];
            if (c == '{') {
                open++;
            } else {
                open--;
            }
            if (open < 0) {
                modifications++;
                open += 2;
            }
            if (open >= line.length() - j) {
                modifications++;
                open -= 2;
            }
        }
        i++;
        cout << i << "." << " " << modifications << endl;
    }
}



