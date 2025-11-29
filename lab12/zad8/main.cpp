#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int findStone(vector<int>& stones, int target) {
    int left = 0, right = stones.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (stones[mid] == target) {
            return mid;
        } else if (stones[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

bool canCross(vector<int>& stones) {
    int n = stones.size();
    
    int maxJump = n;
    bool dp[2000][2001];
    memset(dp, false, sizeof(dp));
    
    dp[0][1] = true;
    
    for (int i = 0; i < n; i++) {
        for (int jump = 1; jump <= maxJump; jump++) {
            if (!dp[i][jump]) {
                continue;
            }
            
            int currentPos = stones[i];
            
            for (int nextJump = (jump > 1 ? jump - 1 : 1); nextJump <= jump + 1; nextJump++) {
                int nextPos = currentPos + nextJump;
                
                int nextIndex = findStone(stones, nextPos);
                
                if (nextIndex != -1) {
                    if (nextIndex == n - 1) {
                        return true;
                    }
                    
                    if (nextJump <= maxJump) {
                        dp[nextIndex][nextJump] = true;
                    }
                }
            }
        }
    }
    
    for (int jump = 1; jump <= maxJump; jump++) {
        if (dp[n - 1][jump]) {
            return true;
        }
    }
    
    return false;
}

int main() {
    cout << "=== Задача о лягушке ===" << endl;
    cout << "Лягушка перепрыгивает через реку по камням." << endl;
    cout << "Первый камень всегда на позиции 0." << endl << endl;
    
    cout << "Введите количество камней (от 2 до 2000): ";
    int n;
    cin >> n;
    
    if (n < 2 || n > 2000) {
        cout << "Ошибка: количество камней должно быть от 2 до 2000!" << endl;
        return 1;
    }
    
    vector<int> stones(n);
    cout << "Введите позиции камней (отсортированные по возрастанию):" << endl;
    cout << "Первый камень (позиция 0): ";
    cin >> stones[0];
    
    if (stones[0] != 0) {
        cout << "Предупреждение: первый камень должен быть на позиции 0. Установлено 0." << endl;
        stones[0] = 0;
    }
    
    for (int i = 1; i < n; i++) {
        cout << "Камень " << (i + 1) << ": ";
        cin >> stones[i];
    }
    
    bool sorted = true;
    for (int i = 1; i < n; i++) {
        if (stones[i] <= stones[i-1]) {
            sorted = false;
            break;
        }
    }
    
    if (!sorted) {
        cout << "Ошибка: позиции должны быть строго возрастающими!" << endl;
        return 1;
    }
    
    cout << endl << "Позиции камней: ";
    for (int i = 0; i < n; i++) {
        cout << stones[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl;
    
    bool result = canCross(stones);
    cout << "Результат: " << (result ? "true" : "false") << endl;
    cout << (result ? "Лягушка может перепрыгнуть реку!" : "Лягушка не может перепрыгнуть реку.") << endl;
    
    return 0;
}

