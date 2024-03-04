#include <iostream>
#include <string>
#include <algorithm>

bool isFebruaryError(const int &day, const int &month, const int &year) {
    return month == 2 && (day > (28 + static_cast<int>((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))));
}

bool isRightDate(const int &day, const int &month, const int &year) {
    if (1 <= day && day <= 31 && 1 <= month && month <= 12 && year > 0) {
        if (isFebruaryError(day, month, year)) {
            return false;
        }
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

int getNameDay(const int &day, const int &month, const int &year) {
    int a = (14 - month) / 12;
    int y = year - a;
    int m = month + 12 * a - 2;

    return (day + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;
}

int main() {
    std::string date;
    std::cin >> date;

    if(std::count(date.begin(), date.end(), '.') != 2){
        std::cout << "Unknown" << std::endl;
        return 0;
    }

    int firstComma = static_cast<int>(date.find('.'));
    int secondComma = static_cast<int>(date.find('.', firstComma + 1));

    std::string strDay = date.substr(0, firstComma);
    std::string strMonth = date.substr(firstComma + 1, secondComma - firstComma - 1);
    std::string strYear = date.substr(secondComma + 1, date.length() - secondComma + 1);

    try {
        int day = std::stoi(strDay);
        int month = std::stoi(strMonth);
        int year = std::stoi(strYear);
        if (isRightDate(day, month, year)) {
            int d = getNameDay(day, month, year);
            std::string daysOfWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                                         "Thursday", "Friday", "Saturday"};

            while (true) {
                ++year;
                if (getNameDay(day, month, year) == 5 && !isFebruaryError(day, month, year)) {
                    break;
                }
            }

            std::cout << daysOfWeek[d] << std::endl;
            std::cout << year << std::endl;

        } else {
            std::cout << "Unknown" << std::endl;
        }
    } catch (...) {
        std::cout << "Unknown" << std::endl;
    }
    return 0;
}