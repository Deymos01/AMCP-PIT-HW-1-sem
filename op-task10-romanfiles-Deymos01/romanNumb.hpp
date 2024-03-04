#ifndef OP_TASK10_ROMANFILES_DEYMOS01_ROMANNUMB_HPP
#define OP_TASK10_ROMANFILES_DEYMOS01_ROMANNUMB_HPP
#include <fstream>

void writeRomeNumb(int number, std::ofstream &outFile) {
  int digits[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  const char *romeDigs[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                            "XL", "X",  "IX", "V",  "IV", "I"};

  for (int i = 0; i < 13; ++i) {
    while (number - digits[i] >= 0) {
      outFile << romeDigs[i];
      number -= digits[i];
    }
  }
}

#endif  // OP_TASK10_ROMANFILES_DEYMOS01_ROMANNUMB_HPP
