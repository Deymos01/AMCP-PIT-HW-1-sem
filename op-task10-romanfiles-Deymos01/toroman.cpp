#include <fstream>
#include <iostream>

#include "romanNumb.hpp"

void writeUntilDivider(std::ifstream &inFile, std::ofstream &outFile) {
  while (inFile.peek() != ' ' && inFile.peek() != EOF &&
         inFile.peek() != '\n') {
    outFile << static_cast<char>(inFile.get());
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Not enough arguments" << std::endl;
    return 1;
  }

  std::ifstream inFile(argv[1]);
  std::ofstream outFile(argv[2]);

  if (!inFile || !outFile) {
    std::cout << "Can't open file" << std::endl;
    inFile.close();
    outFile.close();
    return 2;
  }

  inFile >> std::noskipws;
  int number;
  char curr;
  while (inFile.peek() != EOF) {
    inFile >> curr;
    if ('0' <= curr && curr <= '9') {
      number = curr - '0';

      if (number == 0) {
        outFile << number;
        continue;
      }

      while (inFile.peek() != EOF && inFile.peek() != ' ' &&
             inFile.peek() != '\n' && inFile.peek() != ')' &&
             inFile.peek() != '-') {
        inFile >> curr;

        if (isdigit(curr) == 0) {
          outFile << number << curr;
          writeUntilDivider(inFile, outFile);
          number = 0;
        } else {
          number = number * 10 + curr - '0';
        }
      }

      if (number > 3999) {
        outFile << number;
        continue;
      }
      if (number != 0) {
        writeRomeNumb(number, outFile);
      }

    } else {
      outFile << curr;
      if (curr != ' ' && curr != '(' && curr != '\n') {
        writeUntilDivider(inFile, outFile);
      }
    }
  }

  inFile.close();
  outFile.close();
}