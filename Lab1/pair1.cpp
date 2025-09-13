#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class Pair1 {
    double first;
    int second;

public:
    bool init(double a, int b) {
        if (a == 0.0 && b < 0) {
            cerr << "Ошибка: нельзя возвести 0 в отрицательную степень\n";
            return false;
        }
        first = a; second = b; return true;
    }
    bool read() {
        double a; int b;
        cout << "Введите пару (double int): ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }
    void display() const {
        cout << "(" << first << ", " << second << ")\n";
    }
    double power() const {
        return pow(first, double(second));
    }
};

Pair1 make_Pair1(double a, int b) {
    Pair1 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair1\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // через фабричную функцию
    Pair1 a = make_Pair1(2.0, 3);
    // через init
    Pair1 b; b.init(5.5, 2);
    // ввод с клавиатуры
    Pair1 c; c.read();

    a.display(); b.display(); c.display();
    cout << "a.power() = " << a.power() << "\n";
    cout << "b.power() = " << b.power() << "\n";
    cout << "c.power() = " << c.power() << "\n";

    // массив объектов
    Pair1 arr[2];
    arr[0].init(10.0, 0);
    arr[1] = make_Pair1(0.5, 3);
    cout << "arr[0].power() = " << arr[0].power() << "\n";
    cout << "arr[1].power() = " << arr[1].power() << "\n";

    // динамический массив
    int n = 2;
    Pair1* dynArr = new Pair1[n];
    dynArr[0] = make_Pair1(4.0, 2);
    dynArr[1].init(9.0, 0);
    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].power() = " << dynArr[i].power() << "\n";
    }
    delete[] dynArr;

    return 0;
}
