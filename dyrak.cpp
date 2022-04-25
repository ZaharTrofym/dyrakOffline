#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class CardDeck {
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

class Player {
    private:
        vector<Card> cards;
};

class Card {
    private:
        int id = 0;
        int type = 1;
        string name = "";
        int nominal = 0;
        bool isRoot = false;
};

class Engine {

};

int main() {
    srand(time(NULL));

    CardDeck deckk;
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
    bool winOrLose = true;
    
    while (winOrLose) {
        cout << "Ти ходиш первим \nВибери карту з тих які в тебе є\nВведи цифру під якою знаходиться карта\n";
        for (int i = 0; i < player1.size(); i++) {
            cout << i + 1 << ". " << player1[i] << endl;
        }
        cin >> choose;

        if ((player1.size() || player2.size()) && card_deck.size() == 0) {
            winOrLose = false;
        }
    }
}