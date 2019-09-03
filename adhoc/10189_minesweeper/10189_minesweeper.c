#include <stdio.h>
#define MAX_NEIGHBOURS 8

typedef struct pos {
  int x, y;
} Pos;

typedef Pos *Posptr;

int fill_field_and_mines(int rows, int cols, char field[][cols], Pos *mines);
int is_mine(const char *value);
int get_neighbours(Pos *pos, Pos *neighbours, int rows, int cols, char field[][cols]);
int is_valid_neighbour(Posptr pos, int rows, int cols, char field[][cols]);
void increment_field(int rows, int cols, int length, char field[][cols], Pos *mines);
void print_output(int rows, int cols, char field[][cols], int count);

/** Replaces all '.' values on the field with '0' and stores each mine's position in the array mines.
 * @param rows int number of rows
 * @param cols int number of cols
 * @param field 2d minesweeper char array
 * @param mines Position array of mines
 * @return the number of mines
 */
int fill_field_and_mines(int rows, int cols, char field[][cols], Pos *mines) {
  int row, col;
  int length = 0;
  for (row = 0; row < rows; row++) {
    for (col = 0; col < cols; col++) {
      char value;
      scanf(" %c", &value);
      if (is_mine(&value)) {
        Pos pos;
        pos.x = row;
        pos.y = col;
        mines[length++] = pos;
        field[row][col] = value;
      } else field[row][col] = '0';
    }
  }
  return length;
}

/**
 * Computes if the value is a mine. A mine is a star '*' char value.
 * @param value
 * @return true if the value is a mine, false otherwise
 */
int is_mine(const char *value) {
  return *value == '*';
}

/**
 * Stores all the valid neighbours of the position pos in the array neighbours.
 * @param pos Position pointer
 * @param neighbours Position array
 * @param rows int number of rows
 * @param cols int number of cols
 * @param field 2d minesweeper char array
 * @return the number of valid neighbours of position pos
 */
int get_neighbours(Pos *pos, Pos *neighbours, int rows, int cols, char field[][cols]) {
  int i, j;
  int length = 0;
  for (i = -1; i <= 1; i++) {
    for (j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue; /** skip the position of itself **/
      Pos neighbour;
      neighbour.x = pos->x + i;
      neighbour.y = pos->y + j;
      if (is_valid_neighbour(&neighbour, rows, cols, field)) {
        neighbours[length++] = neighbour;
      }
    }
  }
  return length;
}

/**
 * Computes if the position pos is a valid neighbour.
 * @param pos Position pointer
 * @param rows int number of rows
 * @param cols int number of columns
 * @param field 2d minesweeper char array
 * @return true if position pos is a valid neighbour, false otherwise
 *
 * A valid neighbour is a valid position on the field which is NOT a mine.
 */
int is_valid_neighbour(Posptr pos, int rows, int cols, char field[][cols]) {
  if (pos->x >= 0 && pos->y >= 0 && pos->x < rows && pos->y < cols) {
    char value = field[pos->x][pos->y];
    return !is_mine(&value);
  }
  return 0;
}

/**
 * Increments all the neighbour fields of each mine by 1.
 * @param rows int number of rows
 * @param cols int number of cols
 * @param length int number of mines
 * @param field 2d minesweeper char array
 * @param mines Pos array holding all the mines, has length "length"
 */
void increment_field(int rows, int cols, int length, char field[][cols], Pos *mines) {
  int i;
  Pos neighbours[MAX_NEIGHBOURS];
  for (i = 0; i < length; i++) {
    Pos pos = mines[i];
    int size = get_neighbours(&pos, neighbours, rows, cols, field);
    int j;
    for (j = 0; j < size; j++) {
      Pos neighbour = neighbours[j];
      field[neighbour.x][neighbour.y]++;
    }
  }
}
/**
 * Prints the desired output of the minesweeper field.
 * @param rows int number of rows
 * @param cols int number of columns
 * @param field 2d minesweeper char array
 * @param count int counter
 */
void print_output(int rows, int cols, char field[][cols], int count) {
  int i, j;
  printf("Field #%d:\n", count);
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%c", field[i][j]);
      if (cols - j == 1) {
        if (rows - i != 1) printf("\n");
      }
    }
  }
}

int main() {
  int count = 1;
  for (;;) {
    int rows, cols;
    scanf(" %d %d", &rows, &cols);
    if (rows == 0 && cols == 0) break;

    if (count != 1) printf("\n\n"); /** needed to NOT create a newline at the very end**/
    char field[rows][cols];
    Pos mines[rows * cols];
    int number_mines = fill_field_and_mines(rows, cols, field, mines);
    increment_field(rows, cols, number_mines, field, mines);
    print_output(rows, cols, field, count);
    count++;
  }
  printf("\n");
  return 0;
}
