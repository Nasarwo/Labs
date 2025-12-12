#include <iostream>
#include <concepts>

using namespace std;

template<typename T>
concept GCDApplicable = std::integral<T>;

template <GCDApplicable T>
constexpr auto gcd = [](T a, T b) constexpr {
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
};

int main() {
    constexpr auto result = gcd<int>(48, 18);
    cout << "GCD(48, 18) = " << result << endl;
    return 0;
}
