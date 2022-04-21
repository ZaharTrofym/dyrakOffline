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

        vector<string> start(vector<string> player) {
            for (int i = 0; i < 6; i++) {
            player[i] = deck[deck.size() - 1];
            deck.pop_back();
            }
            return player;
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

    player1 = deckk.start(player1);
    player2 = deckk.start(player2);
    int choose;
    
    while((player1.size() || player2.size()) && card_deck.size() == 0) {
        cout << "Ти ходиш первим \nВибери карту з тих які в тебе є\nВведи цифру під якою знаходиться карта\n";
        for (int i = 0; i < player1.size(); i++) {
            cout << i + 1 << ". " << player1[i] << endl;
        }
        cin >> choose;
    }
}