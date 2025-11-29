#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Использую algorithm, чтобы в очередной раз не реализовывать min и max

const int MAX_REPEATS = 20;

class PasswordChecker {
private:
    string password;
    
    int countMissingTypes();
    int findRepeats(int repeats[]);
    int handleShortPassword(int missingTypes, int repeats[], int repeatsCount);
    int handleLongPassword(int missingTypes, int repeats[], int repeatsCount, int needDelete);
    int handleNormalPassword(int missingTypes, int repeats[], int repeatsCount);
    
public:
    int strongPasswordChecker(string password);
};

int PasswordChecker::countMissingTypes() {
    bool hasLower = false, hasUpper = false, hasDigit = false;
    for (char c : password) {
        if (islower(c)) hasLower = true;
        if (isupper(c)) hasUpper = true;
        if (isdigit(c)) hasDigit = true;
    }
    return (hasLower ? 0 : 1) + (hasUpper ? 0 : 1) + (hasDigit ? 0 : 1);
}

int PasswordChecker::findRepeats(int repeats[]) {
    int n = password.length();
    int count = 0;
    int i = 0;
    while (i < n && count < MAX_REPEATS) {
        int j = i;
        while (j < n && password[j] == password[i]) {
            j++;
        }
        int len = j - i;
        if (len >= 3) {
            repeats[count++] = len;
        }
        i = j;
    }
    return count;
}

int PasswordChecker::handleShortPassword(int missingTypes, int repeats[], int repeatsCount) {
    int needAdd = 6 - password.length();
    int replaceOps = 0;
    for (int i = 0; i < repeatsCount; i++) {
        replaceOps += repeats[i] / 3;
    }
    return max(needAdd, max(replaceOps, missingTypes));
}

int PasswordChecker::handleLongPassword(int missingTypes, int repeats[], int repeatsCount, int needDelete) {
    int deleteOps = 0;
    
    // Сначала удаляем по одному символу из групп длиной 3k (k>=1)
    for (int j = 0; j < repeatsCount && deleteOps < needDelete; j++) {
        if (repeats[j] >= 3 && repeats[j] % 3 == 0) {
            int toDelete = min(needDelete - deleteOps, 1);
            repeats[j] -= toDelete;
            deleteOps += toDelete;
        }
    }
    
    // Затем удаляем по 2 символа из групп длиной 3k+1
    for (int j = 0; j < repeatsCount && deleteOps < needDelete; j++) {
        if (repeats[j] >= 3 && repeats[j] % 3 == 1) {
            int toDelete = min(needDelete - deleteOps, 2);
            repeats[j] -= toDelete;
            deleteOps += toDelete;
        }
    }
    
    // Затем удаляем по 3 символа из оставшихся групп
    for (int j = 0; j < repeatsCount && deleteOps < needDelete; j++) {
        if (repeats[j] >= 3) {
            int toDelete = min(needDelete - deleteOps, (repeats[j] - 2) / 3 * 3);
            repeats[j] -= toDelete;
            deleteOps += toDelete;
        }
    }
    
    // Подсчитываем замены для оставшихся групп
    int replaceOps = 0;
    for (int i = 0; i < repeatsCount; i++) {
        if (repeats[i] >= 3) {
            replaceOps += repeats[i] / 3;
        }
    }
    
    return needDelete + max(replaceOps, missingTypes);
}

int PasswordChecker::handleNormalPassword(int missingTypes, int repeats[], int repeatsCount) {
    int replaceOps = 0;
    for (int i = 0; i < repeatsCount; i++) {
        replaceOps += repeats[i] / 3;
    }
    return max(replaceOps, missingTypes);
}

int PasswordChecker::strongPasswordChecker(string password) {
    this->password = password;
    int n = password.length();
    
    int missingTypes = countMissingTypes();
    int repeats[MAX_REPEATS];
    int repeatsCount = findRepeats(repeats);
    
    if (n < 6) {
        return handleShortPassword(missingTypes, repeats, repeatsCount);
    }
    
    if (n > 20) {
        int needDelete = n - 20;
        return handleLongPassword(missingTypes, repeats, repeatsCount, needDelete);
    }
    
    return handleNormalPassword(missingTypes, repeats, repeatsCount);
}

int main() {
    PasswordChecker checker;
    string password;
    
    cout << "Введите пароль для проверки: ";
    getline(cin, password);
    
    int steps = checker.strongPasswordChecker(password);
    cout << "Минимальное количество шагов для превращения пароля в надежный: " << steps << endl;
    
    return 0;
}

