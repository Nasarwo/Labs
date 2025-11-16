#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

template<typename T>
class Optional {
private:
    bool has_value{false};
    T value{};

public:
    Optional() = default;
    ~Optional() = default;
    auto hasValue() const -> bool;
    auto getValue() const -> const decltype(value)&;
    void setValue(const decltype(value)& val);
    auto toString() const -> std::string;

    template<typename U>
    friend ostream& operator<<(ostream& os, const Optional<U>& opt);

    template<typename U>
    friend istream& operator>>(istream& is, Optional<U>& opt);
};

template<typename T>
auto Optional<T>::hasValue() const -> bool {
    return has_value;
}

template<typename T>
auto Optional<T>::getValue() const -> const decltype(value)& {
    if (!has_value) {
        throw runtime_error("Optional value is not set");
    }
    return value;
}

template<typename T>
void Optional<T>::setValue(const decltype(value)& val) {
    value = val;
    has_value = true;
}

template<typename T>
auto Optional<T>::toString() const -> std::string {
    if (!has_value) {
        return "null";
    }
    auto ss = stringstream{};
    ss << value;
    return ss.str();
}

template<typename T>
ostream& operator<<(ostream& os, const Optional<T>& opt) {
    os << opt.toString();
    return os;
}

template<typename T>
istream& operator>>(istream& is, Optional<T>& opt) {
    const auto peek = is.peek();
    if (peek == EOF || is.eof()) {
        opt.has_value = false;
        return is;
    }
    auto val = decltype(opt.value){};
    if (is >> val && is.good()) {
        opt.setValue(val);
    } else {
        opt.has_value = false;
        is.clear();
    }
    return is;
}

int main() {
    Optional<int> opt;

    cout << "=== Проверка hasValue ===" << endl;
    cout << "Значение установлено: " << (opt.hasValue() ? "да" : "нет") << endl;

    cout << "\n=== Проверка setValue ===" << endl;
    opt.setValue(42);
    cout << "После setValue(42), hasValue: " << (opt.hasValue() ? "да" : "нет") << endl;

    cout << "\n=== Проверка getValue ===" << endl;
    cout << "Значение: " << opt.getValue() << endl;

    cout << "\n=== Проверка toString ===" << endl;
    cout << "Содержимое через toString: " << opt.toString() << endl;

    cout << "\n=== Проверка вывода в поток (operator<<) ===" << endl;
    cout << "Вывод в поток: " << opt << endl;

    cout << "\n=== Проверка чтения из потока (operator>>) ===" << endl;
    cout << "Введите число: ";
    Optional<int> opt2;
    cin >> opt2;
    cout << "Прочитано: " << opt2 << endl;
    cout << "hasValue: " << (opt2.hasValue() ? "да" : "нет") << endl;
    if (opt2.hasValue()) {
        cout << "Значение: " << opt2.getValue() << endl;
    }

    cout << "\n=== Проверка создания пустого Optional ===" << endl;
    Optional<int> opt3;
    cout << "Пустой Optional: " << opt3 << endl;
    cout << "hasValue: " << (opt3.hasValue() ? "да" : "нет") << endl;

    cout << "\n=== Проверка изменения значения ===" << endl;
    opt3.setValue(100);
    cout << "После setValue(100): " << opt3 << endl;
    opt3.setValue(200);
    cout << "После setValue(200): " << opt3 << endl;

    return 0;
}
