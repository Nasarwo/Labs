#include <iostream>
#include <cstdlib>
using namespace std;

class Pair9 {
    int first;   // часы
    int second;  // минуты

public:
    bool init(int h, int m) {
        if (h < 0 || m < 0 || m >= 60) {
            cerr << "Ошибка: часы должны быть >= 0, минуты в диапазоне [0, 59]\n";
            return false;
        }
        first = h;
        second = m;
        return true;
    }

    bool read() {
        int h, m;
        cout << "Введите время (часы минуты): ";
        if (!(cin >> h >> m)) return false;
        return init(h, m);
    }

    void display() const {
        cout << "Время: " << first << " ч " << second << " мин\n";
    }

    int minutes() const {
        return first * 60 + second;
    }
};

// фабричная функция
Pair9 make_Pair9(int h, int m) {
    Pair9 p;
    if (!p.init(h, m)) {
        cerr << "Ошибка: недопустимые аргументы для Pair9\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. создание через фабричную функцию
    Pair9 a = make_Pair9(2, 30);

    // 2. создание через init()
    Pair9 b; b.init(1, 45);

    // 3. ввод с клавиатуры
    Pair9 c; c.read();

    a.display(); cout << "В минутах: " << a.minutes() << "\n";
    b.display(); cout << "В минутах: " << b.minutes() << "\n";
    c.display(); cout << "В минутах: " << c.minutes() << "\n";

    // 4. массив объектов
    Pair9 arr[2];
    arr[0].init(0, 15);
    arr[1] = make_Pair9(3, 0);

    cout << "arr[0] = " << arr[0].minutes() << " мин\n";
    cout << "arr[1] = " << arr[1].minutes() << " мин\n";

    // 5. динамический массив
    int n = 2;
    Pair9* dynArr = new Pair9[n];
    dynArr[0] = make_Pair9(10, 5);
    dynArr[1].init(23, 59);

    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "В минутах: " << dynArr[i].minutes() << "\n";
    }

    delete[] dynArr;
    return 0;
}
