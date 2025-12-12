#include <iostream>
#include <string>
#include <string_view>
#include <concepts>

using namespace std;

template<typename T>
concept Parseable = std::integral<T> || std::floating_point<T>;

template <Parseable T>
constexpr auto parseNumber = [](string_view str) constexpr {
    if (str.empty()) return T(0);

    T result = 0;
    bool negative = false;
    size_t start = 0;

    if (str[0] == '-') {
        negative = true;
        start = 1;
    }

    for (size_t i = start; i < str.size(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            break;
        }
    }

    return negative ? -result : result;
};

int main() {
    constexpr string_view str1 = "12345";
    constexpr string_view str2 = "-678";
    constexpr auto num1 = parseNumber<int>(str1);
    constexpr auto num2 = parseNumber<int>(str2);
    cout << "Parsed '12345': " << num1 << endl;
    cout << "Parsed '-678': " << num2 << endl;
    return 0;
}
