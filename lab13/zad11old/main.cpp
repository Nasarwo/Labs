#include <iostream>
#include <utility>
using namespace std;

template<typename T>
struct product_type {
    typedef typename std::remove_reference<T>::type type;
};

template<typename First, typename Second, typename... Rest>
struct product_type_multi {
    typedef decltype(typename product_type<First>::type() * typename product_type_multi<Second, Rest...>::type()) type;
};

template<typename First, typename Second>
struct product_type_multi<First, Second> {
    typedef decltype(typename product_type<First>::type() * typename product_type<Second>::type()) type;
};

template<typename T>
auto product(T&& arg) -> typename product_type<T>::type {
    return std::forward<T>(arg);
}

template<typename First, typename... Rest>
auto product(First&& first, Rest&&... rest) -> typename product_type_multi<First, Rest...>::type {
    return std::forward<First>(first) * product(std::forward<Rest>(rest)...);
}

int main() {
    cout << product(2, 3, 4) << endl;
    cout << product(1.5, 2.0, 3.0) << endl;
    cout << product(5) << endl;
    
    return 0;
}

