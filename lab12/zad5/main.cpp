#include <iostream>
using namespace std;

void sortColors(int nums[], int n) {
    int left = 0;
    int right = n - 1;
    int current = 0;
    
    while (current <= right) {
        if (nums[current] == 0) {
            swap(nums[current], nums[left]);
            left++;
            current++;
        } else if (nums[current] == 2) {
            swap(nums[current], nums[right]);
            right--;
        } else {
            current++;
        }
    }
}

void printArray(int nums[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << nums[i];
        if (i < n - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

int main() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    
    int nums[300];
    cout << "Введите элементы массива (0, 1 или 2): ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    cout << "Ввод: ";
    printArray(nums, n);
    
    sortColors(nums, n);
    
    cout << "Вывод: ";
    printArray(nums, n);
    
    return 0;
}
