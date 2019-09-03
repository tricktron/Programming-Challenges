/*
Created by Thibault Gagnaux on 27.02.18.

uva 10006 - Carmichael Numbers
*/
#include <iostream>;
#define SIZE 65100
using namespace std;

void generate_prime_numbers(int upper_limit, bool *numbers);
bool is_carmichael(int number, const bool *numbers);
int fast_modular_exponentiation(long long base, int exp, int mod);

int main() {
  bool numbers[SIZE] = {};
  generate_prime_numbers(SIZE, numbers);
  int number;
  while (cin >> number && number) {
    if (is_carmichael(number, numbers)) {
      printf("The number %d is a Carmichael number.\n", number);
    } else {
      printf("%d is normal.\n", number);
    }
  }
}

bool is_carmichael(int number, const bool *numbers) {
  if (numbers[number]) return false;
  for (int i = 2; i < number; i++) {
    if (fast_modular_exponentiation(i, number, number) != i) return false;
  }
  return true;

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
}

int fast_modular_exponentiation(long long base, int exp, int mod) {
  long long result = 1;
  while (exp > 0) {
    if ((exp & 1) == 1) result = (result * base) % mod;
    base = (base * base) % mod;
    exp >>= 1;
  }
  return (int) result;
}

