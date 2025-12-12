#include <iostream>
#include <concepts>

using namespace std;

template<typename T>
concept PalindromeNumberApplicable = std::integral<T>;

template <PalindromeNumberApplicable T>
constexpr auto isPalindromeNumber = [](T n) constexpr {
    if (n < 0) return false;
    if (n < 10) return true;

    T original = n;
    T reversed = 0;

    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }

    return original == reversed;
};

int main() {
    constexpr auto result1 = isPalindromeNumber<int>(121);
    constexpr auto result2 = isPalindromeNumber<int>(123);
    cout << "121 is palindrome: " << result1 << endl;
    cout << "123 is palindrome: " << result2 << endl;
    return 0;
}
