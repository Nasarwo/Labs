#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Octal {
public:
    Octal();
    Octal(unsigned long long value);
    Octal(const string& value);
    size_t size() const;
    string toString() const;
    bool operator==(const Octal& other) const;
    bool operator<(const Octal& other) const;
    Octal operator+(const Octal& other) const;
    Octal operator-(const Octal& other) const;
    Octal& operator+=(const Octal& other);
    Octal& operator-=(const Octal& other);
    friend istream& operator>>(istream& in, Octal& value);
    friend ostream& operator<<(ostream& out, const Octal& value);
private:
    static const size_t kMaxDigits = 100;
    unsigned char digits[kMaxDigits];
    size_t length;
    void normalize();
    void fromString(const string& value);
};

class BitString {
public:
    BitString();
    BitString(size_t len, unsigned char value);
    BitString(const string& value);
    size_t size() const;
    void setBit(size_t index, unsigned char value);
    unsigned char getBit(size_t index) const;
    string toString() const;
    BitString operator&(const BitString& other) const;
    BitString operator|(const BitString& other) const;
    BitString operator^(const BitString& other) const;
    BitString operator~() const;
    BitString shiftLeft(size_t count) const;
    BitString shiftRight(size_t count) const;
    friend istream& operator>>(istream& in, BitString& value);
    friend ostream& operator<<(ostream& out, const BitString& value);
private:
    static const size_t kMaxBits = 100;
    unsigned char bits[kMaxBits];
    size_t length;
    void checkLength(size_t len) const;
};

Octal::Octal() : digits(), length(1) {
    for (size_t i = 0; i < kMaxDigits; ++i) {
        digits[i] = 0;
    }
}

Octal::Octal(unsigned long long value) : Octal() {
    size_t index = 0;
    while (value > 0 && index < kMaxDigits) {
        digits[index++] = static_cast<unsigned char>(value % 8);
        value /= 8;
    }
    if (value > 0) {
        throw overflow_error("Переполнение восьмеричного числа");
    }
    length = index > 0 ? index : 1;
}

Octal::Octal(const string& value) : Octal() {
    fromString(value);
}

size_t Octal::size() const {
    return length;
}

string Octal::toString() const {
    string result;
    for (size_t i = 0; i < length; ++i) {
        result.push_back(static_cast<char>('0' + digits[length - 1 - i]));
    }
    return result;
}

