#include <iostream>
#include <cstdlib>
using namespace std;

class Pair4 {
    int first;   // номинал купюры
    int second;  // количество купюр

    // вспомогательная проверка корректности номинала
    bool isValidNominal(int x) {
        return x == 1 || x == 2 || x == 5 || x == 10 ||
               x == 50 || x == 100 || x == 500 ||
               x == 1000 || x == 5000;
    }

public:
    bool init(int a, int b) {
        if (!isValidNominal(a) || b <= 0) {
            cerr << "Ошибка: номинал или количество некорректны\n";
            return false;
        }
        first = a; second = b; return true;
    }
    bool read() {
        int a, b;
        cout << "Введите номинал и количество: ";
        if (!(cin >> a >> b)) return false;
        return init(a, b);
    }
    void display() const {
        cout << "Купюра " << first << " руб × " << second
             << " шт = " << summa() << " руб\n";
    }
    int summa() const {
        return first * second;
    }
};

// фабричная функция
Pair4 make_Pair4(int a, int b) {
    Pair4 p;
    if (!p.init(a, b)) {
        cerr << "Ошибка: недопустимые аргументы для Pair4\n";
        exit(EXIT_FAILURE);
    }
    return p;
}

int main() {
    // 1. фабричная функция
    Pair4 a = make_Pair4(100, 3);   // 300 руб

    // 2. через init
    Pair4 b; b.init(5000, 2);       // 10000 руб

    // 3. ввод с клавиатуры
    Pair4 c; c.read();

    a.display(); b.display(); c.display();
    cout << "a.summa() = " << a.summa() << "\n";
    cout << "b.summa() = " << b.summa() << "\n";
    cout << "c.summa() = " << c.summa() << "\n";

    // 4. массив объектов
    Pair4 arr[2];
    arr[0].init(50, 10);
    arr[1] = make_Pair4(1000, 7);
    cout << "arr[0].summa() = " << arr[0].summa() << "\n";
    cout << "arr[1].summa() = " << arr[1].summa() << "\n";

    // 5. динамический массив
    int n = 2;
    Pair4* dynArr = new Pair4[n];
    dynArr[0] = make_Pair4(10, 25);
    dynArr[1].init(500, 4);
    for (int i = 0; i < n; i++) {
        dynArr[i].display();
        cout << "dynArr[" << i << "].summa() = " << dynArr[i].summa() << "\n";
    }
    delete[] dynArr;

    return 0;
}
