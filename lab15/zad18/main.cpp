#include <iostream>
#include <string>
#include <string_view>

using namespace std;

constexpr auto isPalindromeString = [](string_view str) constexpr {
    size_t left = 0;
    size_t right = str.size();
    if (right == 0) return true;
    --right;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
};

int main() {
    constexpr string_view str1 = "racecar";
    constexpr string_view str2 = "hello";
    constexpr auto result1 = isPalindromeString(str1);
    constexpr auto result2 = isPalindromeString(str2);
    cout << "'racecar' is palindrome: " << result1 << endl;
    cout << "'hello' is palindrome: " << result2 << endl;
    return 0;
}
