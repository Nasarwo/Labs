#include <iostream>
#include <cstdlib>
using namespace std;

class Pair3 {
    int first;   // числитель
    int second;  // знаменатель

public:
    bool init(int a, int b) {
        if (a < 0 || b <= 0) {
            cerr << "Ошибка: числитель и знаменатель должны быть положительными, знаменатель > 0\n";
            return false;
        }
        first = a; second = b; return true;
    }
    bool read() {
        int a, b;
        cout << "Введите дробь (числитель знаменатель): ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }
    void display() const {
        cout << first << "/" << second << "\n";
    }
    int ipart() const {
        return first / second;  // целая часть деления
    }
};

// фабричная функция
Pair3 make_Pair3(int a, int b) {
    Pair3 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair3\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. фабричная функция
    Pair3 a = make_Pair3(7, 3);

    // 2. через init
    Pair3 b; b.init(10, 4);

    // 3. ввод с клавиатуры
    Pair3 c; c.read();

    a.display(); b.display(); c.display();
    cout << "a.ipart() = " << a.ipart() << "\n";
    cout << "b.ipart() = " << b.ipart() << "\n";
    cout << "c.ipart() = " << c.ipart() << "\n";

    // 4. массив объектов
    Pair3 arr[2];
    arr[0].init(11, 2);
    arr[1] = make_Pair3(25, 7);
    cout << "arr[0].ipart() = " << arr[0].ipart() << "\n";
    cout << "arr[1].ipart() = " << arr[1].ipart() << "\n";

    // 5. динамический массив
    int n = 2;
    Pair3* dynArr = new Pair3[n];
    dynArr[0] = make_Pair3(100, 9);
    dynArr[1].init(13, 5);
    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].ipart() = " << dynArr[i].ipart() << "\n";
    }
    delete[] dynArr;

    return 0;
}
