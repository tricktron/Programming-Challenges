#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;


/* 
The uncommented solution was my first try with a hashmap to track min in O(logn). There are two more elegant solutions:
1. Use two stacks. One normal stack for push, pop, top and one to track the min. Update min at push and pop in the
min stack. Needs O(n) additional space.

2. See code. Store the difference: (x-min) in the stack. Two caveats:
- May overflow: use long.
- How to retrieve original value: If top() < 0 return min else return top() + min

But in O(1) space!
*/


/* class MinStack {
public:
    vector<int> stack;
    map<int, int> m;

    MinStack() {
        stack = {};
        m = {};
    }

    void push(int x) {
        m[x]++;
        stack.push_back(x);
    }

    void pop() {
        int last = stack.back();
        stack.pop_back();
        if (m[last] > 1) {
            m[last]--;
        } else {
            m.erase(last);
        }
    }

    int top() {
        return stack.back();
    }

    int getMin() {
        auto i = m.begin();
        return i->first;
    }
}; */

class MinStack {
public:
  /** initialize your data structure here. */
  stack<long> s;
  long min;

  MinStack() {}

  void push(int x) {
    if (s.empty()) {
      min = x;
      s.push(0);
    } else {
      s.push(x - min);
      if (x < min) min = x;
    }
  }

  void pop() {
    if (!s.empty()) {
      long t = s.top();
      if (t < 0) min -= t;
      s.pop();
    }
  }

  int top() {
    long t = s.top();
    if (t < 0) return (int) min;
    return (int) (t + min);
  }

  int getMin() { return (int) min; }
};

int main() {
  MinStack *s = new MinStack();
  s->push(-2);
  s->push(0);
  s->push(-3);
  cout << s->getMin() << endl;
  s->pop();
  cout << s->top() << endl;
  cout << s->getMin() << endl;
}
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */