#pragma once
#include <vector>
#include <string>
#include "card.h"

class DurakGame {
private:
    std::vector<Card> deck;
    std::vector<Card> player;
    std::vector<Card> computer;

    int trumpSuit;

    std::string rankToString(int rank);
    std::string suitToString(int suit);
    std::string cardToString(Card card);

    int getNumber();
    void createDeck();
    void dealCards();
    bool beats(Card attack, Card defend);
    void showPlayerCards();

public:
    void play();
};
