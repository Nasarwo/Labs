#include <iostream>

using namespace std;

template<typename... Conditions>
bool anyTrue(Conditions&&... conditions) {
    return (conditions || ...);
}

int main() {
    // Примеры использования
    cout << boolalpha;
    
    cout << "anyTrue(true, false, false) = " << anyTrue(true, false, false) << endl;
    cout << "anyTrue(false, false, false) = " << anyTrue(false, false, false) << endl;
    cout << "anyTrue(true, true, true) = " << anyTrue(true, true, true) << endl;
    cout << "anyTrue(false, true, false) = " << anyTrue(false, true, false) << endl;
    
    return 0;
}

