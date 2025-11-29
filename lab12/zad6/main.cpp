#include <iostream>
using namespace std;

int min(int a, int b) {
    return a < b ? a : b;
}

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    int n = triangleSize;
    
    int* dp = new int[n];
    for (int i = 0; i < n; i++) {
        dp[i] = triangle[n - 1][i];
    }
    
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
        }
    }
    
    int result = dp[0];
    delete[] dp;
    return result;
}

int main() {
    int n;
    cout << "Введите количество строк в треугольнике: ";
    cin >> n;
    
    int** triangle = new int*[n];
    int* triangleColSize = new int[n];
    
    for (int i = 0; i < n; i++) {
        triangleColSize[i] = i + 1;
        triangle[i] = new int[i + 1];
        cout << "Введите " << (i + 1) << " элементов для строки " << (i + 1) << ": ";
        for (int j = 0; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }
    
    cout << "Минимальная сумма пути: " << minimumTotal(triangle, n, triangleColSize) << endl;
    
    for (int i = 0; i < n; i++) {
        delete[] triangle[i];
    }
    delete[] triangle;
    delete[] triangleColSize;
    
    return 0;
}

