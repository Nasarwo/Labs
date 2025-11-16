#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string decodeString(string s, int& index) {
    string result = "";
    int num = 0;
    
    while (index < s.length()) {
        if (isdigit(s[index])) {
            num = num * 10 + (s[index] - '0');
            index++;
        } else if (s[index] == '[') {
            index++; // пропускаем '['
            string decoded = decodeString(s, index); // рекурсивно декодируем содержимое
            // index уже указывает на символ после ']' после возврата из рекурсии
            
            // Повторяем декодированную строку num раз
            for (int i = 0; i < num; i++) {
                result += decoded;
            }
            num = 0; // сбрасываем число
        } else if (s[index] == ']') {
            // Возвращаемся на уровень выше
            index++; // переходим на символ после ']'
            return result;
        } else {
            // Обычная буква
            result += s[index];
            index++;
        }
    }
    
    return result;
}

string decodeString(string s) {
    int index = 0;
    return decodeString(s, index);
}

int main() {
    cout << "=== Декодер закодированных строк ===" << endl;
    cout << endl;
    cout << "Введите закодированную строку в формате:" << endl;
    cout << "  - Число перед квадратными скобками означает повторение" << endl;
    cout << "  - Примеры: 3[a] -> aaa, 2[ab] -> abab, 3[a2[bc]] -> abcbcabcbcabcbc" << endl;
    cout << endl;
    cout << "Введите строку: ";
    
    string s;
    cin >> s;
    
    cout << endl;
    cout << "Результат декодирования: " << decodeString(s) << endl;
    
    return 0;
}


