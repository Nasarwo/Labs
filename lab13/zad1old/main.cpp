#include <iostream>
#include <algorithm>
#include <type_traits>

using namespace std;

template<typename T>
T maxOf(T&& arg) {
    return arg;
}

template<typename T, typename U, typename... Args>
auto maxOf(T&& a, U&& b, Args&&... args) -> typename common_type<T, U, Args...>::type {
    return maxOf(max(a, b), args...);
}

int main() {
    double a, b, c, d, e;
    cout << "Введите 5 чисел: ";
    cin >> a >> b >> c >> d >> e;
    cout << "Максимум: " << maxOf(a, b, c, d, e) << endl;
    
    return 0;
}