bool Octal::operator==(const Octal& other) const {
    if (length != other.length) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool Octal::operator<(const Octal& other) const {
    if (length != other.length) {
        return length < other.length;
    }
    for (size_t i = length; i > 0; --i) {
        if (digits[i - 1] != other.digits[i - 1]) {
            return digits[i - 1] < other.digits[i - 1];
        }
    }
    return false;
}

Octal Octal::operator+(const Octal& other) const {
    Octal result;
    unsigned char carry = 0;
    size_t maxLen = length > other.length ? length : other.length;
    for (size_t i = 0; i < maxLen || carry; ++i) {
        if (i >= kMaxDigits) {
            throw overflow_error("Переполнение восьмеричного числа");
        }
        unsigned char sum = carry;
        if (i < length) {
            sum += digits[i];
        }
        if (i < other.length) {
            sum += other.digits[i];
        }
        result.digits[i] = sum % 8;
        carry = sum / 8;
        result.length = i + 1;
    }
    result.normalize();
    return result;
}

Octal Octal::operator-(const Octal& other) const {
    if (*this < other) {
        throw invalid_argument("Результат отрицательный");
    }
    Octal result;
    unsigned char borrow = 0;
    for (size_t i = 0; i < length; ++i) {
        int diff = digits[i] - borrow;
        if (i < other.length) {
            diff -= other.digits[i];
        }
        if (diff < 0) {
            diff += 8;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = static_cast<unsigned char>(diff);
        result.length = i + 1;
    }
    result.normalize();
    return result;
}

Octal& Octal::operator+=(const Octal& other) {
    *this = *this + other;
    return *this;
}

Octal& Octal::operator-=(const Octal& other) {
    *this = *this - other;
    return *this;
}

istream& operator>>(istream& in, Octal& value) {
    string input;
    in >> input;
    value.fromString(input);
    return in;
}

ostream& operator<<(ostream& out, const Octal& value) {
    out << value.toString();
    return out;
}

void Octal::normalize() {
    while (length > 1 && digits[length - 1] == 0) {
        --length;
    }
}

void Octal::fromString(const string& value) {
    if (value.empty() || value.size() > kMaxDigits) {
        throw invalid_argument("Некорректная восьмеричная строка");
    }
    for (size_t i = 0; i < kMaxDigits; ++i) {
        digits[i] = 0;
    }
    length = 0;
    size_t start = 0;
    while (start < value.size() - 1 && value[start] == '0') {
        ++start;
    }
    for (size_t i = value.size(); i > start; --i) {
        char c = value[i - 1];
        if (c < '0' || c > '7') {
            throw invalid_argument("Недопустимая восьмеричная цифра");
        }
        digits[length++] = static_cast<unsigned char>(c - '0');
        if (length > kMaxDigits) {
            throw overflow_error("Переполнение восьмеричного числа");
        }
    }
    if (length == 0) {
        length = 1;
    }
    normalize();
}

BitString::BitString() : bits(), length(0) {
    for (size_t i = 0; i < kMaxBits; ++i) {
        bits[i] = 0;
    }
}

BitString::BitString(size_t len, unsigned char value) : BitString() {
    checkLength(len);
    length = len;
    unsigned char bit = value ? 1 : 0;
    for (size_t i = 0; i < len; ++i) {
        bits[i] = bit;
    }
}

BitString::BitString(const string& value) : BitString() {
    checkLength(value.size());
    length = value.size();
    for (size_t i = 0; i < value.size(); ++i) {
        char c = value[value.size() - 1 - i];
        if (c != '0' && c != '1') {
            throw invalid_argument("Недопустимый бит");
        }
        bits[i] = static_cast<unsigned char>(c - '0');
    }
}

size_t BitString::size() const {
    return length;
}

void BitString::setBit(size_t index, unsigned char value) {
    if (index >= length) {
        throw out_of_range("Недопустимый индекс бита");
    }
    bits[index] = value ? 1 : 0;
}

unsigned char BitString::getBit(size_t index) const {
    if (index >= length) {
        throw out_of_range("Недопустимый индекс бита");
    }
    return bits[index];
}

string BitString::toString() const {
    if (length == 0) {
        return "0";
    }
    string result;
    for (size_t i = 0; i < length; ++i) {
        result.push_back(static_cast<char>('0' + bits[length - 1 - i]));
    }
    return result;
}

BitString BitString::operator&(const BitString& other) const {
    BitString result;
    size_t newLen = length > other.length ? length : other.length;
    result.length = newLen;
    for (size_t i = 0; i < newLen; ++i) {
        unsigned char left = i < length ? bits[i] : 0;
        unsigned char right = i < other.length ? other.bits[i] : 0;
        result.bits[i] = left & right;
    }
    return result;
}

BitString BitString::operator|(const BitString& other) const {
    BitString result;
    size_t newLen = length > other.length ? length : other.length;
    result.length = newLen;
    for (size_t i = 0; i < newLen; ++i) {
        unsigned char left = i < length ? bits[i] : 0;
        unsigned char right = i < other.length ? other.bits[i] : 0;
        result.bits[i] = left | right;
    }
    return result;
}

BitString BitString::operator^(const BitString& other) const {
    BitString result;
    size_t newLen = length > other.length ? length : other.length;
    result.length = newLen;
    for (size_t i = 0; i < newLen; ++i) {
        unsigned char left = i < length ? bits[i] : 0;
        unsigned char right = i < other.length ? other.bits[i] : 0;
        result.bits[i] = left ^ right;
    }
    return result;
}

BitString BitString::operator~() const {
    BitString result;
    result.length = length;
    for (size_t i = 0; i < length; ++i) {
        result.bits[i] = bits[i] ? 0 : 1;
    }
    return result;
}

BitString BitString::shiftLeft(size_t count) const {
    if (count == 0 || length == 0) {
        return *this;
    }
    BitString result;
    size_t newLen = length + count;
    if (newLen > kMaxBits) {
        newLen = kMaxBits;
    }
    result.length = newLen;
    for (size_t i = newLen; i > count; --i) {
        size_t src = i - count - 1;
        if (src < length) {
            result.bits[i - 1] = bits[src];
        } else {
            result.bits[i - 1] = 0;
        }
    }
    for (size_t i = 0; i < count && i < newLen; ++i) {
        result.bits[i] = 0;
    }
    return result;
}

BitString BitString::shiftRight(size_t count) const {
    if (count == 0 || length == 0) {
        return *this;
    }
    if (count >= length) {
        return BitString();
    }
    BitString result;
    result.length = length - count;
    for (size_t i = 0; i < result.length; ++i) {
        result.bits[i] = bits[i + count];
    }
    return result;
}

istream& operator>>(istream& in, BitString& value) {
    string input;
    in >> input;
    value = BitString(input);
    return in;
}

ostream& operator<<(ostream& out, const BitString& value) {
    out << value.toString();
    return out;
}

void BitString::checkLength(size_t len) const {
    if (len > kMaxBits) {
        throw invalid_argument("Слишком длинная битовая строка");
    }
}

int main() {
    Octal a("157");
    Octal b(123);
    Octal c = a + b;
    Octal d = c - Octal("10");
    cout << "значение a: " << a << endl;
    cout << "значение b: " << b << endl;
    cout << "результат c = a + b: " << c << endl;
    cout << "результат d = c - 10: " << d << endl;
    BitString bs1("101101");
    BitString bs2("001111");
    cout << "битовая строка bs1: " << bs1 << endl;
    cout << "битовая строка bs2: " << bs2 << endl;
    cout << "bs1 & bs2: " << (bs1 & bs2) << endl;
    cout << "bs1 | bs2: " << (bs1 | bs2) << endl;
    cout << "bs1 ^ bs2: " << (bs1 ^ bs2) << endl;
    cout << "инверсия bs1: " << (~bs1) << endl;
    cout << "bs1 << 2: " << bs1.shiftLeft(2) << endl;
    cout << "bs2 >> 1: " << bs2.shiftRight(1) << endl;
    return 0;
}
