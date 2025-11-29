#include <iostream>

using namespace std;

template<typename... Args>
auto product(Args&&... args) {
    return (1 * ... * args);
}

int main() {
    // Примеры использования
    cout << product(2, 3, 4) << endl;           // 24
    cout << product(1.5, 2.0, 3.0) << endl;     // 9.0
    cout << product(5) << endl;                 // 5
    cout << product() << endl;                   // 1
    
    return 0;
}

