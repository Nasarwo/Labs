#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>

using namespace std;

class Date {
private:
    unsigned int year, month, day;

    static bool isValidDate(unsigned int y, unsigned int m, unsigned int d) {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > 31) return false;

        int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (isLeapYear(y)) daysInMonth[1] = 29;
        return d <= daysInMonth[m - 1];
    }

public:
    // --- Конструкторы ---
    Date() : year(0), month(0), day(0) {}
    Date(unsigned int y, unsigned int m, unsigned int d) : year(y), month(m), day(d) {
        if (!isValidDate(y, m, d)) throw invalid_argument("Invalid date");
    }
    Date(const Date& other) : year(other.year), month(other.month), day(other.day) {}

    // --- Инициализация ---
    void initFromString(const string& s) {
        istringstream iss(s);
        char dot1, dot2;
        unsigned int y, m, d;
        if ((iss >> y >> dot1 >> m >> dot2 >> d) && dot1 == '.' && dot2 == '.' && isValidDate(y, m, d)) {
            year = y; month = m; day = d;
        } else throw invalid_argument("Invalid string format");
    }

    void initFromDate(const Date& other) {
        year = other.year; month = other.month; day = other.day;
    }

    // --- Геттеры ---
    unsigned int getYear() const { return year; }
    unsigned int getMonth() const { return month; }
    unsigned int getDay() const { return day; }

    // --- Сеттеры ---
    void setYear(unsigned int y) {
        if (isValidDate(y, month, day)) year = y;
        else throw invalid_argument("Invalid year");
    }
    void setMonth(unsigned int m) {
        if (isValidDate(year, m, day)) month = m;
        else throw invalid_argument("Invalid month");
    }
    void setDay(unsigned int d) {
        if (isValidDate(year, month, d)) day = d;
        else throw invalid_argument("Invalid day");
    }

    // --- Статические методы ---
    static bool isLeapYear(unsigned int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int daysInMonth(unsigned int y, unsigned int m) {
        if (m == 2) return isLeapYear(y) ? 29 : 28;
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
        return 31;
    }

    // --- Основные методы ---
    Date addDays(int days) const;
    Date subtractDays(int days) const;
    int daysBetween(const Date& other) const;

    // --- Операторы сравнения ---
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
};

// ================== Реализация методов ==================

Date Date::addDays(int days) const {
    if (days == 0) return *this;
    Date result = *this;
    int direction = (days > 0) ? 1 : -1;
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
        }
        else if (result.day > daysInMonth(result.year, result.month)) {
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

Date Date::subtractDays(int days) const {
    return addDays(-days);
}

int Date::daysBetween(const Date& other) const {
    auto toJulianDay = [](unsigned int y, unsigned int m, unsigned int d) {
        int a = (14 - m) / 12;
        int yy = y + 4800 - a;
        int mm = m + 12 * a - 3;
        return d + (153 * mm + 2) / 5 + 365 * yy + yy / 4 - yy / 100 + yy / 400 - 32045;
    };
    int jd1 = toJulianDay(year, month, day);
    int jd2 = toJulianDay(other.year, other.month, other.day);
    return jd2 - jd1;
}

// --- Операторы сравнения ---
bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}
bool Date::operator!=(const Date& other) const { return !(*this == other); }
bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}
bool Date::operator>(const Date& other) const { return other < *this; }
bool Date::operator<=(const Date& other) const { return !(other < *this); }
bool Date::operator>=(const Date& other) const { return !(*this < other); }

// ================== MAIN ==================
int main() {
    setlocale(LC_ALL, "");

    try {
        Date d1(2024, 3, 1);
        Date d2 = d1.addDays(-1); // 29 февраля 2024
        Date d3 = d1.addDays(2);  // 3 марта 2024

        cout << "d1: " << d1.getYear() << "." << d1.getMonth() << "." << d1.getDay() << "\n";
        cout << "d2: " << d2.getYear() << "." << d2.getMonth() << "." << d2.getDay() << "\n";
        cout << "d3: " << d3.getYear() << "." << d3.getMonth() << "." << d3.getDay() << "\n";

        Date a(2025, 9, 19);
        Date b(2026, 1, 1);
        cout << "Дней между a->b: " << a.daysBetween(b) << "\n";

        Date s;
        s.initFromString("2004.08.31");
        cout << "Строка: " << s.getYear() << "." << s.getMonth() << "." << s.getDay() << "\n";

        if (a < b) cout << "a раньше чем b\n";
        else cout << "b раньше чем a\n";

        // --- Ввод от пользователя ---
        cout << "\nВведите дату (ГГГГ.ММ.ДД): ";
        string input;
        cin >> input;

        Date userDate;
        userDate.initFromString(input);

        cout << "Вы ввели: " << userDate.getYear() << "."
             << userDate.getMonth() << "." << userDate.getDay() << "\n";

        cout << "Введите количество дней для сдвига: ";
        int shift;
        cin >> shift;

        Date shifted = userDate.addDays(shift);
        cout << "Результат: " << shifted.getYear() << "."
             << shifted.getMonth() << "." << shifted.getDay() << "\n";

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}