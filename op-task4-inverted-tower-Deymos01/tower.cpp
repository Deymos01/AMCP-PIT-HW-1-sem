#include <iostream>
typedef long long LL;


int main() {
    LL n_apart, lastApartInBlock = 0, numberApartsOnFloor = 0, lastFloor = 0;
    std::cin >> n_apart;

    while (lastApartInBlock < n_apart) {
        ++numberApartsOnFloor;
        lastApartInBlock += numberApartsOnFloor * numberApartsOnFloor;
        lastFloor += numberApartsOnFloor;
    }

    LL firstApartInBlock = lastApartInBlock - numberApartsOnFloor * numberApartsOnFloor + 1;
    LL floorInBlock = (n_apart - firstApartInBlock) / numberApartsOnFloor + 1;
    LL resultFloor = lastFloor - (numberApartsOnFloor - floorInBlock);
    LL numberOnFloor = n_apart - (firstApartInBlock + (floorInBlock - 1) * numberApartsOnFloor) + 1;

    std::cout << resultFloor << " " << numberOnFloor;

    return 0;
}
