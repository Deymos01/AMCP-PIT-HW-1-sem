typedef long long LL;

#include <iostream>

void convertNumberAndPrint(LL number, short base) {
    if (!number)
        return;
    convertNumberAndPrint(number / base, base);
    std::cout << char(number % base + (number % base > 9 ? 55 : 48));
}

int main() {
    LL n;
    std::cin >> n;
    short p;
    std::cin >> p;

    convertNumberAndPrint(n, p);

    return 0;
}