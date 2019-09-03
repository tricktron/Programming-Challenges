/*
 Created by Thibault Gagnaux on 2019-04-05.

 uva 10249 - The grand dinner

 Summary: Given are 1<= M <=70 teams with 1 <= m_i <= 100 members and 1 <= N <= 50 tables with 2 <= n_i <= 100 capacity. Is there a
 seating arrangement so that no two members of the same team sit at the same table?
 If so: print 1 and the configuration, else print 0.

 Solution: This problem can be solved either greedily or using network flow. I chose to solve it greedily as it is
 faster:
 1. Sort the M teams decreasingly according to their m_i members.
 2. Order the N tables decreasingly according to their n_i capacity.
 3. For each team m in M do:
     if m_i > available_tables.size then return 0 because due to the Pigeon hole principle we need to place at
      least on one table two of the same family members.
     else:  3a) Put the m_i members on the m_i available tables and save the arrangement
            3b) Decrease each available_tables capacity by 1 and if the capacity == 0: available_tables.size--

 There are different ways to implement the ordering and retrieving of the k = sum of m_i for i in M tables:
 -> Using a priority queue see solution 10249_the_grand_dinner_priority_queue.cpp: Complexity: Init of queue: O(NlogN)
 Pushing and pop:+ O(klogN) = O(logN * (N + k))
 -> Using insertion sort see solution 10249_the_grand_dinner_insertion_sort.cpp. Complexity: O(k * N^2) but fast for small arrays

 This file uses an own implementation of a bucket queue with an array of vectors to make use of that
 the tables capacity can only be in the range 0-100. As a result we get a complexity of O(k + 100) to order and retrieve
 the k tables.

 Summary: The bucket queue approach is a tiny bit faster than the priority queue and the insertion sort. Priority queue
 and insertion sort are easier to code because you don't need to manually keep track of the remaining available tables.

 Total complexity: Sorting teams O(MlogM) + ordering and retrieving tables (O(k + 100)) = O(MlogM)
 AC 0.02-0.03

 Note: For network flow approach see: http://www.cse.psu.edu/~ads22/courses/cse565/F10/www/handouts/CSE565-F10-midterm2-sols.pdf
*/

#include <algorithm>
#include <vector>
#include <stdio.h>
#include <queue>

using namespace std;

#define VI vector<int>
#define FORN(i, a, b) for (int i = (a); i < (b); i++)


struct Table {
    int index;
    int capacity;

    Table() = default;

    Table(int index, int capacity) : index{index}, capacity{capacity} {}

    bool operator<(const Table &t) const {
        return capacity < t.capacity;
    }
};

struct Team {
    int index;
    int size;

    bool operator<(const Team &t) const {
        return size > t.size;
    }
};

int main() {
    Team teams[71];
    int membersCount[71];
    int arrangement[71][51];
    Table temp[101];
    priority_queue<Table> tables;
    int M, N;
    while (scanf("%d %d", &M, &N) == 2) {
        if (M == 0 && N == 0) break;

        FORN(i, 0, M) {
            Team t;
            t.index = i;
            scanf("%d", &membersCount[i]);
            t.size = membersCount[i];
            teams[i] = t;
        }
        FORN(i, 0, N) {
            int capacity;
            scanf("%d", &capacity);
            tables.emplace(Table(i, capacity));
        }

        bool validSeating = true;
        sort(teams, teams + M);
        FORN(i, 0, M) {
            Team team = teams[i];
            if (team.size > tables.size()) {
                validSeating = false;
                break;
            }
            int emptyTablesCount = 0;
            FORN(j, 0, team.size) {
                Table table = tables.top();
                tables.pop();
                arrangement[team.index][j] = table.index;
                table.capacity--;
                if (table.capacity > 0) {
                    temp[emptyTablesCount++] = table;
                }
            }

            FORN(j, 0, emptyTablesCount) {
                tables.push(temp[j]);
            }
        }

        if (validSeating) {
            printf("1\n");
            FORN(i, 0, M) {
                FORN(j, 0, membersCount[i]) {
                    printf("%d", arrangement[i][j] + 1);
                    if (j != membersCount[i] - 1) printf(" ");
                }
                printf("\n");
            }
        } else {
            printf("0\n");
        }
        priority_queue<Table> empty;
        tables.swap(empty);
    }
    return 0;
}