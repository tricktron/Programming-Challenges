#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RELATIVES 500
#define GROUPSIZE 5

int compute_min_distance(int *arr, int length);
int randomized_partition(int *arr, int start, int end);
int partition(int *arr, int start, int end);
int randomized_select_iterative(int *arr, int nth_small, int start, int end);
void swap(int *arr, int i, int j);

/**
 * Partitions the array around the last element of the array.
 * @param arr int array
 * @param start int start index
 * @param end int end index
 * @return the int index of the pivot
 */

int partition(int *arr, int start, int end) {
  int pivot = arr[end];
  int i = start - 1;
  int j = end;
  for (;;) {
    while (arr[++i] < pivot);
    while (pivot < arr[--j]) if (j == start) break;
    if (i >= j) break;
    /**swap(arr, i, j);**/
    int temp1 = arr[i];
    arr[i] = arr[j];
    arr[j] = temp1;
  }
  /**swap(arr, i, end);**/
  arr[end] = arr[i];
  arr[i] = pivot;
  return i;
}

/**
 * Swaps the element at index i with element at index j of the array.
 * @param arr int array
 * @param i int index
 * @param j int index
 *
 * Note: Swap is only NOT used because it increases the runtime from 0.000 to 0.010 due to the additional function calls.
 */
void swap(int *arr, int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

/**
 * Partitions the array around a randomly selected pivot.
 * @param arr int array
 * @param start int start index
 * @param end int end index
 * @return the int index of the pivot element
 */

int randomized_partition(int *arr, int start, int end) {
  int rand_index = (rand() % (end - start)) + start;

  /**swap(arr, rand_index, end);**/
  int temp = arr[rand_index];
  arr[rand_index] = arr[end];
  arr[end] = temp;
  return partition(arr, start, end);
}

/**
 * Selects the nth-smallest element using a random pivot element.
 * @param arr: int array
 * @param nth_small: nth-smallest integer
 * @param start: int start index of arr
 * @param end: int end index of arr
 * @return: the nth-smallest integer of the array
 * @runtime: O(n)
 */
int randomized_select_iterative(int *arr, int nth_small, int start, int end) {
  while (end > start) {
    int mid = randomized_partition(arr, start, end);
    if (nth_small <= mid) end = mid - 1;
    if (nth_small >= mid) start = mid + 1;
  }
  return arr[nth_small];
}

/**
 * Computes total sum of each element of the array to its median value.
 * @param arr: int array
 * @param length: int length of array
 * @return: The total sum
 */
int compute_min_distance(int *arr, int length) {
  int min_dist, i, median, nth_small;
  min_dist = 0;
  nth_small = length >> 1;
  median = randomized_select_iterative(arr, nth_small, 0, length - 1);
  for (i = 0; i < length; i++) {
    min_dist += abs(median - arr[i]);
  }
  return min_dist;
}

int main() {
  int cases, length, i, j;
  int arr[RELATIVES];
  srand((unsigned int) time(NULL));
  scanf("%d", &cases);
  for (i = 0; i < cases; i++) {
    scanf("%d", &length);
    for (j = 0; j < length; j++) scanf("%d", &arr[j]);
    printf("%d\n", compute_min_distance(arr, length));
  }
  return 0;
}