#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
using namespace std;

// ---------------------- STRUCT ----------------------
struct Date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

// ---------------------- ПРОТОТИПЫ ----------------------
bool isLeapYear(unsigned int year);
bool isValidDate(unsigned int y, unsigned int m, unsigned int d);
int daysInMonth(unsigned int y, unsigned int m);
Date createDate(unsigned int y, unsigned int m, unsigned int d);
Date createDateFromString(const string& s);
Date createDateFromDate(const Date& other);
void display(const Date& d);
string toString(const Date& d);
Date addDays(const Date& d, int days);
Date subtractDays(const Date& d, int days);
int daysBetween(const Date& d1, const Date& d2);
bool isEqual(const Date& d1, const Date& d2);
bool isLess(const Date& d1, const Date& d2);
bool isGreater(const Date& d1, const Date& d2);

// ---------------------- ФУНКЦИИ ----------------------
bool isLeapYear(unsigned int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(unsigned int y, unsigned int m, unsigned int d) {
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;
    return d <= daysInMonth(y, m);
}

int daysInMonth(unsigned int y, unsigned int m) {
    if (m == 2) return isLeapYear(y) ? 29 : 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

Date createDate(unsigned int y, unsigned int m, unsigned int d) {
    if (!isValidDate(y, m, d)) throw invalid_argument("Некорректная дата");
    return {y, m, d};
}

Date createDateFromString(const string& s) {
    istringstream iss(s);
    char dot1, dot2;
    unsigned int y, m, d;
    if ((iss >> y >> dot1 >> m >> dot2 >> d) && dot1 == '.' && dot2 == '.' && isValidDate(y, m, d)) {
        return {y, m, d};
    } else throw invalid_argument("Неверный формат даты");
}

Date createDateFromDate(const Date& other) {
    return {other.year, other.month, other.day};
}

void display(const Date& d) {
    cout << d.year << "." << (d.month < 10 ? "0" : "") << d.month
         << "." << (d.day < 10 ? "0" : "") << d.day;
}

string toString(const Date& d) {
    return to_string(d.year) + "." + to_string(d.month) + "." + to_string(d.day);
}

Date addDays(const Date& d, int days) {
    Date result = d;
    int direction = days > 0 ? 1 : -1;
    int remaining = abs(days);

    while (remaining--) {
        result.day += direction;
        if (result.day < 1) {
            result.month--;
            if (result.month < 1) {
                result.month = 12;
                result.year--;
            }
            result.day = daysInMonth(result.year, result.month);
        } else if (result.day > daysInMonth(result.year, result.month)) {
            result.day = 1;
            result.month++;
            if (result.month > 12) {
                result.month = 1;
                result.year++;
            }
        }
    }
    return result;
}

Date subtractDays(const Date& d, int days) {
    return addDays(d, -days);
}

int daysBetween(const Date& d1, const Date& d2) {
    auto toJulianDay = [](unsigned int y, unsigned int m, unsigned int d) {
        int a = (14 - m) / 12;
        int year = y + 4800 - a;
        int month = m + 12 * a - 3;
        return d + (153 * month + 2) / 5 + 365 * year + year / 4 - year / 100 + year / 400 - 32045;
    };
    int jd1 = toJulianDay(d1.year, d1.month, d1.day);
    int jd2 = toJulianDay(d2.year, d2.month, d2.day);
    return jd2 - jd1;
}

// Сравнения
bool isEqual(const Date& d1, const Date& d2) {
    return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day;
}

bool isLess(const Date& d1, const Date& d2) {
    if (d1.year != d2.year) return d1.year < d2.year;
    if (d1.month != d2.month) return d1.month < d2.month;
    return d1.day < d2.day;
}

bool isGreater(const Date& d1, const Date& d2) {
    return isLess(d2, d1);
}

// ---------------------- MAIN ----------------------
int main() {
    setlocale(LC_ALL, "");

    try {
        Date d1 = createDate(2023, 9, 20);
        Date d2 = addDays(d1, 15);

        cout << "Дата 1: ";
        display(d1);
        cout << "\nДата 2 (через 15 дней): ";
        display(d2);
        cout << "\nРазница: " << daysBetween(d1, d2) << " дней\n";

        if (isLess(d1, d2)) cout << "d1 раньше d2\n";
        else cout << "d1 позже или равна d2\n";

        Date d3 = subtractDays(d2, 40);
        cout << "Дата 3 (d2 - 40 дней): ";
        display(d3);
        cout << "\n";

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
