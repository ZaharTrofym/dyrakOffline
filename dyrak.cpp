#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void pause(string text = "") {
    cout << "\n" << text << "\n";
    fflush(stdin);
    cin.get();
    system("clear");
}

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

        string getName() {
            return name;
        }

        int getType() {
            return type;
        }

        int getNominal() {
            return nominal;
        }

        bool getRoot() {
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

        void showCardsForWalk(string suits[4]) {
            cout << "\nВведи номер карти щоб походити нею";
            for (int i = 0; i < cards.size(); i++) {
                cout << "\n" << i + 1 << ". " << cards[i]->getName() << " " << suits[cards[i]->getType() - 1];
            }
            cout << endl;
        }

        void removeCard(int num) {
            Card* card = cards[cards.size() - 1];
            cards[num - 1] = card;
            cards.pop_back();
        }

        void setCards(vector<Card*> cards) {
            this->cards = cards;
        }

        vector<Card*> getCards() {
            return cards;
        }

        Card* getCard(int num) {
            return cards[num - 1];
        }

        vector<Card*> sorting(vector<Card*> cards) {
            vector<Card*> emptyErray;
            int count = cards.size();

            for (int i = 0; i < count; i++) {
                int check = 0;
                int value = 0;

                for (int j = 0; j < cards.size(); j++) {
                    if (j == 0) {
                        value = cards[0]->getType() * 100 + cards[0]->getNominal();
                    }
                    
                    if (value > cards[j]->getType() * 100 + cards[j]->getNominal()) {
                        value = cards[j]->getType() * 100 + cards[j]->getNominal();
                        check = j;
                    }
                }

                emptyErray.push_back(cards[check]);
                cards.erase(cards.begin() + check);
            }

            return emptyErray;
        }
};

class Deck {
    private:
        vector<Card*> deck;
        vector<Card*> shuffleDeck;
    public:
        void addCardToDeck(Card* card) {
            deck.push_back(card);
        }

        void addCardToShuffle(Card* card) {
            shuffleDeck.push_back(card);
        }

        void showCards() {
            string card;
            for(int i = 0; i < shuffleDeck.size(); i++) {
                card = shuffleDeck[i]->getName();
                cout << card << endl;
            }
        }

        void setShuffleDeck(vector<Card*> shuffleDeck) {
            this->shuffleDeck = shuffleDeck;
        }
        
        vector<Card*> getShuffleDeck() {
            return shuffleDeck;
        }

        Card* getRandomCardInDeck() {
            return deck[rand() % deck.size()];
        }

        Card* getCardInShuffleDeck() {
            Card* card = shuffleDeck[shuffleDeck.size() - 1];
            shuffleDeck.pop_back();
            
            return card;
        }
};

class Engine {
    private:
        string suits[4] = {"Чірва", "Піка", "Буба", "Креста"};
        string cards[13] = {"Два", "Три", "Чотири", "П'ять", "Шість", "Сім", "Вісім", "Дев'ять", "Десять", "Валет", "Дама", "Король", "Туз"};
        int walk;
        int root;
        bool isRoot;
        bool takeCards;
    public:
        Engine() {
            root = rand() % 4 + 1;
        }

        Deck* generateDeck() {
            Deck* deck = new Deck();
            vector<Card*> shuffleDeck;

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
                for (int i = 0; i < shuffleDeck.size(); i++) {
                    if (card == shuffleDeck[i]) {
                        inDeck = true;
                    }
                }
                if (inDeck == false) {
                    shuffleDeck.push_back(card);
                    i++;
                }
            }
            deck->setShuffleDeck(shuffleDeck);

