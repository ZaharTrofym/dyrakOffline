#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;


class Card {
    private:
        int type;
        string name;
        int nominal;
        bool isRoot;
    public:
        Card(int type, string name, int nominal, bool isRoot) {
            this->type = type;
            this->name = name;
            this->nominal = nominal;
            this->isRoot = isRoot;
        }

        bool getCard() {
            return isRoot;
        }
};

class Player {
    private:
        vector<Card*> cards;
    public:
        void addCard(Card* card) {
            cards.push_back(card);
        }

        void showCards() {
            for (int i = 0; i < 6; i++) {
                cout << cards[i] << endl;
            }
        }
};

class Deck {
    private:
        vector<Card*> deck;
        vector<Card*> shuffle_deck;
    public:
        void addCardToDeck(Card* card) {
            deck.push_back(card);
        }

        void addCardToShuffle(Card* card) {
            shuffle_deck.push_back(card);
        }

        void showCards() {
            bool card;
            for(int i = 0; i < 52; i++) {
                card = shuffle_deck[i]->getCard();
                cout << card << endl;
            }
        }

        Card* deleteAndReturnCard() {
            return shuffle_deck[rand() % shuffle_deck.size()];
        }

        vector<Card*> getShuffleDeck() {
            return shuffle_deck;
        }

        Card* getRandomCardInDeck() {
            return deck[rand() % deck.size()];
        }
};

class Engine {
    private:
        string suits[4] = {"Чірва", "Піка", "Буба", "Креста"};
        string cards[13] = {"Два", "Три", "Чотири", "П'ять", "Шість", "Сім", "Вісім", "Дев'ять", "Десять", "Валет", "Дама", "Король", "Туз"};
        int root;
        bool isRoot;
    public:
        Engine() {
            root = rand() % 4 + 1;
        }

        Deck* generateDeck() {
            Deck* deck = new Deck();
            vector<Card*> shuffle_deck;

            for (int i = 0; i < 4; i++) {
                if (i + 1 == root) {
                    isRoot = true;
                }
                else {
                    isRoot = false;
                }

                for (int j = 0; j < 13; j++) {
                    deck->addCardToDeck(generateCard(i + 1, cards[j], j + 1, this->isRoot));
                } 
            }
            
            Card* card;
            bool inDeck;
            int i = 0;
            while(i < 52) {
                card = deck->getRandomCardInDeck();
                inDeck = false;
                for (int i = 0; i < shuffle_deck.size(); i++) {
                    if (card == shuffle_deck[i]) {
                        inDeck = true;
                    }
                }
                if (inDeck == false) {
                    shuffle_deck.push_back(card);
                    i++;
                }
            }

            return deck;
        }

        Card* generateCard(int type, string name, int nominal, bool isRoot) {
            Card* card = new Card(type, name, nominal, isRoot);

            return card;
        }

        Player* generatePlayer(Deck* deck) {
            Player* player = new Player();
            for (int i = 0; i < 6; i++) {
                player->addCard(deck->deleteAndReturnCard());
            }

            return player;
        }

        void showRoot() {
            for(int i = 0; i < 4; i++) {
                if (root == i + 1) {
                    cout << "\nКозирь - " << suits[i] << endl;
                }
            } 
        }
};

int main() {
    srand(time(NULL));
    Engine* engine = new Engine();
    Deck* deck = engine->generateDeck();
    Player* player1 = engine->generatePlayer(deck);

    cout << 234214132;
}