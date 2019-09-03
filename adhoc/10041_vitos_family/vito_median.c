#include <stdio.h>
#include <stdlib.h>

#define RELATIVES 500
#define GROUPSIZE 5

void swap(int *arr, int i, int j);
int partition_pivot(int *arr, int start, int end, int pivot);
int median5_partition(int *arr, int start, int end);
int median5_select_iterative(int *arr, int nth_small, int start, int end);
int find_median_of_medians(int *arr, int start, int end);
void insertion_sort(int *arr, int start, int end);
int compute_min_distance(int *arr, int length);

/**
 * Swaps the element at index i with element at index j of the array.
 * @param arr int array
 * @param i int index
 * @param j int index
 */
void swap(int *arr, int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

/**
 * Partitions the array around the pivot.
 * @param arr int array
 * @param start int start index
 * @param end int end index
 * @param pivot int pivot element
 * @return the int index of the pivot
 */
int partition_pivot(int *arr, int start, int end, int pivot) {
  int i = start - 1;
  int j;
  for (j = start; j < end; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(arr, i, j);
    }
  }
  return i + 1;
}

/**
 * Partitions the array around the median of the medians pivot.
 * @param arr int array
 * @param start int start index
 * @param end int end index
 * @return the int index of the pivot element
 */
int median5_partition(int *arr, int start, int end) {
  int median5 = find_median_of_medians(arr, start, end);
  return partition_pivot(arr, start, end, median5);
}

/**
 * Selects the nth-smallest element using the median of medians as the pivot.
 * @param arr: int array
 * @param nth_small: nth-smallest integer
 * @param start: int start index of arr
 * @param end: int end index of arr
 * @return: the nth-smallest integer of the array
 * @runtime: O(n)
 */
int median5_select_iterative(int *arr, int nth_small, int start, int end) {
  while (end > start) {
    int mid = median5_partition(arr, start, end);
    if (nth_small <= mid) end = mid - 1;
    if (nth_small >= mid) start = mid + 1;
  }
  return arr[nth_small];
}

/**
 * Computes the median of medians of an array.
 * @param arr int array
 * @param start int start index
 * @param end int end index
 * @return the int median of medians
 *
 * If you split the array into n groups of size <= 5 the median of medians is the median of each group's median.
 */
int find_median_of_medians(int *arr, int start, int end) {
  if (end - start < GROUPSIZE) {
    insertion_sort(arr, start, end);
    return arr[(end - start + 1) >> 1];
  }
  int groups = (end - start + 1) / GROUPSIZE;
  int last_group = (end - start + 1) % GROUPSIZE;
  int medians[groups + 1];
  int i;
  for (i = 0; i < groups; i++) {
    insertion_sort(arr, start, end);
    medians[i] = arr[(end - start + 1) >> 1];
  }
  if (last_group != 0) {
    int left = groups * GROUPSIZE;
    int right = left + last_group - 1;
    insertion_sort(arr, left, right);
    medians[groups] = arr[(right - left + 1) >> 1];
  }
  return find_median_of_medians(medians, 0, groups);
}

/**
 * Sorts the array in ascending order using insertion sort.
 * @param arr int array
 * @param start int start index
 * @param end int end index
 */
void insertion_sort(int *arr, int start, int end) {
  int i, j, key;
  for (j = start + 1; j <= end; j++) {
    key = arr[j];
    i = j - 1;
    while (i >= 0 && arr[i] > key) {
      arr[i + 1] = arr[i];
      i--;
    }
    arr[i + 1] = key;
  }
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
  nth_small = (length >> 1);
  median = median5_select_iterative(arr, nth_small, 0, length - 1);
  for (i = 0; i < length; i++) {
    min_dist += abs(median - arr[i]);
  }
  return min_dist;
}

int main() {
  int cases, length, i, j;
  int arr[RELATIVES];
  scanf("%d", &cases);
  for (i = 0; i < cases; i++) {
    scanf("%d", &length);
    for (j = 0; j < length; j++) scanf("%d", &arr[j]);
    printf("%d\n", compute_min_distance(arr, length));
  }
  return 0;
}