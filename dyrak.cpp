#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Card_deck {
    private:
        vector<string> deck;
    public:
        void getDeck(vector<string> deck) {
            this->deck = deck;
        }
};

int main() {
    srand(time(NULL));

    Card_deck deckk;
    vector<string> card_deck(52);
    string suits[4] = {"Чірва", "Піка", "Буба", "Креста"};
    string cards[13] = {"Два", "Три", "Чотири", "П'ять", "Шість", "Сім", "Вісім", "Дев'ять", "Десять", "Валет", "Дама", "Король", "Туз"};
    
    for (int i = 0; i < card_deck.size(); i++) {
        card_deck[i] = cards[rand() % 13] + " " + suits[rand() % 4];
    }
    deckk.getDeck(card_deck);
    vector<string> player1(6);
    vector<string> player2(6);

    for (int i = 0; i < 6; i++) {
        player1[i] = card_deck[card_deck.size() - 1];
        card_deck.pop_back();
    }
}