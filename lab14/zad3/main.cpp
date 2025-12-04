#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

string reduceBoard(const string &s) {
    string t = s;
    bool changed = true;
    while (changed) {
        changed = false;
        string tmp;
        for (int i = 0; i < (int)t.size();) {
            int j = i;
            while (j < (int)t.size() && t[j] == t[i]) j++;
            if (j - i >= 3) {
                changed = true; // удаляем этот блок
            } else {
                tmp.append(t.substr(i, j - i));
            }
            i = j;
        }
        t = move(tmp);
    }
    return t;
}

unordered_map<string,int> memo;

int dfs(string board, unordered_map<char,int> &hand) {
    board = reduceBoard(board);
    if (board.empty()) return 0;

    // ключ: board + encoded hand
    string key = board + "#";
    for (auto &p : hand) {
        if (p.second > 0) {
            key.push_back(p.first);
            key += to_string(p.second);
        }
    }

    if (memo.count(key)) return memo[key];

    int ans = numeric_limits<int>::max();

    for (int i = 0; i < (int)board.size(); ++i) {
        int j = i;
        while (j < (int)board.size() && board[j] == board[i]) ++j;
        int need = 3 - (j - i); // сколько шаров нужно вставить, чтобы взорвать этот блок
        char c = board[i];
        if (need <= 0) continue; // уже >=3 (по условию исходно таких нет, но после рекурсии возможно)

        if (hand[c] >= need) {
            hand[c] -= need;
            string next = board.substr(0, i) + board.substr(j);
            int sub = dfs(next, hand);
            if (sub != -1) ans = min(ans, sub + need);
            hand[c] += need;
        }
    }

    memo[key] = (ans == numeric_limits<int>::max() ? -1 : ans);
    return memo[key];
}

int findMinStep(string board, string handStr) {
    unordered_map<char,int> hand;
    for (char c : handStr) ++hand[c];
    memo.clear();
    return dfs(board, hand);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Zuma Game Solver ===\n";
    cout << "Разрешённые цвета: R Y B G W\n\n";

    string board, hand;
    if (!(cin >> board >> hand)) return 0;
    cout << findMinStep(board, hand) << '\n';
    return 0;
}
