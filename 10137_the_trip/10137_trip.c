#include <stdio.h>
#include <math.h>

#define TWO_DECIMALS 0.01

double compute_min_average_difference(double average, const double *expenses, int students);
double compute_sum(int students, double *expenses);
double cut_off_to_2_decimals(double f);

/**
 * Computes the minimal sum difference of each expense to the average of all expenses.
 * @param average double average of all expenses
 * @param expenses double array containing all expenses of each student
 * @param students int number of students
 * @return the minimal sum difference
 *
 * We need to consider two things:
 *  1. There is a negative sum and a positive sum. In the end we need the maximum of these two otherwise we may have
 *  0.01 cents too less.
 *  2. As we only have a precision of 2 decimals we need to round after each addition.
 */
double compute_min_average_difference(double average, const double *expenses, int students) {
  int i;
  double negative_difference = 0, positive_difference = 0;
  for (i = 0; i < students; i++) {
    if (expenses[i] > average) positive_difference += cut_off_to_2_decimals(expenses[i] - average);
    else negative_difference += cut_off_to_2_decimals(expenses[i] - average);
  }
  negative_difference = fabs(negative_difference);
  return (positive_difference > negative_difference) ? positive_difference : negative_difference;
}

/**
 * Stores the expenses in an array and returns the sum of all expenses.
 * @param students int number of students
 * @param expenses double array containing all the expenses of each student
 * @return the sum of all expenses.
 */
double compute_sum(int students, double *expenses) {
  double sum = 0;
  int i;
  for (i = 0; i < students; i++) {
    double expense;
    scanf("%lf", &expense);
    sum += expense;
    expenses[i] = expense;
  }
  return sum;
}

/**
 * Cuts off all the decimal bits except the two most significant ones of a double. E.g. 12.7699 becomes 12.76
 * @param f double point number
 * @return the corrected double.
 *
 * This is needed because we only have a precision of 2 decimal places in the given exercise.
 */
double cut_off_to_2_decimals(double f) {
  double d = f / TWO_DECIMALS;
  int integer_part = (int) d;
  return integer_part * TWO_DECIMALS;
}

int main() {
  int students;
  for (;;) {
    scanf("%d", &students);
    if (students == 0) break;
    double expenses[students];
    double average = compute_sum(students, expenses) / students; /** NOT ROUNDED **/
    printf("$%.2lf\n", compute_min_average_difference(average, expenses, students));
  }
  return 0;
}


