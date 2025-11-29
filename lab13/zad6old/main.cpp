#include <iostream>

using namespace std;

bool anyTrue() {
    return false;
}

template<typename First, typename... Rest>
bool anyTrue(First&& first, Rest&&... rest) {
    return static_cast<bool>(first) || anyTrue(std::forward<Rest>(rest)...);
}

int main() {
    cout << boolalpha;
    
    cout << "anyTrue(false, false, false): " 
         << anyTrue(false, false, false) << endl;
    
    cout << "anyTrue(false, true, false): " 
         << anyTrue(false, true, false) << endl;
    
    cout << "anyTrue(true, true, true): " 
         << anyTrue(true, true, true) << endl;
    
    cout << "anyTrue(false): " 
         << anyTrue(false) << endl;
    
    cout << "anyTrue(true): " 
         << anyTrue(true) << endl;
    
    cout << "anyTrue(): " 
         << anyTrue() << endl;
    
    cout << "anyTrue(0, 0, 5): " 
         << anyTrue(0, 0, 5) << endl;
    
    return 0;
}

