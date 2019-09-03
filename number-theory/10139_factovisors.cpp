/*
 Created by Thibault Gagnaux on 22.06.18.

 uva 10139 - Factovisors

 Problem: Does m divide n!, e.g. Does 9 divide 6!
 Solution: You cannot calculate n! as the factorial grows much too quickly.
 1. Find the prime factorization of m by trial division: 9 = 3^2
 2.a Find the highest power of all prime factors in n!: 6! / 3 = 2
 2.b Divide by the number of the times the prime factor appears: 2 / 2 = 1
 3. That means that the highest power of 3^2 is 1 and it thus divides 6!
 4. E.g. 27 = 3^3 -> 6! / 3 = 2 -> 2 / 3 = 0 -> 27 does not divide 6!
 5.a Edge case: multiple prime factors All prime factors must divide n! -> If one does not
 divide n! you can stop early. This is done through an if-statement.
 5.b Edge case: m = 0: m divides all possible n. -> Stop early.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<size_t, size_t > trial_division(size_t number) {
  unordered_map<size_t , size_t> factors = {};
  while (number % 2 == 0) {
    factors[2]++;
    number /= 2;
  }
  size_t factor = 3;
  while (factor * factor <= number) {
    if (number % factor == 0) {
      factors[factor]++;
      number /= factor;
    } else {
      factor += 2;
    }
  }
  if (number != 1) factors[number]++;
  return factors;
}

size_t highest_power_of(size_t number, size_t factor, size_t count) {
  size_t highest_power = 0;
  size_t base = factor;
  while (factor <= number) {
    highest_power += number / factor;
    factor *= base;
  }
  return highest_power / count;
}

void is_divisible(size_t m, size_t n) {
  if (m == 0) {
    cout << m << " divides " << n << "!" << endl;
    return;
  }
  unordered_map<size_t, size_t > prime_factors_count = trial_division(m);
  for (auto &prime_factor: prime_factors_count) {
    if (highest_power_of(n, prime_factor.first, prime_factor.second) == 0) {
      cout << m << " does not divide " << n << "!" << endl;
      return;
    }
  }
  cout << m << " divides " << n << "!" << endl;
}

int main() {
  size_t n, m;
  while (cin >> n >> m && n | m) {
    is_divisible(m, n);
  }
  return 0;
}


