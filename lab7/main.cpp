#include <iostream>
#include <stdexcept>
using namespace std;

class Complex {
private:
    double a;
    double b;

public:
    Complex();
    Complex(double real, double imag);

    void input();
    void print() const;
    Complex operator/(const Complex& other) const;
};

Complex::Complex() : a(0), b(0) {}
Complex::Complex(double real, double imag) : a(real), b(imag) {}

void Complex::input() {
    cout << "Введите действительную часть: ";
    cin >> a;
    cout << "Введите мнимую часть: ";
    cin >> b;
}

void Complex::print() const {
    cout << "(" << a << ", " << b << ")";
}

Complex Complex::operator/(const Complex& other) const {
    if (other.a == 0 && other.b == 0)
        throw invalid_argument("Ошибка: деление на ноль.");

    double denom = other.a * other.a + other.b * other.b;
    double realNumerator = a * other.a + b * other.b;
    double imagNumerator = b * other.a - a * other.b;

    return Complex(realNumerator / denom, imagNumerator / denom);
}

int main() {
    Complex A, B, C;

    cout << "Введите комплексное число A\n";
    A.input();

    cout << "\nВведите комплексное число B\n";
    B.input();

    try {
        C = A / B;
        cout << "\nРезультат деления A / B = ";
        C.print();
        cout << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "\nПерехвачено исключение: " << e.what() << endl;
    }

    return 0;
}
