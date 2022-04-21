#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL));
    vector<vector<string> > card_deck(13, vector<string>(4));
    string suits[4] = {"Чірва", "Піка", "Буба", "Креста"};
    string cards[13] = {"Два", "Три", "Чотири", "П'ять", "Шість", "Сім", "Вісім", "Дев'ять", "Десять", "Валет", "Дама", "Король", "Туз"};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            card_deck[i][j] = cards[rand() % 13] + " " + suits[rand() % 4];
        }
    }
}