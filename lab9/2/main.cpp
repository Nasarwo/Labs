#include <iostream>
using namespace std;

// Шаблонная функция сравнения
template<typename T>
bool compare(const T& a, const T& b) {
    return a == b;
}

template<typename T>
class TArrayManager {
private:
    T* array1;
    T* array2;
    int size1;
    int size2;
public:
    TArrayManager(int s1 = 3, int s2 = 3);
    ~TArrayManager();
    void inputArrays();
    void print() const;
    T* concatenateArrays(const T* arr1, int size1, const T* arr2, int size2);
    void printArray(const T* arr, int size, const string& name) const;
    void deleteArray(T* arr);
    void demonstrateCompare();
};

template<typename T>
TArrayManager<T>::TArrayManager(int s1, int s2) {
    size1 = s1;
    size2 = s2;
    array1 = new T[size1];
    array2 = new T[size2];

    for (int i = 0; i < size1; i++)
        array1[i] = T{};
    for (int i = 0; i < size2; i++)
        array2[i] = T{};
}

template<typename T>
TArrayManager<T>::~TArrayManager() {
    delete[] array1;
    delete[] array2;
}

template<typename T>
void TArrayManager<T>::inputArrays() {
    cout << "\n=== Ввод данных пользователем ===" << endl;
    cout << "Введите размер первого массива: ";
    cin >> size1;
    delete[] array1;
    array1 = new T[size1];
    cout << "Введите " << size1 << " элементов первого массива: ";
    for (int i = 0; i < size1; i++)
        cin >> array1[i];

    cout << "Введите размер второго массива: ";
    cin >> size2;
    delete[] array2;
    array2 = new T[size2];
    cout << "Введите " << size2 << " элементов второго массива: ";
    for (int i = 0; i < size2; i++)
        cin >> array2[i];

    cout << "\nВведенные массивы:" << endl;
    print();

    cout << "\nРезультат склеивания:" << endl;
    T* result = concatenateArrays(array1, size1, array2, size2);
    printArray(result, size1 + size2, "Склеенный массив");
    deleteArray(result);
}

template<typename T>
void TArrayManager<T>::print() const {
    cout << "Первый массив: ";
    for (int i = 0; i < size1; i++)
        cout << array1[i] << " ";
    cout << endl;

    cout << "Второй массив: ";
    for (int i = 0; i < size2; i++)
        cout << array2[i] << " ";
    cout << endl;
}

template<typename T>
T* TArrayManager<T>::concatenateArrays(const T* arr1, int size1, const T* arr2, int size2) {
    T* result = new T[size1 + size2];

    for (int i = 0; i < size1; ++i) {
        result[i] = arr1[i];
    }

    for (int i = 0; i < size2; ++i) {
        result[size1 + i] = arr2[i];
    }

    return result;
}

template<typename T>
void TArrayManager<T>::printArray(const T* arr, int size, const string& name) const {
    cout << name << ": [";
    for (int i = 0; i < size; ++i) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

template<typename T>
void TArrayManager<T>::deleteArray(T* arr) {
    delete[] arr;
}

template<typename T>
void TArrayManager<T>::demonstrateCompare() {
    cout << "\n=== Демонстрация функции сравнения ===" << endl;

    // Сравнение элементов массивов
    cout << "Сравнение элементов массивов:" << endl;
    for (int i = 0; i < min(size1, size2); i++) {
        bool result = compare(array1[i], array2[i]);
        cout << "array1[" << i << "] = " << array1[i]
             << " == array2[" << i << "] = " << array2[i]
             << " -> " << (result ? "true" : "false") << endl;
    }

    // Сравнение с константными значениями
    cout << "\nСравнение с константными значениями:" << endl;
    T testValue = T{};
    cout << "Сравнение с нулевым значением:" << endl;
    for (int i = 0; i < size1; i++) {
        bool result = compare(array1[i], testValue);
        cout << "array1[" << i << "] == 0 -> " << (result ? "true" : "false") << endl;
    }
}

int main() {
    cout << "=== Шаблонная функция сравнения ===" << endl;
    cout << "Демонстрация работы с разными типами данных:" << endl;

    cout << "\n=== Тестирование с целыми числами ===" << endl;
    TArrayManager<int> intTest;
    intTest.inputArrays();
    intTest.demonstrateCompare();

    cout << "\n=== Тестирование с числами с плавающей точкой ===" << endl;
    TArrayManager<double> doubleTest;
    doubleTest.inputArrays();
    doubleTest.demonstrateCompare();

    cout << "\n=== Тестирование со строками ===" << endl;
    TArrayManager<string> stringTest;
    stringTest.inputArrays();
    stringTest.demonstrateCompare();

    // Дополнительные примеры использования функции compare
    cout << "\n=== Дополнительные примеры функции compare ===" << endl;

    // --- Сравнение целых чисел ---
    int a, b, c;
    cout << "Введите три целых числа (a, b, c): ";
    cin >> a >> b >> c;

    cout << "compare(" << a << ", " << b << ") = " << (compare(a, b) ? "true" : "false") << endl;
    cout << "compare(" << a << ", " << c << ") = " << (compare(a, c) ? "true" : "false") << endl;

    // --- Сравнение строк ---
    string str1, str2, str3;
    cout << "\nВведите три строки (str1, str2, str3): ";
    cin >> str1 >> str2 >> str3;

    cout << "compare(\"" << str1 << "\", \"" << str2 << "\") = "
         << (compare(str1, str2) ? "true" : "false") << endl;
    cout << "compare(\"" << str1 << "\", \"" << str3 << "\") = "
         << (compare(str1, str3) ? "true" : "false") << endl;

    // --- Сравнение чисел с плавающей точкой ---
    double d1, d2, d3;
    cout << "\nВведите три числа с плавающей точкой (d1, d2, d3): ";
    cin >> d1 >> d2 >> d3;

    cout << "compare(" << d1 << ", " << d2 << ") = " << (compare(d1, d2) ? "true" : "false") << endl;
    cout << "compare(" << d1 << ", " << d3 << ") = " << (compare(d1, d3) ? "true" : "false") << endl;

    return 0;
}
