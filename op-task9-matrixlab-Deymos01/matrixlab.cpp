#include <cstring>
#include <fstream>
#include <iostream>

template <typename T>
void deleteMatrix(T **arr, int rows) {
  for (int i{0}; i < rows; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

void printMatrix(double *M[], const int rows, const int cols) {
  for (int i{0}; i < rows; ++i) {
    for (int j{0}; j < cols; ++j) {
      std::cout << M[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void readMatrix(double *M[], const int rows, const int cols,
                std::ifstream &inpFile) {
  for (int i{0}; i < rows; ++i) {
    M[i] = new double[cols];
    for (int j{0}; j < cols; ++j) {
      inpFile >> M[i][j];
    }
  }
}

void writeMatrix(double *M[], const int rows, const int cols,
                 std::ofstream &outFile) {
  for (int i{0}; i < rows; ++i) {
    for (int j{0}; j < cols; ++j) {
      outFile << M[i][j] << ((j == cols - 1) ? "\n" : " ");
    }
  }
}

double makeUpperTriangMatrix(double *M[], const int rows, const int cols) {
  for (int col{0}; col < rows; ++col) {
    int i = col;
    while ((i < cols) && (M[i][col] == 0)) {
      ++i;
    }
    if (i >= cols) {
      return 0;
    }
    std::swap(M[i], M[col]);
    if (i != col) {
      for (int elem{0}; elem < cols; ++elem) {
        M[i][elem] *= -1;
      }
    }
    for (int row{col + 1}; row < rows; ++row) {
      double lineCoef = M[row][col] / M[col][col];
      for (int elem{col}; elem < cols; ++elem) {
        M[row][elem] = M[row][elem] - M[col][elem] * lineCoef;
      }
    }
  }
  double det{1};
  for (int row{0}; row < rows; ++row) {
    if (M[row][row] != 0) {
      double div{M[row][row]};
      det *= div;
      for (int col{row}; col < cols; ++col) {
        M[row][col] /= div;
      }
    }
  }
  return det;
}

double calcDeterminate(double *M[], const int rows, const int cols) {
  if (rows != cols) {
    throw "error";
  }
  return makeUpperTriangMatrix(M, rows, cols);
}

void calcInvert(double *M[], const int rows, const int cols) {
  double **copyM = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    copyM[i] = new double[cols];
    for (int j = 0; j < cols; ++j) {
      copyM[i][j] = M[i][j];
    }
  }
  try {
    double determinate = calcDeterminate(copyM, rows, cols);
    deleteMatrix(copyM, rows);
    if (determinate == 0) {
      throw "singular";
    }
  } catch (const char *error) {
    throw error;
  }

  double **expandedMatrix = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    expandedMatrix[i] = new double[cols + cols];
    for (int j = 0; j < cols + cols; ++j) {
      if (j < cols) {
        expandedMatrix[i][j] = M[i][j];
      } else if (i == j - cols) {
        expandedMatrix[i][j] = 1;
      } else {
        expandedMatrix[i][j] = 0;
      }
    }
  }
  makeUpperTriangMatrix(expandedMatrix, rows, cols + cols);

  for (int col = rows - 1; col > 0; --col) {
    for (int row = col - 1; row >= 0; --row) {
      if (expandedMatrix[row][col] == 0) {
        continue;
      }
      double lineCoef = expandedMatrix[row][col];
      for (int elem = col; elem < cols + cols; ++elem) {
        expandedMatrix[row][elem] =
            expandedMatrix[row][elem] - expandedMatrix[col][elem] * lineCoef;
      }
    }
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      M[i][j] =
          (expandedMatrix[i][j + cols] == 0) ? 0 : expandedMatrix[i][j + cols];
    }
  }
  deleteMatrix(expandedMatrix, rows);
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout << "Not enough arguments";
    return 1;
  }

  std::ifstream inpFile(argv[2]);
  std::ofstream outFile(argv[3]);

  if (!outFile || !inpFile) {
    std::cout << "error opening file" << std::endl;
    return 2;
  }

  int rows;
  int cols;
  inpFile >> rows >> cols;

  double **matrix = new double *[rows];
  readMatrix(matrix, rows, cols, inpFile);

  if (strcmp(argv[1], "-det") == 0) {
    try {
      outFile << calcDeterminate(matrix, rows, cols);
    } catch (const char *error) {
      outFile << error;
    }
  } else if (strcmp(argv[1], "-inv") == 0) {
    try {
      calcInvert(matrix, rows, cols);
      outFile << rows << " " << cols << "\n";
      writeMatrix(matrix, rows, cols, outFile);
    } catch (const char *error) {
      outFile << error;
    }
  }

  deleteMatrix(matrix, rows);
  inpFile.close();
  outFile.close();
  return 0;
}