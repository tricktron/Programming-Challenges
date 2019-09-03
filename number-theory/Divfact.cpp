/*
 Created by Thibault Gagnaux on 30.11.18.

 spoj - DIVFACT - Divisors of factorial
*/

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
typedef unsigned long long int ull;
#define SIZE 50001
#define MODULO 1000000007

vector<ull> primes = {};

void generate_prime_numbers(int upper_limit, bool *numbers);
ull prime_division_count(ull number, ull factor);

int main() {
  int test_case_count = SIZE;
  cin >> test_case_count;
  ull n;
  bool numbers[SIZE] = {};
  generate_prime_numbers(SIZE, numbers);
  for (int i = 0; i < test_case_count; i++) {
    ull res = 1;
    cin >> n;
    ull prime;
    size_t j = 0;
    while (j < primes.size() && (prime = primes[j]) <= n)
    {
      res *= (prime_division_count(n, prime) + 1);
      res %= MODULO;
      j++;
    }
    cout << res % MODULO << endl;
  }
  return 0;
}

void generate_prime_numbers(int upper_limit, bool *numbers) {
  for (int i = 0; i < upper_limit; i++) numbers[i] = true;
  numbers[0] = false;
  numbers[1] = false;
  for (int j = 2; j < upper_limit; j++) {
    if (numbers[j]) {
      int prime = j;
      for (int k = prime + prime; k < upper_limit; k += prime) numbers[k] = false;
    }
  }
  for (size_t i = 2; i < upper_limit; i++) {
    if (numbers[i]) {
      primes.push_back(i);
    }
  }
}

ull prime_division_count(ull number, ull factor) {
  ull count = 0;
  ull exp = factor;
  while (exp <= number) {
    count += number / exp;
    exp *= factor;
  }
  return count;
}

