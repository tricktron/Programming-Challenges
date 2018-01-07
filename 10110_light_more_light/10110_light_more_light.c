#include <stdio.h>

int is_perfect_square(unsigned long int number);

int is_no_perfect_square_by_last_digit(unsigned long int number) {
  /*
   * Every number ending in 2, 3, 7, 8 is NOT a perfect square.
   * See for more info: http://burningmath.blogspot.ch/2013/09/how-to-check-if-number-is-perfect-square.html
   */
  int last_digit = (int) (number % 10);
  if (last_digit == 2 || last_digit == 3 || last_digit == 7 || last_digit == 8) return 1;
  return 0;
}

int is_perfect_square(unsigned long int number) {
  /*
   * Uses the binary search algorithm.
   */
  if (is_no_perfect_square_by_last_digit(number)) return 0;

  unsigned long int start = 0;
  unsigned long int end = number >> 1;

  while (start <= end) {
    unsigned  long int mid = (start + end) >> 1;
    unsigned long int square = mid * mid;
    if (square == number) return 1;
    else if (square < number) start = mid + 1;
    else end = mid - 1;
  }
  return 0;
}

int main() {
  for (;;) {
    unsigned long int number;
    scanf("%lu", &number);

    if (number == 0) break;
    if (number == 1) printf("yes\n");
    else {
      printf("%s\n", (is_perfect_square(number)) ? "yes" : "no");
    }
  }
  return 0;
}

