/*
 copyright: 2018, Thibault Gagnaux
 uva: 706 lc-display
 link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=647
 problem: Print numbers in the LED format.
 category: adhoc
 solution:  1. Use this representation for each number:
 	   -0-   upper part
 	  |   |
 	  2   1 upper left / right part
	  |   |
	   -3-  middle part
	  |   |
	  5   4 lower left /right part
	  |   |
	   -6-  lower part

	  2. Use the conversion table defined below to print each number.
	  3. Pay attention to newlines.
 */

#include <tiff.h>
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
#define LEFT_UPPER_PART 2
#define RIGHT_UPPER_PART 1
#define LEFT_LOWER_PART 5
#define RIGHT_LOWER_PART 4

const char conversionTable[10][7] = {
          /* 0    1    2    3    4    5    6 */
    /* 0 */ '-', '|', '|', ' ', '|', '|', '-',
    /* 1 */ ' ', '|', ' ', ' ', '|', ' ', ' ',
    /* 2 */ '-', '|', ' ', '-', ' ', '|', '-',
    /* 3 */ '-', '|', ' ', '-', '|', ' ', '-',
    /* 4 */ ' ', '|', '|', '-', '|', ' ', ' ',
    /* 5 */ '-', ' ', '|', '-', '|', ' ', '-',
    /* 6 */ '-', ' ', '|', '-', '|', '|', '-',
    /* 7 */ '-', '|', ' ', ' ', '|', ' ', ' ',
    /* 8 */ '-', '|', '|', '-', '|', '|', '-',
    /* 9 */ '-', '|', '|', '-', '|', ' ', '-',
};

void print_upper_middle_lower_part(int16 segment, int i, int16 digit) {
  cout << " ";
  for (int16 k = 0; k < segment; k++) cout << conversionTable[digit][(i / (segment + 1)) * 3];
  cout << " ";
}

void print_between_part(int16 segment, int16 digit, int16 LEFT_PART, int16 RIGHT_PART) {
  cout << conversionTable[digit][LEFT_PART];
  for (int16 k = 0; k < segment; k++) cout << " ";
  cout << conversionTable[digit][RIGHT_PART];
}

void print_between_middle_and_lower_part(int16 segment, int16 digit) {
  print_between_part(segment, digit, LEFT_LOWER_PART, RIGHT_LOWER_PART);
}

void print_between_upper_and_middle_part(int16 segment, int16 digit) {
  print_between_part(segment, digit, LEFT_UPPER_PART, RIGHT_UPPER_PART);
}

void print_lcd(int16 segment, const string &number) {
  auto number_length = static_cast<int16> (number.length());
  for (int i = 0; i < 2 * segment + 3; i++) {
    for (int16 j = 0; j < number_length; j++) {
      int16 digit = number[j] - '0';
      if (i % (segment + 1) == 0) print_upper_middle_lower_part(segment, i, digit);
      if (i > 0 && i < (segment + 1)) print_between_upper_and_middle_part(segment, digit);
      if (i > (segment + 1) && i < (2 * segment + 2)) print_between_middle_and_lower_part(segment, digit);
      if (j != number_length - 1) cout << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  while (true) {
    int16 segment;
    string number;
    cin >> segment >> number;
    if (segment == 0) break;
    print_lcd(segment, number);
  }
  return 0;
}


