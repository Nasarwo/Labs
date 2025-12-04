#include <iostream>
#include <vector>
using namespace std;

class Kids {
public:
    static int candy(vector<int>& ratings);
};

int Kids::candy(vector<int>& ratings) {
    int n = ratings.size();
    vector candies(n, 1);

    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    int total = 0;
    for (int c : candies) {
        total += c;
    }

    return total;
}

int main() {
    int n;
    cout << "Введите количество детей: ";
    cin >> n;

    vector<int> ratings(n);
    cout << "Введите рейтинги: ";
    for (int i = 0; i < n; i++) {
        cin >> ratings[i];
    }

    cout << "Минимальное количество конфет: "
         << Kids::candy(ratings) << endl;

    return 0;
}
