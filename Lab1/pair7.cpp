#include <iostream>
#include <cstdlib>
using namespace std;

class Pair7 {
    double first;   // левая граница
    double second;  // правая граница

public:
    bool init(double a, double b) {
        if (a > b) {
            cerr << "Ошибка: левая граница не может быть больше правой\n";
            return false;
        }
        first = a; second = b; return true;
    }
    bool read() {
        double a, b;
        cout << "Введите левую и правую границы диапазона: ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }
    void display() const {
        cout << "Диапазон: [" << first << ", " << second << "]\n";
    }
    bool rangecheck(double x) const {
        return (x >= first && x <= second);
    }
};

// фабричная функция
Pair7 make_Pair7(double a, double b) {
    Pair7 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair7\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. фабричная функция
    Pair7 a = make_Pair7(0.0, 10.0);

    // 2. через init
    Pair7 b; b.init(-5.0, 5.0);

    // 3. ввод с клавиатуры
    Pair7 c; c.read();

    a.display(); b.display(); c.display();

    double x;
    cout << "Введите число для проверки: ";
    cin >> x;

    cout << "a.rangecheck(" << x << ") = " << (a.rangecheck(x) ? "Да" : "Нет") << "\n";
    cout << "b.rangecheck(" << x << ") = " << (b.rangecheck(x) ? "Да" : "Нет") << "\n";
    cout << "c.rangecheck(" << x << ") = " << (c.rangecheck(x) ? "Да" : "Нет") << "\n";

    // 4. массив объектов
    Pair7 arr[2];
    arr[0].init(1.5, 2.5);
    arr[1] = make_Pair7(-10.0, -1.0);

    cout << "arr[0].rangecheck(" << x << ") = " << (arr[0].rangecheck(x) ? "Да" : "Нет") << "\n";
    cout << "arr[1].rangecheck(" << x << ") = " << (arr[1].rangecheck(x) ? "Да" : "Нет") << "\n";

    // 5. динамический массив
    int n = 2;
    Pair7* dynArr = new Pair7[n];
    dynArr[0] = make_Pair7(100.0, 200.0);
    dynArr[1].init(-50.0, 0.0);

    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].rangecheck(" << x << ") = "
            << (dynArr[i].rangecheck(x) ? "Да" : "Нет") << "\n";
    }
    delete[] dynArr;

    return 0;
}
