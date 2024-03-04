#include <iostream>

int main() {
    int digits[] = {1000, 900, 500, 400, 100, 90, 50, 40,
                    10,9, 5, 4, 1};
    const char* romeDigs[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL",
                              "X", "IX", "V", "IV", "I"};

    int n;
    std::cin >> n;

    for (int i = 0; i < 13; ++i){
        while (n - digits[i] >= 0){
            std::cout << romeDigs[i];
            n -= digits[i];
        }
    }

    return 0;
}
