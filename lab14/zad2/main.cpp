#include <iostream>
#include <vector>
using namespace std;

int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = dungeon.size();
    int n = dungeon[0].size();

    vector dp(m, vector(n, 0));

    // последняя клетка
    dp[m-1][n-1] = max(1, 1 - dungeon[m-1][n-1]);

    // последний столбец
    for (int i = m - 2; i >= 0; i--) {
        dp[i][n-1] = max(1, dp[i+1][n-1] - dungeon[i][n-1]);
    }

    // последняя строка
    for (int j = n - 2; j >= 0; j--) {
        dp[m-1][j] = max(1, dp[m-1][j+1] - dungeon[m-1][j]);
    }

    // остальная таблица
    for (int i = m - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            int need = min(dp[i+1][j], dp[i][j+1]);
            dp[i][j] = max(1, need - dungeon[i][j]);
        }
    }

    return dp[0][0];
}

int main() {
    vector<vector<int>> dungeon = {
        {-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5}
    };

    cout << calculateMinimumHP(dungeon) << endl;
    return 0;
}
