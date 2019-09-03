/*
 Created by Thibault Gagnaux on 15.02.18.

 uva 10104 - Extended Euclid
*/

#include <iostream>
#include <vector>
#include <ratio.h>
using namespace std;

struct Euclid {
  int gcd, x, y;
  Euclid(int a, int x0, int y0): gcd(a), x(x0), y(y0)
  {}
};

int extended_euclid(int a, int b, int &x, int &y);
Euclid extended_euclid2(int a, int b);

int main() {
    int g = ____gcd(12, 8)
  int a, b, x, y;
  while (cin >> a >> b && a | b) {
    int d = extended_euclid(a, b, x, y);
    if (a == b) {
      x = 0;
      y = 1;
    }
    printf("%d %d %d\n", x, y, d);
    Euclid euclid = extended_euclid2(a, b);
    cout << euclid.x << " " << euclid.y << " " << euclid.gcd << endl;
  }
}
int extended_euclid(int a, int b, int &x, int &y) {
  int x1, y1, d;
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }

  d = extended_euclid(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

Euclid extended_euclid2(int a, int b) {
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
  return {a, x0, y0};
}



