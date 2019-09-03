/*
 Created by Thibault Gagnaux on 2019-02-22.

 spoj AMR11E - Distinct Primes
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

const int SIZE = 3001;
bool numbers[SIZE] = {};
VI primes = {};

VI generate_prime_numbers(int upper_limit, bool *numbers) {
    VI primes = {};
    FORN(i, 0, upper_limit) numbers[i] = true;
    numbers[0] = false;
    numbers[1] = false;
    FORN(j, 2, upper_limit) {
        if (numbers[j]) {
            int prime = j;
            for (int k = prime + prime; k < upper_limit; k += prime) numbers[k] = false;
        }
    }
    for (int i = 2; i < upper_limit; i++) {
        if (numbers[i]) {
            primes.PB(i);
        }
    }
    return primes;
}

vector<int> generate_lucky_numbers() {
    VI lucky_numbers = {};
    FOR(i, 30, SIZE)
    {
        int distinct_primes = 0;
        for (int prime: primes) {
            if (i % prime == 0)
            {
                distinct_primes++;
            }
            if (distinct_primes == 3)
            {
                lucky_numbers.PB(i);
                break;
            }
        }
    }
    return lucky_numbers;
}

int main() {
    int T, n;
    primes = generate_prime_numbers(SIZE, numbers);
    VI lucky_numbers = generate_lucky_numbers();
    cin >> T;
    FOR(i, 1, T) {
        cin >> n;
        n--;
        cout << lucky_numbers[n] << endl;
    }
    return 0;
}

