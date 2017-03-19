// Tugcan Olgun

#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
string suits[4] = {"Spades", "Clubs", "Hearts", "Diamonds"};
int index[13][4] = {0};

class Card {
    int suit;
    int rank;
public:
    Card() {}
    Card(int r, int s) {
        suit = s;
        rank = r;
    }
    string getRank() {
        return ranks[rank];
    }
    string getSuit() {
        return suits[suit];
    }
    int getRankNum() {
        return rank;
    }
    int getSuitNum() {
        return suit;
    }
    void setRank(int r) {
        rank = r;
    }
    void setSuit(int s) {
        suit = s;
    }
};

class Deck {
    Card card[52];
public:
    Deck() {
        int count = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                card[count].setSuit(i);
                card[count].setRank(j);
                count++;
            }
        }
    }

    void Shuffle() {
        for (int i = 0; i < 52; ++i) {
            int randomNumber = rand() % 52;
            Card temp;
            temp = card[i];
            card[i] = card[randomNumber];
            card[randomNumber] = temp;
        }
    }

    void DealAll() {
        int count = 0;
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 4; ++j) {
                index[i][j] = count;
                count++;
            }
        }
    }

    int putUnder(int pile, int card) {
        int temp1 = 0;
        int temp2 = 0;
        temp1 = index[pile][1];
        index[pile][1] = index[pile][0];
        temp2 = index[pile][2];
        index[pile][2] = temp1;
        temp1 = index[pile][3];
        index[pile][3] = temp2;
        index[pile][0] = card;
        return temp1;
    }
    int IndX(int cardNum) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                if(index[j][i] == cardNum) {
                    return j;
                }
            }
        }
    }
    int IndY(int cardNum) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                if(index[j][i] == cardNum) {
                    return i;
                }
            }
        }
    }


    int Index(int rank, int suit) {
        for (int i = 0; i < 52; ++i) {
            if(card[i].getRankNum() == rank && card[i].getSuitNum() == suit) {
                return i;
            }
        }
    }

    Card getCard(int i) {
        return card[i];
    }
};

ostream &operator<<(ostream &out, Card &card) {
    out << card.getRank() << " of " << card.getSuit();
    return out;
}

int Game() {
    Deck deck;
    deck.Shuffle();
    deck.DealAll();
    int pile = deck.getCard(index[12][0]).getRankNum();
    int indX = 12;
    int indY = 0;
    int h;
    int countOfKings = 0;
    for (int i = 0; i < 52; ++i) {
        h = deck.putUnder(pile, deck.Index(deck.getCard(index[indX][indY]).getRankNum(), deck.getCard(index[indX][indY]).getSuitNum()));
        pile = deck.getCard(h).getRankNum();
        indX = deck.IndX(h);
        indY = deck.IndY(h);

        if(deck.getCard(h).getRankNum() == 12) {
            countOfKings++;
        }
        if(countOfKings==4 && i <50) {
            return 0;
        }
    }
    return 1;
}

int main() {
    srand(time(NULL));
    int x;
    int win = 0;
    int lose = 0;
    for (int i = 0; i < 100; ++i) {
        x = Game();
        if(x == 1) {
            win++;
        } else {
            lose++;
        }
    }
    cout << "The win/lose ratio is " << win << "/" << lose << " ";

    return 0;
}