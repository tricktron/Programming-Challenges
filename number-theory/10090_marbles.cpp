/*
 Created by Thibault Gagnaux on 25.06.18.

 uva 10090 - Marbles

 Problem: We have two boxes m1 and m2 which cost c1 bzw. c2 and can hold n1 bzw. n2 marbles. We need to divide the n
 marbles so that the cost becomes minimal and the boxes are filled to its capacity. All numbers are 1 <= n <= 10^9. If
 it is not possible print failed.

 Solution: Interestingly the problem is the same as solving the diophantine equation for integers: n1 * x + n2 * y = n
 and minimizing the equation c = c1 * x + y * m2.
 1. We find x0, y0, and gcd using the extended euclidean algorithm: n1 * x0 + n2 * y0 = gcd
 2. If gcd does not divide n no solution for the diophantine equation exists and we print failed.
 3. Compute the factors: factor1 = x0 * n / gcd and factor2 = y0 * n / gcd so that n1 * factor1 + n2 * factor2 = n
 4. Theorem says that all solutions are given by:
 x = factor1 + n2/gcd * bound_value and y = factor2 - n1/gcd * bound_value with x >=0 and y >= 0
 5. It remains to find the bound_value that minimizes the cost function. Realizing that the cost function is linear
 (A straight line) the minimum can only appear at its boundary value.
 6. Using x >= 0 and y >= 0 we can find the two possible boundary values:
 lower_bound = ceil(-factor1 * gcd / n2), upper_bound = floor(factor2 * gcd / n1)
 7. Check which value has the smaller cost function
 8. Use the smaller value to calculate x and y.

 Pitfalls/Edge cases:
1. Integer overflow --> You have to use long long int as numbers 10^9 get multiplied.
2. Rounding --> Do not round on your own but use ceil and floor functions! How to round if number is negative. Floor
 and ceil take care of that.
 3. Nasty edge case: if capacity of one box is larger than n a valid solution takes a negative number of one box which
 makes no sense at all. Check if one box count is negative -> print failed.
*/

#include <iostream>
#include <cmath>
using namespace std;

struct Euclid {
  int gcd, x, y;
  Euclid(int gcd, int x, int y) : gcd(gcd), x(x), y(y) {}
};

struct Box {
  int cost, capacity;
  Box() {
    cost = 0;
    capacity = 0;
  }
};

struct Solution {
  long long int box_1_count;
  long long int box_2_count;
  Solution(long long int box_1_count, long long int box_2_count) : box_1_count(box_1_count), box_2_count(box_2_count) {}
};

Euclid extended_euclid(int a, int b) {
  int x0 = 1, y1 = 1;
  int y0 = 0, x1 = 0;
  while (b != 0) {
    int q = a / b;
    int r = a % b;
    a = b;
    b = r;
    int temp1 = x1;
    x1 = x0 - q * x1;
    x0 = temp1;
    int temp2 = y1;
    y1 = y0 - q * y1;
    y0 = temp2;
  }
  return Euclid{a, x0, y0};
}
long long int cost(Box box1,
                   Box box2,
                   long long int factor1,
                   long long int factor2,
                   Euclid euclid,
                   long long int bound_value) {
  long long int first = box1.cost * (factor1 + box2.capacity / euclid.gcd * bound_value);
  long long int second = box2.cost * (factor2 - box1.capacity / euclid.gcd * bound_value);
  return abs(first + second);
}

Solution compute_min_cost(Box box1, Box box2, Euclid euclid, long long int marbles_count) {
  long long int factor1 = euclid.x * marbles_count / euclid.gcd;
  long long int factor2 = euclid.y * marbles_count / euclid.gcd;
  auto lower_bound = static_cast<long long int>(floor(factor2 * euclid.gcd / (double) box1.capacity));
  auto upper_bound = static_cast<long long int>(ceil(-factor1 * euclid.gcd / (double) box2.capacity));
  long long int min_bound_value = lower_bound;
  long long int lower_cost = cost(box1, box2, factor1, factor2, euclid, lower_bound);
  if (cost(box1, box2, factor1, factor2, euclid, upper_bound) < lower_cost) min_bound_value = upper_bound;
  long long int box_count1 = factor1 + (box2.capacity / euclid.gcd * min_bound_value);
  long long int box_count2 = factor2 - (box1.capacity / euclid.gcd * min_bound_value);
  return Solution{box_count1, box_count2};

}

int main() {
  long long int marbles_count;
  while (cin >> marbles_count && marbles_count) {
    Box box1, box2;
    cin >> box1.cost >> box1.capacity >> box2.cost >> box2.capacity;
    Euclid euclid = extended_euclid(box1.capacity, box2.capacity);
    if (marbles_count % euclid.gcd) cout << "failed" << endl;
    else {
      Solution min_cost = compute_min_cost(box1, box2, euclid, marbles_count);
      if (min_cost.box_1_count < 0 || min_cost.box_2_count < 0) cout << "failed" << endl;
      else cout << min_cost.box_1_count << " " << min_cost.box_2_count << endl;
    }
  }
  return 0;
}



