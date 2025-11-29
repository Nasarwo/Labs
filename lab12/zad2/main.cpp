#include <iostream>
#include <string>

using namespace std;

int lengthOfLongestSubstring(string s) {
    int n = s.length();
    if (n == 0) return 0;
    
    int charIndex[128];
    for (int i = 0; i < 128; i++) {
        charIndex[i] = -1;
    }
    
    int maxLength = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        if (charIndex[s[right]] != -1 && charIndex[s[right]] >= left) {
            left = charIndex[s[right]] + 1;
        }
        
        charIndex[s[right]] = right;
        
        int currentLength = right - left + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }
    
    return maxLength;
}

string longestSubstring(string s) {
    int n = s.length();
    if (n == 0) return "";
    
    int charIndex[128];
    for (int i = 0; i < 128; i++) {
        charIndex[i] = -1;
    }
    
    int maxLength = 0;
    int maxLeft = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        if (charIndex[s[right]] != -1 && charIndex[s[right]] >= left) {
            left = charIndex[s[right]] + 1;
        }
        
        charIndex[s[right]] = right;
        
        int currentLength = right - left + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
            maxLeft = left;
        }
    }
    
    return s.substr(maxLeft, maxLength);
}

int main() {
    string s1 = "abcabcbb";
    cout << "Ввод: s = \"" << s1 << "\"" << endl;
    cout << "Вывод: " << lengthOfLongestSubstring(s1) << endl;
    cout << "Пояснение: Ответ — \"abc\", длина 3." << endl << endl;
    
    string s2 = "bbbbb";
    cout << "Ввод: s = \"" << s2 << "\"" << endl;
    cout << "Вывод: " << lengthOfLongestSubstring(s2) << endl;
    cout << "Пояснение: Ответ — \"b\", длина 1." << endl << endl;
    
    string s3 = "pwwkew";
    cout << "Ввод: s = \"" << s3 << "\"" << endl;
    cout << "Вывод: " << lengthOfLongestSubstring(s3) << endl;
    cout << "Пояснение: Ответ — \"wke\", длина 3." << endl << endl;
    
    string s;
    cout << "Введите строку для проверки: ";
    getline(cin, s);
    string result = longestSubstring(s);
    cout << "Вывод: " << result.length() << endl;
    cout << "Подстрока: \"" << result << "\"" << endl;
    
    return 0;
}

