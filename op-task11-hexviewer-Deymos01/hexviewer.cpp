#include <fstream>
#include <iostream>

void convertToHex(uint64_t code, int size, char* res) {
  res[size] = '\0';
  int index = size - 1;
  while (code > 0) {
    res[index--] = static_cast<char>(code % 16 + (code % 16 > 9 ? 55 : 48));
    code /= 16;
  }
  while (index >= 0) {
    res[index--] = '0';
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Not enough arguments" << std::endl;
    return 1;
  }

  std::ifstream inFile(argv[1], std::ios_base::binary);
  std::ofstream outFile(argv[2], std::ios_base::binary);

  if (!inFile || !outFile) {
    std::cerr << "Can't open file" << std::endl;
    inFile.close();
    outFile.close();
    return 2;
  }

  int64_t fromBegin = 0;
  unsigned char blockSymbols[16];
  char hexCode[11];
  int numSymb;

  while (inFile.peek() != EOF) {
    if (fromBegin != 0) {
      outFile << '\n';
    }
    convertToHex(fromBegin, 10, hexCode);
    outFile << hexCode << ": ";
    fromBegin += 16;

    numSymb = 0;
    for (int i = 0; i < 16; ++i) {
      if (i == 8) {
        outFile << "| ";
      }
      if (inFile.peek() != EOF) {
        blockSymbols[i] = inFile.get();
        convertToHex(blockSymbols[i], 2, hexCode);
        outFile << hexCode << " ";
        ++numSymb;
      } else {
        outFile << "   ";
      }
    }
    outFile << ' ';
    for (int i = 0; i < numSymb; ++i) {
      outFile << static_cast<char>(blockSymbols[i] < 32 ? '.' : blockSymbols[i]);
    }
  }

  inFile.close();
  outFile.close();
  return 0;
}