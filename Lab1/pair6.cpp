#include <iostream>
#include <cstdlib>
using namespace std;

class Pair6 {
    int first;      // калорийность на 100 г
    double second;  // масса продукта в килограммах

public:
    bool init(int a, double b) {
        if (a <= 0 || b <= 0.0) {
            cerr << "Ошибка: калорийность и масса должны быть положительными\n";
            return false;
        }
        first = a; second = b; return true;
    }
    bool read() {
        int a; double b;
        cout << "Введите калорийность на 100 г и массу (в кг): ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }
    void display() const {
        cout << "Продукт: " << second << " кг, "
            << first << " ккал/100г, "
            << "всего = " << power() << " ккал\n";
    }
    double power() const {
        return first * (second * 10);  // переводим кг -> г и считаем
    }
};

// фабричная функция
Pair6 make_Pair6(int a, double b) {
    Pair6 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair6\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. фабричная функция
    Pair6 a = make_Pair6(250, 0.3);   // 250 ккал/100г, 0.3 кг

    // 2. через init
    Pair6 b; b.init(120, 1.5);

    // 3. ввод с клавиатуры
    Pair6 c; c.read();

    a.display(); b.display(); c.display();
    cout << "a.power() = " << a.power() << "\n";
    cout << "b.power() = " << b.power() << "\n";
    cout << "c.power() = " << c.power() << "\n";

    // 4. массив объектов
    Pair6 arr[2];
    arr[0].init(90, 2.0);       // 90 ккал/100г, 2 кг
    arr[1] = make_Pair6(450, 0.25);
    cout << "arr[0].power() = " << arr[0].power() << "\n";
    cout << "arr[1].power() = " << arr[1].power() << "\n";

    // 5. динамический массив
    int n = 2;
    Pair6* dynArr = new Pair6[n];
    dynArr[0] = make_Pair6(300, 0.5);
    dynArr[1].init(200, 1.2);
    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].power() = " << dynArr[i].power() << "\n";
    }
    delete[] dynArr;

    return 0;
}
