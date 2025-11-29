#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class NestedInteger {
private:
    bool isInteger;
    int integerValue;
    NestedInteger* listValue;
    int listSize;
    int listCapacity;

public:
    NestedInteger(int value);
    NestedInteger();
    ~NestedInteger();
    NestedInteger(const NestedInteger& other);
    NestedInteger& operator=(const NestedInteger& other);
    bool isInt() const;
    int getInteger() const;
    void setInteger(int value);
    void add(const NestedInteger& ni);
    int getListSize() const;
    const NestedInteger& getListElement(int index) const;
    void print() const;
};

NestedInteger::NestedInteger(int value) : isInteger(true), integerValue(value), listValue(nullptr), listSize(0), listCapacity(0) {}

NestedInteger::NestedInteger() : isInteger(false), listValue(nullptr), listSize(0), listCapacity(0) {}

NestedInteger::~NestedInteger() {
    if (listValue != nullptr) {
        delete[] listValue;
    }
}

NestedInteger::NestedInteger(const NestedInteger& other) : isInteger(other.isInteger), integerValue(other.integerValue), listSize(other.listSize), listCapacity(other.listCapacity) {
    if (other.isInteger) {
        listValue = nullptr;
    } else {
        listValue = new NestedInteger[listCapacity];
        for (int i = 0; i < listSize; ++i) {
            listValue[i] = other.listValue[i];
        }
    }
}

NestedInteger& NestedInteger::operator=(const NestedInteger& other) {
    if (this != &other) {
        if (listValue != nullptr) {
            delete[] listValue;
        }
        isInteger = other.isInteger;
        integerValue = other.integerValue;
        listSize = other.listSize;
        listCapacity = other.listCapacity;
        if (other.isInteger) {
            listValue = nullptr;
        } else {
            listValue = new NestedInteger[listCapacity];
            for (int i = 0; i < listSize; ++i) {
                listValue[i] = other.listValue[i];
            }
        }
    }
    return *this;
}

bool NestedInteger::isInt() const {
    return isInteger;
}

int NestedInteger::getInteger() const {
    return integerValue;
}

void NestedInteger::setInteger(int value) {
    if (listValue != nullptr) {
        delete[] listValue;
        listValue = nullptr;
    }
    isInteger = true;
    integerValue = value;
    listSize = 0;
    listCapacity = 0;
}

void NestedInteger::add(const NestedInteger& ni) {
    isInteger = false;
    if (listSize >= listCapacity) {
        int newCapacity = (listCapacity == 0) ? 1 : listCapacity * 2;
        NestedInteger* newList = new NestedInteger[newCapacity];
        for (int i = 0; i < listSize; ++i) {
            newList[i] = listValue[i];
        }
        if (listValue != nullptr) {
            delete[] listValue;
        }
        listValue = newList;
        listCapacity = newCapacity;
    }
    listValue[listSize] = ni;
    listSize++;
}

int NestedInteger::getListSize() const {
    return listSize;
}

const NestedInteger& NestedInteger::getListElement(int index) const {
    return listValue[index];
}

void NestedInteger::print() const {
    if (isInteger) {
        cout << integerValue;
    } else {
        cout << "[";
        for (int i = 0; i < listSize; ++i) {
            if (i > 0) cout << ",";
            listValue[i].print();
        }
        cout << "]";
    }
}

NestedInteger parse(const string& s, int& index);

bool isValidInput(const string& s) {
    for (char c : s) {
        if (!isdigit(c) && c != '[' && c != ']' && c != '-' && c != ',') {
            return false;
        }
    }
    return true;
}

NestedInteger deserialize(const string& s) {
    int index = 0;
    return parse(s, index);
}

NestedInteger parse(const string& s, int& index) {
    if (index < s.length() && s[index] == '[') {
        index++;
        NestedInteger result;
        
        if (index < s.length() && s[index] != ']') {
            while (true) {
                result.add(parse(s, index));
                
                if (index >= s.length() || s[index] == ']') {
                    break;
                }
                
                if (s[index] == ',') {
                    index++;
                }
            }
        }
        
        if (index < s.length() && s[index] == ']') {
            index++;
        }
        
        return result;
    } else {
        int sign = 1;
        if (index < s.length() && s[index] == '-') {
            sign = -1;
            index++;
        }
        
        int num = 0;
        bool hasDigit = false;
        while (index < s.length() && isdigit(s[index])) {
            hasDigit = true;
            num = num * 10 + (s[index] - '0');
            index++;
        }
        
        if (!hasDigit) {
            return NestedInteger(0);
        }
        
        return NestedInteger(sign * num);
    }
}

int main() {
    string s;
    cout << "Введите строку для десериализации: ";
    getline(cin, s);
    
    if (!isValidInput(s)) {
        cout << "Ошибка: строка содержит недопустимые символы. Разрешены только цифры, '[', ']', '-', и ','" << endl;
        return 1;
    }
    
    NestedInteger result = deserialize(s);
    cout << "Вывод: ";
    result.print();
    cout << endl;
    
    return 0;
}

