#include <cstring>
#include <fstream>
#include <iostream>

void writeSymbolsToFile(const char block[128], const signed char length, std::ofstream &outFile) {
    outFile << length;
    for (int i = 0; i < -static_cast<int>(length); ++i) {
        outFile << block[i];
    }
}


void encodeFile(std::ifstream &inFile, std::ofstream &outFile) {
    signed char length = 0;
    signed char currSymbol = -128;
    signed char lastSymbol;
    char blockSymbol[128];

    while (inFile.peek() != EOF) {
        lastSymbol = currSymbol;
        currSymbol = static_cast<signed char>(inFile.get());

        if (currSymbol == static_cast<signed char>(inFile.peek())) {
            if (length < 0) {
                outFile << length;
                for (int i = 0; i < -static_cast<int>(length); ++i) {
                    outFile << blockSymbol[i];
                }
                length = 1;
            } else if (length == 127) {
                outFile << length << currSymbol;
                length = 0;
            } else {
                ++length;
            }
        } else {
            if (currSymbol == lastSymbol && length == static_cast<signed char>(0)) {
                outFile << '\0' << currSymbol;
                length = 0;
            } else if (length > 0) {
                outFile << length << currSymbol;
                length = 0;
            } else {
                if (length == -128) {
                    writeSymbolsToFile(blockSymbol, length, outFile);
                    length = 0;
                }
                blockSymbol[-length] = currSymbol;
                --length;
            }
        }
    }
    if (length < 0) {
        writeSymbolsToFile(blockSymbol, length, outFile);
    }
}

void decodeFile(std::ifstream &inFile, std::ofstream &outFile) {
    while (inFile.peek() != EOF) {
        signed char number = static_cast<signed char>(inFile.get());
        char letter = static_cast<char>(inFile.get());

        outFile << letter;
        if (number > 0) {
            for (int i = 0; i < number; ++i) {
                outFile << letter;
            }
        } else {
            for (int i = 0; i < abs(number) - 1; ++i) {
                outFile << static_cast<char>(inFile.get());
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cout << "Not enough arguments." << std::endl;
        return 1;
    }

    std::ifstream inFile(argv[2], std::ios_base::binary);
    std::ofstream outFile(argv[3], std::ios_base::binary);

    if (!inFile || !outFile) {
        std::cout << "Can't open file" << std::endl;
        inFile.close();
        outFile.close();
        return 2;
    }

    if (std::strcmp(argv[1], "-e") == 0) {
        encodeFile(inFile, outFile);
    } else if (std::strcmp(argv[1], "-d") == 0) {
        decodeFile(inFile, outFile);
    } else {
        std::cout << "Wrong arguments" << std::endl;
        return -1;
    }

    inFile.close();
    outFile.close();
    return 0;
}