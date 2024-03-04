#include <iostream>
#include <iomanip>

int getPrecision(int number) {
  int counter{0};
  while (number > 0) {
    ++counter;
    number /= 10;
  }
  return counter;
}

void fillPrecisionArray(int *precisions, int **arr, const int rows, const int cols){
  for (int i = 0; i < cols; ++i) {
    int maxElem = arr[0][i];
    for (int j = 0; j < rows; ++j) {
      maxElem = std::max(maxElem, arr[j][i]);
    }
    precisions[i] = getPrecision(maxElem);
  }
}

void initArray(int **arr, const int rows, const int cols){
  for (int i = 0; i < rows; ++i){
    arr[i] = new int[cols];
    for (int j = 0; j < cols; ++j){
      arr[i][j] = 0;
    }
  }
}

void fillArray(int **arr, const int rows, const int cols){
  char direction = 'r';
  int val{1};
  int row{0};
  int col{0};

  while (val < rows * cols) {
    arr[row][col] = val;

    switch (direction) {
      case 'r':
        ++col;
        if (col == cols - 1 || arr[row][col + 1] != 0) {
          direction = 'd';
        }
        break;
      case 'd':
        ++row;
        if (row == rows - 1 || arr[row + 1][col] != 0) {
          direction = 'l';
        }
        break;
      case 'l':
        --col;
        if (col == 0 || arr[row][col - 1] != 0) {
          direction = 'u';
        }
        break;
      case 'u':
        --row;
        if (row == 0 || arr[row - 1][col] != 0) {
          direction = 'r';
        }
        break;
    }
    ++val;
  }
  arr[row][col] = val;
}

void printArray(int **arr, const int rows, const int cols){
  int *precisions = new int[cols];
  fillPrecisionArray(precisions, arr, rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << std::setiosflags(std::ios::right) << std::setw(precisions[j])
                << arr[i][j];
      if (j != cols - 1){
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  delete[] precisions;
}

void deleteArray(int **arr, int rows){
  for (int i = 0; i < rows; ++i){
    delete[] arr[i];
  }
  delete[] arr;
}

int main() {
  int rows;
  int cols;
  std::cin >> rows >> cols;

  int **arr = new int *[rows];

  initArray(arr, rows, cols);
  fillArray(arr, rows, cols);

  printArray(arr, rows, cols);
  deleteArray(arr, rows);

  return 0;
}
