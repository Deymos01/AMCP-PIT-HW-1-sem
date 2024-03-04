#include <iostream>

#include "romanNumb.hpp"
#include "stack.hpp"

/*
Написать условие на \n в конце строки для замены этого символа на группу " = (число)"
*/

int romanToInt(char roman) {
  switch (roman) {
    case 'I':
      return 1;
    case 'V':
      return 5;
    case 'X':
      return 10;
    case 'L':
      return 50;
    case 'C':
      return 100;
    case 'D':
      return 500;
    case 'M':
      return 1000;
    default:
      return 0;
  }
}

char movePointer(std::ifstream &inFile, std::ofstream &outFile) {
  char curr;
  inFile >> curr;
  outFile << curr;
  return curr;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Not enough arguments" << std::endl;
    return 1;
  }

  std::ifstream inFile(argv[1]);
  std::ofstream outFile(argv[2]);
  inFile >> std::noskipws;

  stack<int> stNumbers;
  char curr;

  int n1;
  int n2;
  int res;
  int answer;

  while (inFile.peek() != EOF) {
    answer = 0;
    while (inFile.peek() != '\n' && inFile.peek() != EOF) {
      res = 0;
      curr = movePointer(inFile, outFile);
      while (romanToInt(curr) != 0) {
        n1 = romanToInt(curr);
        n2 = romanToInt(static_cast<char>(inFile.peek()));

        if (n2 != 0 && n2 > n1) {
          res = res + n2 - n1;
          movePointer(inFile, outFile);
        } else {
          res += n1;
        }
        curr = movePointer(inFile, outFile);
      }
      if (res != 0) {
        stNumbers.push(res);
      } else {
        if (curr == '+') {
          stNumbers.push(stNumbers.pop() + stNumbers.pop());
        } else if (curr == '-') {
          int tmp = stNumbers.pop();
          stNumbers.push(stNumbers.pop() - tmp);
        } else if (curr == '*') {
          stNumbers.push(stNumbers.pop() * stNumbers.pop());
        } else if (curr == '/') {
          int tmp = stNumbers.pop();
          stNumbers.push(stNumbers.pop() / tmp);
        }
      }
    }
    if (!stNumbers.empty()) {
      answer = stNumbers.pop();
    }
    outFile << " = ";
    if (answer < 1 || answer > 3999) {
      outFile << "ERR";
    } else {
      writeRomeNumb(answer, outFile);
    }
    if (inFile.peek() != EOF) {
      movePointer(inFile, outFile);
    }
  }

  inFile.close();
  outFile.close();
  return 0;
}