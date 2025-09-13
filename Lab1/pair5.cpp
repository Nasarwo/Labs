#include <iostream>
#include <cstdlib>
using namespace std;

class Pair5 {
    double first;  // цена товара
    int second;    // количество

public:
    bool init(double a, int b) {
        if (a <= 0.0 || b <= 0) {
            cerr << "Ошибка: цена и количество должны быть положительными\n";
            return false;
        }
        first = a; second = b; return true;
    }
    bool read() {
        double a; int b;
        cout << "Введите цену и количество: ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }
    void display() const {
        cout << "Товар: цена = " << first
             << " руб, количество = " << second
             << ", стоимость = " << cost() << " руб\n";
    }
    double cost() const {
        return first * second;
    }
};

// фабричная функция
Pair5 make_Pair5(double a, int b) {
    Pair5 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair5\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. фабричная функция
    Pair5 a = make_Pair5(99.9, 3);

    // 2. через init
    Pair5 b; b.init(15.5, 10);

    // 3. ввод с клавиатуры
    Pair5 c; c.read();

    a.display(); b.display(); c.display();
    cout << "a.cost() = " << a.cost() << "\n";
    cout << "b.cost() = " << b.cost() << "\n";
    cout << "c.cost() = " << c.cost() << "\n";

    // 4. массив объектов
    Pair5 arr[2];
    arr[0].init(250.0, 2);
    arr[1] = make_Pair5(13.75, 8);
    cout << "arr[0].cost() = " << arr[0].cost() << "\n";
    cout << "arr[1].cost() = " << arr[1].cost() << "\n";

    // 5. динамический массив
    int n = 2;
    Pair5* dynArr = new Pair5[n];
    dynArr[0] = make_Pair5(7.5, 12);
    dynArr[1].init(1200.0, 1);
    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].cost() = " << dynArr[i].cost() << "\n";
    }
    delete[] dynArr;

    return 0;
}
