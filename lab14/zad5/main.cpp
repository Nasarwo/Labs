#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int s, e, p;
};

int main() {
    int n;
    cout << "Введите количество заданий: ";
    cin >> n;

    vector<int> startTime(n), endTime(n), profit(n);

    cout << "Введите массив startTime (" << n << " чисел): ";
    for (int i = 0; i < n; i++) cin >> startTime[i];

    cout << "Введите массив endTime (" << n << " чисел): ";
    for (int i = 0; i < n; i++) cin >> endTime[i];

    cout << "Введите массив profit (" << n << " чисел): ";
    for (int i = 0; i < n; i++) cin >> profit[i];

    vector<Job> jobs(n);
    for (int i = 0; i < n; i++) {
        jobs[i] = { startTime[i], endTime[i], profit[i] };
    }

    // сортировка по времени окончания
    sort(jobs.begin(), jobs.end(),
         [](const Job &a, const Job &b) {
             return a.e < b.e;
         });

    vector<long long> dp(n);
    dp[0] = jobs[0].p;

    for (int i = 1; i < n; i++) {

        long long includeProfit = jobs[i].p;

        int l = 0, r = i - 1, pos = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (jobs[mid].e <= jobs[i].s) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if (pos != -1) includeProfit += dp[pos];

        dp[i] = max(dp[i - 1], includeProfit);
    }

    cout << "Максимальная прибыль: " << dp[n - 1] << endl;

    return 0;
}
