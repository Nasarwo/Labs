#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Pair10 {
    double first;   // коэффициент A
    double second;  // коэффициент B

public:
    bool init(double a, double b) {
        if (isnan(a) || isnan(b) || isinf(a) || isinf(b)) {
            cerr << "Ошибка: недопустимые коэффициенты\n";
            return false;
        }
        first = a;
        second = b;
        return true;
    }

    bool read() {
        double a, b;
        cout << "Введите коэффициенты A и B: ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }

    void display() const {
        cout << "Уравнение: y = " << first << " * x + " << second << "\n";
    }

    double function(double x) const {
        return first * x + second;
    }
};

// фабричная функция
Pair10 make_Pair10(double a, double b) {
    Pair10 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair10\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. фабричная функция
    Pair10 a = make_Pair10(2.5, 1.0);

    // 2. init()
    Pair10 b; b.init(-1.0, 3.0);

    // 3. ввод с клавиатуры
    Pair10 c; c.read();

    a.display(); cout << "При x=2 → y=" << a.function(2) << "\n";
    b.display(); cout << "При x=2 → y=" << b.function(2) << "\n";
    c.display(); cout << "При x=2 → y=" << c.function(2) << "\n";

    // 4. массив объектов
    Pair10 arr[2];
    arr[0].init(0.5, -1.0);
    arr[1] = make_Pair10(1.0, 0.0);

    cout << "arr[0]: y(4) = " << arr[0].function(4) << "\n";
    cout << "arr[1]: y(4) = " << arr[1].function(4) << "\n";

    // 5. динамический массив
    int n = 2;
    Pair10* dynArr = new Pair10[n];
    dynArr[0] = make_Pair10(10.0, 5.0);
    dynArr[1].init(-2.0, 7.0);

    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "При x=1 → y=" << dynArr[i].function(1) << "\n";
    }

    delete[] dynArr;
    return 0;
}
