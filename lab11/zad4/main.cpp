#include <iostream>

using namespace std;

int sbor(int* height, int n) {
    if (n <= 2) {
        return 0;
    }
    
    int left = 0;
    int right = n - 1;
    int leftMax = 0;
    int rightMax = 0;
    int water = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    
    return water;
}

int main() {
    // Пример 1
    int height1[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Пример 1: [0,1,0,2,1,0,1,3,2,1,2,1]" << endl;
    cout << "Результат: " << sbor(height1, 12) << endl;
    cout << "Ожидается: 6" << endl << endl;
    
    // Пример 2
    int height2[] = {4, 2, 0, 3, 2, 5};
    cout << "Пример 2: [4,2,0,3,2,5]" << endl;
    cout << "Результат: " << sbor(height2, 6) << endl;
    cout << "Ожидается: 9" << endl << endl;
    
    // Пример 3
    cout << "Пример 3 - ручной ввод" << endl;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    
    int* height3 = new int[n];
    cout << "Введите " << n << " элементов (высоты): ";
    for (int i = 0; i < n; i++) {
        cin >> height3[i];
    }
    
    cout << "Введенный массив: [";
    for (int i = 0; i < n; i++) {
        cout << height3[i];
        if (i < n - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
    cout << "Результат: " << sbor(height3, n) << endl << endl;
    
    delete[] height3;
    return 0;
}

