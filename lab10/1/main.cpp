#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <iterator>

using namespace std;

template<typename T>
class Deque {
private:
    deque<T> data;
public:
    Deque() = default;
    ~Deque() = default;
    void enqueue(const T& value);
    auto dequeue() -> typename decltype(data)::value_type;
    auto size() const -> typename decltype(data)::size_type;
    auto toString() const -> string;
    void clear();

    template<typename U>
    friend ostream& operator<<(ostream& os, const Deque<U>& dq);

    template<typename U>
    friend istream& operator>>(istream& is, Deque<U>& dq);
};

template<typename T>
void Deque<T>::enqueue(const T& value) {
    data.push_back(value);
}

template<typename T>
auto Deque<T>::dequeue() -> typename decltype(data)::value_type {
    const auto front = data.front();
    data.pop_front();
    return front;
}

template<typename T>
auto Deque<T>::size() const -> typename decltype(data)::size_type {
    return data.size();
}

template<typename T>
auto Deque<T>::toString() const -> string {
    if (data.empty()) {
        return "[]";
    }
    
    stringstream ss;
    ss << "[";
    for (auto it = data.cbegin(); it != data.cend(); ++it) {
        ss << *it;
        if (std::next(it) != data.cend()) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

template<typename T>
void Deque<T>::clear() {
    data.clear();
}

template<typename T>
ostream& operator<<(ostream& os, const Deque<T>& dq) {
    os << dq.toString();
    return os;
}

template<typename T>
istream& operator>>(istream& is, Deque<T>& dq) {
    dq.clear();
    string line;
    getline(is, line);
    
    stringstream ss(line);
    using ValueType = typename decltype(dq.data)::value_type;
    auto value = ValueType{};
    while (ss >> value) {
        dq.enqueue(value);
    }
    return is;
}

int main() {
    Deque<int> dq;
    
    cout << "=== Проверка чтения из потока (operator>>) ===" << endl;
    cout << "Введите числа через пробел для добавления в очередь: ";
    cin >> dq;
    
    cout << "\n=== Проверка размера (size) ===" << endl;
    cout << "Размер очереди: " << dq.size() << endl;
    
    cout << "\n=== Проверка toString ===" << endl;
    cout << "Содержимое через toString: " << dq.toString() << endl;
    
    cout << "\n=== Проверка вывода в поток (operator<<) ===" << endl;
    cout << "Вывод в поток: " << dq << endl;
    
    cout << "\n=== Проверка метода enqueue ===" << endl;
    cout << "Введите число для добавления в очередь: ";
    auto valueToEnqueue = int{};
    cin >> valueToEnqueue;
    dq.enqueue(valueToEnqueue);
    cout << "Добавлен элемент " << valueToEnqueue << " через enqueue. Размер: " << dq.size() << endl;
    cout << "Содержимое: " << dq << endl;
    
    int count;
    cout << "\n=== Проверка метода dequeue ===" << endl;
    cout << "Сколько элементов удалить из очереди? ";
    cin >> count;
    cin.ignore();
    
    cout << "Удаление элементов:" << endl;
    for (int i = 0; i < count && dq.size() > 0; i++) {
        cout << "  Удален элемент: " << dq.dequeue() << endl;
    }
    cout << "После удаления размер: " << dq.size() << endl;
    cout << "Содержимое: " << dq << endl;
    
    cout << "\n=== Вторая проверка чтения из потока ===" << endl;
    cout << "Введите числа через пробел для второй очереди: ";
    Deque<int> dq2;
    cin >> dq2;
    cout << "Прочитано: " << dq2 << endl;
    
    cout << "\n=== Проверка метода clear ===" << endl;
    cout << "Размер перед очисткой: " << dq2.size() << endl;
    dq2.clear();
    cout << "Размер после очистки: " << dq2.size() << endl;
    cout << "Содержимое после очистки: " << dq2 << endl;
    
    return 0;
}