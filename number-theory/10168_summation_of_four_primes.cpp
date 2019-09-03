/*
Created by Thibault Gagnaux on 28.06.18.

uva 10168 - Summation of Four Primes

Problem: Find a way to express a given integer n < 10^7 as the sum of exactly four primes. There may
be multiple solutions but any good one will be accepted.

Solution: Using the goldbach and waring conjecture we get:
n = prime or sum of 3 primes if n is odd
n = sum of 2 primes if n is even
As every good solution gets accepted we can simplify the problem using the conjectures:
If n is even: subtract 4 (2 + 2) which gives us again a even number and thus the number is
is another sum of 2 primes -> Find these two numbers trying all prime numbers up to n - 4 using
the numbers lookup table with access of O(1).
If n is odd: subtract 5 (2 + 3) which gives us again an even number and do the same as above for n - 5
Edge case: if n < 8 it is impossible, try it.
*/

#include <iostream>
#include <vector>
using namespace std;
#define UPPER_LIMIT 10000001

vector<size_t> generate_prime_numbers(bool *numbers) {
  /*
   * Uses the sieve of eratosthenes.
   */
  vector<size_t> primes = {2};
  numbers[0] = true;
  numbers[1] = true;
  for (size_t j = 4; j < UPPER_LIMIT; j += 2) numbers[j] = true;
  for (size_t k = 3; k < UPPER_LIMIT; k += 2) {
    if (!numbers[k]) {
      primes.push_back(k);
      for (size_t i = k * k; i < UPPER_LIMIT; i += 2 * k) {
        if (!numbers[i]) numbers[i] = true;
      }
    }
  }
  return primes;
}

void print_four_primes(size_t number, const bool *numbers, const vector<size_t> &primes) {
  if (number < 8) {
    cout << "Impossible." << endl;
    return;
  }
  size_t prime1 = 2;
  size_t prime2 = number % 2 == 0 ? 2: 3;
  number -= prime1 + prime2;

  for (size_t prime3: primes) {
    size_t prime4 = number - prime3;
    if (!numbers[prime4]) {
      cout << prime1 << " " << prime2 << " " << prime3 << " " << prime4 << endl;
      break;
    }
  }
}

int main() {
  static bool numbers[UPPER_LIMIT] = {};
  vector<size_t> primes = generate_prime_numbers(numbers);
  size_t number;
  while (cin >> number && number) {
    print_four_primes(number, numbers, primes);
  }
  return 0;
}