            return deck;
        }

        Card* generateCard(int type, string name, int nominal, bool isRoot) {
            Card* card = new Card(type, name, nominal, isRoot);

            return card;
        }

        Player* generatePlayer(Deck* deck) {
            Player* player = new Player();
            for (int i = 0; i < 6; i++) {
                player->addCard(deck->getCardInShuffleDeck());
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

        int getWalk() {
            return walk;
        }
        
        void setWalk(int walk) {
            this->walk = walk;
        }

        bool getTakeCards() {
            return takeCards;
        }

        bool oneRound(Player* player1, Player* player2, Deck* deck) {
            int num1, num2, x = 0;
            takeCards = false;
            vector<Card*> walker;
            
            if (walk == 1) {  //хід гравця
                if (deck->getShuffleDeck().size() > 0) {
                    for (int i = 0; i < 6; i++) {
                        if (player2->getCards().size() < 6) {
                            player2->addCard(deck->getCardInShuffleDeck());
                        }

                        if (player1->getCards().size() < 6) {
                            player1->addCard(deck->getCardInShuffleDeck());
                        }
                    }
                }

                showRoot();  
                player1->setCards(player1->sorting(player1->getCards()));
                player1->showCardsForWalk(suits);
                cin >> num1;

                if (num1 > 0 && num1 <= player1->getCards().size()) {  //хід гравця та спроба побити цей хід суперником
                    walker.push_back(player1->getCard(num1));
                    player1->removeCard(num1);
                    cout << walker[0]->getName() << " " << suits[walker[0]->getType() - 1] << " -> " << "...";
                    pause("");

                    if(player1->getCards().size() == 0 && deck->getShuffleDeck().size() == 0) {  //виграш гравця
                        cout << "Ви виграли, тому що у вас закінчились карти! ";
                        return true;
                    }

                    Card* card1;
                    Card* card2;
                    for (int i = 0; i < player2->getCards().size(); i++) {  //пошук карти не козиря і найменшого номіналу щоб побити атаку
                        if (walker[0]->getType() == player2->getCard(i + 1)->getType() && walker[0]->getNominal() < player2->getCard(i + 1)->getNominal()) {
                            card1 = player2->getCard(i + 1);
                            if(card1->getNominal() >= player2->getCard(i + 1)->getNominal()) {
                                card2 = player2->getCard(i + 1);
                                num2 = i + 1;
                            }
                            x = 1;
                        }
                    }
                    if (x == 0) {  //якщо немає не козиря то спроба захиститись козирем
                        for (int i = 0; i < player2->getCards().size(); i++) {
                            if(player2->getCard(i + 1)->getRoot() == true) {
                                card1 = player2->getCard(i + 1);
                                if(card1->getNominal() >= player2->getCard(i + 1)->getNominal()) {
                                    card2 = player2->getCard(i + 1);
                                    num2 = i + 1;
                                    x = 1;
                                }
                            }
                        }
                    }
                    if (x == 1) {
                        player2->removeCard(num2);
                    }

                    if (x == 0) {  //якщо немає чим побити карту
                        cout << "\nСуперник забирає карти ";
                        takeCards = true;
                        player2->addCard(walker[0]);
                        pause();
                    }
                    else {  //суперник відстояв атаку
                        cout << walker[0]->getName() << " " << suits[walker[0]->getType() - 1] << " -> " << card2->getName() << " " << suits[card2->getType() - 1];
                    }

                    pause();
                }
                else {
                    cout << "\nВи ввели не правльну цифру. Почнемо з початку";

                    return false;
                }
            }
            else if (walk == 2) {  //хід суперника
                vector<Card*> temp;
                int take;

                if (deck->getShuffleDeck().size() > 0) {
                    for (int i = 0; i < 6; i++) {
                        if (player1->getCards().size() < 6) {
                            player1->addCard(deck->getCardInShuffleDeck());
                        }

                        if (player2->getCards().size() < 6) {
                            player2->addCard(deck->getCardInShuffleDeck());
                        }
                    }
                }

                if (deck->getShuffleDeck().size() > 0) {  //додавання карт якщо їх не вистачає
                    if (player1->getCards().size() < player2->getCards().size()) {
                        for (int i = 0; i < 6 - player1->getCards().size(); i++) {
                            if (deck->getShuffleDeck().size() != 0 && player1->getCards().size() < 6) {
                                player1->addCard(deck->getCardInShuffleDeck());
                            }
                            if (deck->getShuffleDeck().size() != 0 && player2->getCards().size() < 6) {
                                player2->addCard(deck->getCardInShuffleDeck());
                            }
                        }
                    }

                    if (player2->getCards().size() < player1->getCards().size()) {
                        for (int i = 0; i < 6 - player2->getCards().size(); i++) {
                            if (deck->getShuffleDeck().size() != 0 && player2->getCards().size() < 6) {
                                player2->addCard(deck->getCardInShuffleDeck());
                            }
                            if (deck->getShuffleDeck().size() != 0 && player1->getCards().size() < 6) {
                                player1->addCard(deck->getCardInShuffleDeck());
                            }
                        }
                    }
                }

                Card* card1;
                Card* card2;
                for (int i = 0; i < player2->getCards().size(); i++) {  //пошук карти для того щоб напасти
                    card1 = player2->getCard(i + 1);
                    if (player2->getCard(i + 1)->getRoot() == false && player2->getCard(i + 1)->getNominal() <= card1->getNominal()) { //шукається карта не козирь
                        card2 = player2->getCard(i + 1);
                        x = 1;
                        num1 = i + 1;
                    }
                }
                if (x == 0) { //шукається козирь
                    for (int i = 0; i < player2->getCards().size(); i++) {
                        card1 = player2->getCard(i + 1);
                        if (player2->getCard(i + 1)->getNominal() <= card1->getNominal()) {
                            card2 = player2->getCard(i + 1);
                            num1 = i + 1;
                        }
                    }
                }
                walker.push_back(card2);
                player2->removeCard(num1);
                cout << walker[0]->getName() << " " << suits[walker[0]->getType() - 1] << " -> " << "...";

                if (deck->getShuffleDeck().size() == 0 && player2->getCards().size() == 0) {
                    cout << "\nСуперник вийграв, у нього закінчилися карти\n";
                    
                    return true;
                }

                player1->setCards(player1->sorting(player1->getCards()));
                showRoot();  

                for (int i = 0; i < player1->getCards().size(); i++) {  //пошук карт які можуть відбити атаку
                    if (walker[0]->getRoot() == false) {  //якщо атака не козирь
                        if (player1->getCard(i + 1)->getType() == walker[0]->getType() && player1->getCard(i + 1)->getNominal() > walker[0]->getNominal()) {
                            temp.push_back(player1->getCard(i + 1));
                        }
                        else if (player1->getCard(i + 1)->getRoot() == true) {
                            temp.push_back(player1->getCard(i + 1));
                        }
                    }
                    else {  //якщо атака козирь
                        if (player1->getCard(i + 1)->getType() == walker[0]->getType() && player1->getCard(i + 1)->getNominal() > walker[0]->getNominal()) {
                            temp.push_back(player1->getCard(i + 1));
                        }
                    }
                }

                if (temp.size() > 0) {
                    cout << "\nВибери карту для захисту: \n";
                    for (int i = 0; i < temp.size(); i++) {
                        cout << i + 1 << ". " << temp[i]->getName() << " " << suits[temp[i]->getType() - 1] << endl;
                        take = i + 2;
                    }
                    cout << take << ". " << "Забираєш карти" << endl;
                    cin >> num2;
                }
                else {
                    cout << "\nТи не можеш відбити атаку, тому забираєш карти\n";
                    takeCards = true;
                    player1->addCard(walker[0]);

                    return false;
                }
                if (num2 == take) {
                    cout << "\nТи вирішив взяти карти\n";
                    takeCards = true;
                    player1->addCard(walker[0]);
                    
                    return false;
                }
                else if (num2 > 0 && num2 < temp.size() + 1) {
                    for (int i = 0; i < player1->getCards().size(); i++) {
                        if (temp[num2 - 1] == player1->getCards()[i]) {
                            player1->removeCard(i + 1);
                        }
                    }

                    cout << walker[0]->getName() << " " << suits[walker[0]->getType() - 1] << " -> " << temp[num2 - 1]->getName() << " " << suits[temp[num2 - 1]->getType() - 1];

                    return false;
                }
                else {
                    cout << "\nТи ввів не ту цифру, тому щоб не було помилки ти взяв карти\n";
                    takeCards = true;
                    player1->addCard(walker[0]);
                    
                    return false;
                }
            }
        }
};

int main() {
    srand(time(NULL));
    Engine* engine = new Engine();
    Deck* deck = engine->generateDeck();
    Player* player1 = engine->generatePlayer(deck);
    Player* player2 = engine->generatePlayer(deck);
    bool isEnd = false;
    
    cout << "\nПривіт, ти знаходишся в грі дурак офлайн!\n";

    pause("Якщо хочеш продовжити нажми Enter: ");

    engine->showRoot();
    engine->setWalk(1);

    while(!isEnd) {
            if (engine->getWalk() == 1) {
                cout << "\nВаш хід";
            }
            else {
                cout << "\nХід суперника";
            }
            pause();
            isEnd = engine->oneRound(player1, player2, deck);

            if (engine->getWalk() == 1 && engine->getTakeCards() == false) {
                engine->setWalk(2);
            }
            else if (engine->getWalk() == 2 && engine->getTakeCards() == false) {
                engine->setWalk(1);
            }
    }

    pause("\nкінець\n");
    
    return 0;
}