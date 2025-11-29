#include <iostream>
#include <tuple>

using namespace std;

template<typename... Args>
auto maxOf(Args&&... args) {
    auto result = get<0>(forward_as_tuple(args...));
    ((result = (result < args ? args : result)), ...);
    return result;
}

int main() {
    cout << "=== Автоматические тесты ===" << endl;
    cout << "maxOf(1, 2, 3) = " << maxOf(1, 2, 3) << endl;
    cout << "maxOf(5.5, 2.3, 8.9, 1.1) = " << maxOf(5.5, 2.3, 8.9, 1.1) << endl;
    cout << "maxOf(10, 20) = " << maxOf(10, 20) << endl;
    cout << "maxOf(42) = " << maxOf(42) << endl;
    cout << "maxOf(-5, -2, -10, -1) = " << maxOf(-5, -2, -10, -1) << endl;
    
    cout << "\n=== Ручной тест ===" << endl;
    int a, b, c;
    cout << "Введите три целых числа: ";
    cin >> a >> b >> c;
    cout << "maxOf(" << a << ", " << b << ", " << c << ") = " << maxOf(a, b, c) << endl;
    
    double x, y, z, w;
    cout << "\nВведите четыре вещественных числа: ";
    cin >> x >> y >> z >> w;
    cout << "maxOf(" << x << ", " << y << ", " << z << ", " << w << ") = " << maxOf(x, y, z, w) << endl;
    
    return 0;
}

