#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class Pair2 {
    double first;   // число
    double second;  // показатель степени

public:
    bool init(double a, double b) {
        if (a == 0.0 && b <= 0.0) {
            cerr << "Ошибка: 0 нельзя возводить в неположительную степень\n";
            return false;
        }
        first = a; second = b; return true;
    }
    bool read() {
        double a, b;
        cout << "Введите пару (double double): ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }
    void display() const {
        cout << "(" << first << ", " << second << ")\n";
    }
    double power() const {
        return pow(first, second);
    }
};

// фабричная функция
Pair2 make_Pair2(double a, double b) {
    Pair2 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair2\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. создание через фабричную функцию
    Pair2 a = make_Pair2(2.0, 3.5);

    // 2. через init
    Pair2 b; b.init(5.5, -2.0);

    // 3. ввод с клавиатуры
    Pair2 c; c.read();

    a.display(); b.display(); c.display();
    cout << "a.power() = " << a.power() << "\n";
    cout << "b.power() = " << b.power() << "\n";
    cout << "c.power() = " << c.power() << "\n";

    // 4. статический массив объектов
    Pair2 arr[2];
    arr[0].init(10.0, 0.5);
    arr[1] = make_Pair2(0.5, 3.0);
    cout << "arr[0].power() = " << arr[0].power() << "\n";
    cout << "arr[1].power() = " << arr[1].power() << "\n";

    // 5. динамический массив объектов
    int n = 2;
    Pair2* dynArr = new Pair2[n];
    dynArr[0] = make_Pair2(4.0, -1.5);
    dynArr[1].init(9.0, 0.0);
    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].power() = " << dynArr[i].power() << "\n";
    }
    delete[] dynArr;

    return 0;
}
