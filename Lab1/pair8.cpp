#include <iostream>
#include <cstdlib>
using namespace std;

class Pair8 {
    int first;   // левая граница (включается)
    int second;  // правая граница (не включается)

public:
    bool init(int a, int b) {
        if (a >= b) {
            cerr << "Ошибка: левая граница должна быть меньше правой\n";
            return false;
        }
        first = a;
        second = b;
        return true;
    }

    bool read() {
        int a, b;
        cout << "Введите левую и правую границы интервала [a, b): ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }

    void display() const {
        cout << "Интервал: [" << first << ", " << second << ")\n";
    }

    bool rangecheck(int x) const {
        return (x >= first && x < second);
    }
};

// фабричная функция
Pair8 make_Pair8(int a, int b) {
    Pair8 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair8\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. фабричная функция
    Pair8 a = make_Pair8(0, 10);

    // 2. init()
    Pair8 b; b.init(-3, 3);

    // 3. ввод с клавиатуры
    Pair8 c; c.read();

    a.display(); b.display(); c.display();

    int x;
    cout << "Введите число для проверки: ";
    cin >> x;

    cout << "a.rangecheck(" << x << ") = " << (a.rangecheck(x) ? "Да" : "Нет") << "\n";
    cout << "b.rangecheck(" << x << ") = " << (b.rangecheck(x) ? "Да" : "Нет") << "\n";
    cout << "c.rangecheck(" << x << ") = " << (c.rangecheck(x) ? "Да" : "Нет") << "\n";

    // 4. массив объектов
    Pair8 arr[2];
    arr[0].init(5, 15);
    arr[1] = make_Pair8(-10, -5);

    cout << "arr[0].rangecheck(" << x << ") = " << (arr[0].rangecheck(x) ? "Да" : "Нет") << "\n";
    cout << "arr[1].rangecheck(" << x << ") = " << (arr[1].rangecheck(x) ? "Да" : "Нет") << "\n";

    // 5. динамический массив
    int n = 2;
    Pair8* dynArr = new Pair8[n];
    dynArr[0] = make_Pair8(100, 200);
    dynArr[1].init(-50, 0);

    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].rangecheck(" << x << ") = "
             << (dynArr[i].rangecheck(x) ? "Да" : "Нет") << "\n";
    }

    delete[] dynArr;
    return 0;
}
