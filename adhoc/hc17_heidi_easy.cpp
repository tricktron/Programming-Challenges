/*
 Created by Thibault Gagnaux on 27.02.18.

 hc2 2017 - A and B. Heidi and Library - https://codeforces.com/contest/802/problem/A
*/


#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <list>
#define MAX_REQUESTS 400000

using namespace std;

struct BookPosition {
  int book;
  int position;
  BookPosition(int book, int position) : book(book), position(position) {}
  bool operator<(const BookPosition &other) const {
    return position < other.position;
  }
};

void read_input(int books, int *requests, list<int> *book_positions);
void update_priority_queue(list<int> *book_pos, int book, priority_queue<BookPosition> &pq);

int main() {
  int books;
  int capacity;
  cin >> books >> capacity;
  int requests[MAX_REQUESTS] = {};
  list<int> book_positions[books + 1] = {};
  priority_queue<BookPosition> pq;
  set<int> library;

  read_input(books, requests, book_positions);

  int cost = 0;
  for (int i = 0; i < books; i++) {
    int book = requests[i];
    if (library.size() < capacity) {
      if (library.find(book) == library.end()) {
        library.insert(book);
        cost++;
      }
    } else {
      if (library.find(book) == library.end()) {
        int book_to_delete = pq.top().book;
        pq.pop();
        library.erase(book_to_delete);
        library.insert(book);
        cost++;
      }
    }
    update_priority_queue(book_positions, book, pq);
  }
  cout << cost << endl;
  return 0;
}

void read_input(int books, int *requests, list<int> *book_positions) {
  for (int i = 0; i < books; i++) {
    int book;
    cin >> book;
    requests[i] = book;
    book_positions[book].push_back(i);
  }
}

void update_priority_queue(list<int> *book_pos, int book, priority_queue<BookPosition> &pq) {
  list<int> &positions = book_pos[book];
  positions.erase(positions.begin());
  pq.push(positions.empty() ? BookPosition(book, MAX_REQUESTS + 1) : BookPosition(book, positions.front()));
}





