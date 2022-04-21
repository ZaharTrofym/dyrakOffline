#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL));
    vector<vector<string> > card_deck;
    string suits[4] = {"Чірва", "Піка", "Буба", "Креста"};
    string cards[13] = {"Два", "Три", "Чотири", "П'ять", "Шість", "Сім", "Вісім", "Дев'ять", "Десять", "Валет", "Дама", "Король", "Туз"};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            card_deck[i][j] = suits[rand() % 4] + cards[rand() % 13];
            cout << card_deck[i][j] << endl;
        }
    }
}