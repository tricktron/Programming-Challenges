/*
 Created by Thibault Gagnaux on 29.06.18.

 uva 10042 - Smith Numbers

 Problem: Find the smallest smith number larger than the given input n.
 A smith number s has the property that:
 digit_sum(s) == digit_sum(prime_factors(s)) and s is NOT prime

 Solution:
 1. Find prime_factors with trial division
 2. Compare digit_sums
 3. Take care of the edge case that it is not a smith number if the number is prime
 */



#include <iostream>
#include <vector>
using namespace std;

vector<size_t> trial_division(size_t number) {
  vector<size_t> primes = {};
  while (number % 2 == 0) {
    primes.push_back(2);
    number /= 2;
  }
  size_t factor = 3;
  while (factor * factor <= number) {
    if (number % factor == 0) {
      primes.push_back(factor);
      number /= factor;
    } else {
      factor += 2;
    }
  }
  if (number != 1) primes.push_back(number);
  return primes;
}

size_t digit_sum(size_t number) {
  size_t sum = 0;
  while (number != 0) {
    sum += number % 10;
    number /= 10;
  }
  return sum;
}

bool is_smith_number(size_t number, const vector<size_t> prime_factors) {
  if (prime_factors.size() == 1) return false;
  size_t number_digit_sum = digit_sum(number);
  size_t prime_digit_sum = 0;
  for (size_t prime: prime_factors) prime_digit_sum += digit_sum(prime);
  return number_digit_sum == prime_digit_sum;
}

int main() {
  size_t number, test_case_count;
  cin >> test_case_count;
  for (int i = 0; i < test_case_count; ++i) {
    cin >> number;
    while (true) {
      number++;
      vector<size_t> primes = trial_division(number);
      if (is_smith_number(number, primes)) {
        cout << number << endl;
        break;
      }
    }
  }
  return 0;
}

