#include <iostream>
#include <string>

using namespace std;

template<typename String>
void concat_impl(string& result, String&& s) {
    result += std::forward<String>(s);
}

template<typename String, typename... Strings>
void concat_impl(string& result, String&& s, Strings&&... strings) {
    result += std::forward<String>(s);
    concat_impl(result, std::forward<Strings>(strings)...);
}

template<typename... Strings>
auto concat(Strings&&... strings) -> string {
    string result;
    concat_impl(result, std::forward<Strings>(strings)...);
    return result;
}

int main() {
    string s1, s2, s3;
    
    cout << "Введите первую строку: ";
    getline(cin, s1);
    
    cout << "Введите вторую строку: ";
    getline(cin, s2);
    
    cout << "Введите третью строку: ";
    getline(cin, s3);
    
    auto result = concat(s1, s2, s3);
    cout << "Результат объединения: " << result << endl;
    
    return 0;
}

