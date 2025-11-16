#include <iostream>
#include <queue>
#include <string>

using namespace std;

string predictPartyVictory(string senate) {
    queue<int> radiant, dire;
    int n = senate.length();
    
    // Инициализация: добавляем всех сенаторов в соответствующие очереди
    for (int i = 0; i < n; i++) {
        if (senate[i] == 'R') {
            radiant.push(i);
        } else {
            dire.push(i);
        }
    }
    
    // Симуляция раундов голосования
    while (!radiant.empty() && !dire.empty()) {
        int rIndex = radiant.front();
        int dIndex = dire.front();
        radiant.pop();
        dire.pop();
        
        // Сенатор с меньшим индексом (ходит первым) отменяет право сенатора с большим индексом
        if (rIndex < dIndex) {
            // Radiant отменяет Dire, Radiant остается активным для следующего раунда
            radiant.push(rIndex + n); // Добавляем с новым индексом для следующего раунда
        } else {
            // Dire отменяет Radiant, Dire остается активным для следующего раунда
            dire.push(dIndex + n);
        }
    }
    
    // Если одна из очередей пуста, другая фракция побеждает
    return radiant.empty() ? "Dire" : "Radiant";
}

int main() {
    cout << "=== Голосование в Сенате Dota2 ===" << endl;
    cout << "Введите строку сенаторов:" << endl;
    cout << "  - 'R' для сенатора фракции Radiant (Свет)" << endl;
    cout << "  - 'D' для сенатора фракции Dire (Тьма)" << endl;
    cout << "Примеры: \"RD\", \"RDD\", \"RRDDD\"" << endl;
    cout << "Ввод: ";
    
    string senate;
    cin >> senate;
    
    // Проверка корректности ввода
    bool valid = true;
    for (char c : senate) {
        if (c != 'R' && c != 'D') {
            valid = false;
            break;
        }
    }
    
    if (!valid || senate.empty()) {
        cout << "Ошибка: строка должна содержать только символы 'R' и 'D'!" << endl;
        return 1;
    }
    
    cout << "\nОбработка голосования..." << endl;
    string result = predictPartyVictory(senate);
    
    cout << "\n=== Результат ===" << endl;
    cout << "Победившая фракция: " << result << endl;
    
    return 0;
}

