#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CardDeck {
    private:
        vector<string> suit;

    public:
        void addSuits() {
            suit.push_back("Чірва");
            suit.push_back("Піка");
            suit.push_back("Креста");
            suit.push_back("Буба");
        }
};

int main() {
    vector<vector<string> > card_deck;
    string suits[4] = {"Чірва", "Піка", "Буба", "Креста"};
    string cards[13] = {"Два", "Три", "Чотири", "П'ять", "Шість", "Сім", "Вісім", "Дев'ять", "Десять", "Валет", "Дама", "Король", "Туз"};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            
        }
    }
}