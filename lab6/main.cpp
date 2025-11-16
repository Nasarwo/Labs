#include <iostream>
#include <cmath>
using namespace std;

class Pair {
protected:
    double a, b;

public:
    Pair(double a = 0, double b = 0);

    void setA(double value);
    void setB(double value);
    double getA() const;
    double getB() const;
    double multiply() const;
};

class RightAngled : public Pair {
public:
    RightAngled(double catet1 = 0, double catet2 = 0);

    double hypotenuse() const;
    double area() const;
};

Pair::Pair(double a, double b) : a(a), b(b) {}

void Pair::setA(double value) { a = value; }
void Pair::setB(double value) { b = value; }

double Pair::getA() const { return a; }
double Pair::getB() const { return b; }

double Pair::multiply() const { return a * b; }

RightAngled::RightAngled(double catet1, double catet2) : Pair(catet1, catet2) {}

double RightAngled::hypotenuse() const {
    return sqrt(a * a + b * b);
}

double RightAngled::area() const {
    return 0.5 * a * b;
}

int main() {
    double catet1, catet2;

    cout << "Введите первый катет: ";
    cin >> catet1;
    cout << "Введите второй катет: ";
    cin >> catet2;

    RightAngled triangle(catet1, catet2);

    cout << "\nКатеты: " << triangle.getA() << " и " << triangle.getB() << endl;
    cout << "Произведение катетов: " << triangle.multiply() << endl;
    cout << "Гипотенуза: " << triangle.hypotenuse() << endl;
    cout << "Площадь: " << triangle.area() << endl;

    return 0;
}
